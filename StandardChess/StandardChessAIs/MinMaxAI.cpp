//
// Created by Ethan on 4/28/20.
//

#include "MinMaxAI.hpp"
#include "../../ChessGame/ChessAIException.hpp"

const std::string MinMaxAI::AIName = "Standard Min/Max AI";
const std::string MinMaxAI::AIDesc = "An AI that chooses its moves in an attempt to maximize its own score while minimizing its opponent's score.";

namespace {
    std::vector<ChessMove> getNextMoves(const ChessGameState& state, bool forWhite) {
        std::vector<ChessMove> result;
        ChessCellState soughtCellState = forWhite ? ChessCellState::white : ChessCellState::black;

        // For each cell on the board, if the piece is ours and we can move it, add its moves to the results to return.
        const ChessBoard& board = state.board();
        for(int row = 0; row != board.height(); ++row) {
            for(int col = 0; col != board.width(); ++col) {
                if(board.getCell(row, col)->getState() != ChessCellState::empty && board.getCell(row, col)->getState() == soughtCellState) {
                    for(std::pair<int, int>& endCoords : state.getValidPieceMoves({row, col})) {
                        if(state.isValidMove(std::make_pair(row, col), endCoords))
                            result.emplace_back(std::make_pair(row, col), endCoords);
                    }
                }
            }
        }

        return result;
    }

    int getAddlCapturePoints(std::unique_ptr<ChessGameState> &state, bool isWhiteAI){
        // Weights determining how important it is to capture a given piece. The higher the number, the higher the priority.
        static std::unordered_map<std::string, int> weights{
                {"King",      1000},
                {"Queen", 600},
                {"Rook",     300},
                {"Knight",     100},
                {"Pawn",        40}
        };

        int addlPoints = 0;

        // Add the points received for capturing a given piece multiplied by the number of said piece captured.
        for(const auto& pieceData : state->getCapturedPieces(isWhiteAI)){
            if(weights.find(pieceData.first) != weights.end()){
                addlPoints += weights[pieceData.first] * pieceData.second;
            }
        }

        return addlPoints;
    }

    // evalState() evaluates the current state of the game by giving it a score based on the following criteria
    //  + the current score as defined by a game state for that player
    //  + the weighted points received from capturing opponents pieces
    //  - the opponent's score calculated in the same manner
    int evalState(std::unique_ptr<ChessGameState> &state, bool isWhiteAI) {
        int result = 0;
        if (isWhiteAI)
            result = state->whiteScore() + getAddlCapturePoints(state, isWhiteAI) - state->blackScore() - getAddlCapturePoints(state, !isWhiteAI);
        else
            result = state->blackScore() + getAddlCapturePoints(state, isWhiteAI) - state->whiteScore() - getAddlCapturePoints(state, !isWhiteAI);

        return result;
    }
}

MinMaxAI::MinMaxAI(unsigned short maxDepth, bool enableMultiThread, bool enableAlphaBetaPrune)
    : MAX_DEPTH{maxDepth}, ENABLE_MULTI_THREADING{enableMultiThread}, ENABLE_ALPHA_BETA_PRUNING{enableAlphaBetaPrune} {

}

int alphaBetaSearch(std::unique_ptr<ChessGameState> &state, int depth, int alpha, int beta, bool isWhiteAI, bool enableABPrune) {
    if (depth == 0)
        return evalState(state, isWhiteAI);

    // If the current turn is this AI's turn, then maximize the score its trying to get, else try to minimize the opponent's score
    // by simulating all possible moves from the current game state (to a limited recursion depth). A branch may be eliminated early
    // if it is determined it is a useless to calculated based on the results of previous simulated moves.
    if (isWhiteAI == state->isWhiteTurn()) { //FIXME check whether should be && or ==
        int maxResult = std::numeric_limits<int>::min();
        std::vector<ChessMove> todo = getNextMoves(*state, isWhiteAI);

        for(const ChessMove& move : todo) {
            std::unique_ptr<ChessGameState> stateClone = state->clone();
            stateClone->makeMove(move.start, move.end);
            maxResult = std::max(maxResult, alphaBetaSearch(stateClone, depth - 1, alpha, beta, isWhiteAI, enableABPrune));

            if(enableABPrune) {
                // Don't bother with this branch if it is a loss so as to not waste time
                alpha = std::max(alpha, maxResult);
                if (alpha >= beta)
                    break;
            }
        }
        return maxResult;
    } else {
        int minResult = std::numeric_limits<int>::max();
        std::vector<ChessMove> todo = getNextMoves(*state, !isWhiteAI);

        for (const ChessMove& move : todo) {
            std::unique_ptr<ChessGameState> stateClone = state->clone();
            stateClone->makeMove(move.start, move.end);
            minResult = std::min(minResult, alphaBetaSearch(stateClone, depth - 1, alpha, beta, isWhiteAI, enableABPrune));

            if(enableABPrune) {
                // Don't bother with this branch if it is a loss so as to not waste time
                beta = std::min(beta, minResult);
                if (alpha >= beta)
                    break;
            }
        }
        return minResult;
    }
}



ChessMove MinMaxAI::choseMove(const ChessGameState& state) {
    bool isWhiteAI = state.isWhiteTurn();
    int maxScore = std::numeric_limits<int>::min();
    std::vector<ChessMove> nextMoves = getNextMoves(state, isWhiteAI);
    ChessMove bestMove = nextMoves[0];

    std::unique_ptr<ChessGameState> stateClone = state.clone();

    // For each move, that can be made, simulate moves via clones of the current state, and receive a score for that particular branch.
    // The highest branch score is determined to be the best move to make, and will be returned from the function.
    for (auto branchMove : nextMoves) {
        std::unique_ptr<ChessGameState> branch = state.clone();
        branch->makeMove(branchMove.start, branchMove.end);

        int branchScore = alphaBetaSearch(branch, MAX_DEPTH, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), isWhiteAI, ENABLE_ALPHA_BETA_PRUNING);

        if (branchScore > maxScore) {
            maxScore = branchScore;
            bestMove = branchMove;
        }
    }

    return bestMove;
}

#include <iostream>
#include <thread>
#include <mutex>
#include "IterativeDeepeningAI.hpp"

const std::string IterativeDeepeningAI::AIName = "Iterative Deepening AI (EXPERIMENTAL)";
const std::string IterativeDeepeningAI::AIDesc = "A minimax AI that continues its search until a given time limit.";

namespace {
    std::vector<ChessMove> getNextMoves(const ChessGameState &state, bool forWhite) {
        std::vector<ChessMove> result;
        ChessCellState soughtCellState = forWhite ? ChessCellState::white : ChessCellState::black;

        // For each cell on the board, if the piece is ours and we can move it, add its moves to the results to return.
        const ChessBoard &board = state.board();
        for (int row = 0; row != board.height(); ++row) {
            for (int col = 0; col != board.width(); ++col) {
                if (board.getCell(row, col)->getState() != ChessCellState::empty &&
                    board.getCell(row, col)->getState() == soughtCellState) {
                    for (std::pair<int, int> &endCoords : state.getValidPieceMoves({row, col})) {
                        if (state.isValidMove(std::make_pair(row, col), endCoords)) {
                            // TODO look into optimizing this operation
                            if (state.board().getCell(endCoords.first, endCoords.second)->getState() !=
                                ChessCellState::empty)
                                result.insert(result.begin(), ChessMove({row, col}, endCoords));
                            else
                                result.emplace_back(std::make_pair(row, col), endCoords);
                        }
                    }
                }
            }
        }

        return result;
    }

    int getAddlCapturePoints(std::unique_ptr<ChessGameState> &state, bool isWhiteAI) {
        // Weights determining how important it is to capture a given piece. The higher the number, the higher the priority.
        static std::unordered_map<std::string, int> weights{
                {"King",   1000},
                {"Queen",  600},
                {"Rook",   300},
                {"Bishop", 300},
                {"Knight", 100},
                {"Pawn",   40}
        };

        int addlPoints = 0;

        // Add the points received for capturing a given piece multiplied by the number of said piece captured.
        for (const auto &pieceData : state->getCapturedPieces(isWhiteAI)) {
            if (weights.find(pieceData.first) != weights.end()) {
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
            result = state->whiteScore() + getAddlCapturePoints(state, isWhiteAI) - state->blackScore() -
                     getAddlCapturePoints(state, !isWhiteAI);
        else
            result = state->blackScore() + getAddlCapturePoints(state, isWhiteAI) - state->whiteScore() -
                     getAddlCapturePoints(state, !isWhiteAI);

        return result;
    }

    int alphaBetaSearch(std::unique_ptr<ChessGameState> &state, int depth, int alpha, int beta, bool isWhiteAI,
                        bool enableABPrune, const std::chrono::time_point<std::chrono::steady_clock> &cutoffTime) {

//        if(std::chrono::steady_clock::now() >= cutoffTime && depth != 0){
//            std::cout << "Terminating AB search early at depth left:" << depth << "\n";
//        }
        if (depth == 0 || std::chrono::steady_clock::now() >= cutoffTime)
            return evalState(state, isWhiteAI);

        // If the current turn is this AI's turn, then maximize the score its trying to get, else try to minimize the opponent's score
        // by simulating all possible moves from the current game state (to a limited recursion depth). A branch may be eliminated early
        // if it is determined it is a useless to calculated based on the results of previous simulated moves.
        if (isWhiteAI == state->isWhiteTurn()) { //FIXME check whether should be && or ==
            int maxResult = std::numeric_limits<int>::min();
            std::vector<ChessMove> todo = getNextMoves(*state, isWhiteAI);

            for (const ChessMove &move : todo) {
                state->makeMove(move.start, move.end);
                maxResult = std::max(maxResult, alphaBetaSearch(state, depth - 1, alpha, beta, isWhiteAI, enableABPrune,
                                                                cutoffTime));
                state->undoMove();

                if (enableABPrune) {
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

            for (const ChessMove &move : todo) {
                state->makeMove(move.start, move.end);
                minResult = std::min(minResult, alphaBetaSearch(state, depth - 1, alpha, beta, isWhiteAI, enableABPrune,
                                                                cutoffTime));
                state->undoMove();

                if (enableABPrune) {
                    // Don't bother with this branch if it is a loss so as to not waste time
                    beta = std::min(beta, minResult);
                    if (alpha >= beta)
                        break;
                }
            }
            return minResult;
        }
    }

    std::vector<std::vector<ChessMove>> divideMoveWork(const std::vector<ChessMove> &moves, int partitions) {
        std::vector<std::vector<ChessMove>> result(partitions);

        int copyIndex = 0;
        int partIndex = 0;
        while (copyIndex != moves.size()) {
            if (partIndex == partitions)
                partIndex = 0;

            result[partIndex].push_back(moves[copyIndex]);
            ++copyIndex;
            ++partIndex;
        }

        return result;
    }
}

IterativeDeepeningAI::IterativeDeepeningAI() : timeLimit(800) {

}

IterativeDeepeningAI::IterativeDeepeningAI(int msTimeLimit) {
    timeLimit = msTimeLimit;
}

ChessMove IterativeDeepeningAI::choseMove(const ChessGameState &state) {
    if (ENABLE_MULTI_THREADING) {
        return MTChooseMove(state);
    }

    std::chrono::time_point startTime = std::chrono::steady_clock::now();
    std::chrono::time_point<std::chrono::steady_clock> timeCutoff = startTime + std::chrono::milliseconds{timeLimit};
    int searchDepth = 0;

    bool isWhiteAI = state.isWhiteTurn();
    int maxScore = std::numeric_limits<int>::min();
    std::vector<ChessMove> nextMoves = getNextMoves(state, isWhiteAI);
    ChessMove bestMove = nextMoves[0];

    std::unique_ptr<ChessGameState> stateClone = state.clone();

    //std::chrono::duration<double, std::milli> elapsedTime = std::chrono::milliseconds(0);
    while (std::chrono::steady_clock::now() < timeCutoff) {
        // For each move, that can be made, simulate moves via clones of the current state, and receive a score for that particular branch.
        // The highest branch score is determined to be the best move to make, and will be returned from the function.
        for (auto branchMove : nextMoves) {
            std::unique_ptr<ChessGameState> branch = state.clone();
            branch->makeMove(branchMove.start, branchMove.end);

            int branchScore = alphaBetaSearch(branch, searchDepth, std::numeric_limits<int>::min(),
                                              std::numeric_limits<int>::max(), isWhiteAI, ENABLE_ALPHA_BETA_PRUNING,
                                              timeCutoff);

            if (branchScore > maxScore) {
                maxScore = branchScore;
                bestMove = branchMove;
            }
        }

        //elapsedTime = std::chrono::steady_clock::now() - startTime;;
        ++searchDepth;
    }
    //std::cout << "ID Depth: " << searchDepth << ", Best score:" << maxScore << "\n";
    return bestMove;
}

IterativeDeepeningAI *IterativeDeepeningAI::clone() const {
    return new IterativeDeepeningAI(timeLimit);
}


void IterativeDeepeningAI::MTSearchHelper(const ChessGameState &state, const std::vector<ChessMove> &moveQueue,
                                          int &maxScore, ChessMove &bestMove, bool isWhiteAI, int searchDepth,
                                          std::chrono::time_point<std::chrono::steady_clock> &cutoffTime) {
    if (moveQueue.empty())
        return;

    for (auto branchMove : moveQueue) {
        std::unique_ptr<ChessGameState> branch = state.clone();
        branch->makeMove(branchMove.start, branchMove.end);

        int branchScore = alphaBetaSearch(branch, searchDepth, std::numeric_limits<int>::min(),
                                          std::numeric_limits<int>::max(), isWhiteAI, ENABLE_ALPHA_BETA_PRUNING,
                                          cutoffTime);

        std::lock_guard<std::mutex> branchScoreLock(scoringMutex);
        if (branchScore > maxScore) {
            maxScore = branchScore;
            bestMove = branchMove;
        }
    }
}

ChessMove IterativeDeepeningAI::MTChooseMove(const ChessGameState &state) {
    bool isWhiteAI = state.isWhiteTurn();
    int maxScore = std::numeric_limits<int>::min();
    std::vector<ChessMove> nextMoves = getNextMoves(state, isWhiteAI);
    ChessMove bestMove = nextMoves[0];

    int searchDepth = -1;
    std::chrono::time_point startTime = std::chrono::steady_clock::now();
    std::chrono::time_point<std::chrono::steady_clock> timeCutoff = startTime + std::chrono::milliseconds{timeLimit};

    // For each move, that can be made, simulate moves via clones of the current state, and receive a score for that particular branch.
    // The highest branch score is determined to be the best move to make, and will be returned from the function.
    // All the possible moves are divided evenly among the number of threads allotted.
    while (std::chrono::steady_clock::now() < timeCutoff) {
        ++searchDepth;

        std::vector<std::thread> activeThreads;
        std::vector<std::vector<ChessMove>> threadWork = divideMoveWork(nextMoves, MAX_THREADS);
        for (int i = 0; i != threadWork.size(); ++i) {
            activeThreads.emplace_back(std::thread(&IterativeDeepeningAI::MTSearchHelper, this,
                                                   std::ref(state), std::ref(threadWork[i]), std::ref(maxScore),
                                                   std::ref(bestMove), isWhiteAI, searchDepth, std::ref(timeCutoff)));
        }

        for (int i = 0; i != activeThreads.size(); ++i) {
            activeThreads[i].join();
        }
    }

    //std::cout << "MT ID Depth: " << searchDepth << ", Best score:" << maxScore << "\n";
    return bestMove;
}
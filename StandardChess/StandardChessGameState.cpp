//
// Created by Ethan on 3/11/20.
//

#include "StandardChessGameState.hpp"
#include "StandardChessBoard.hpp"
#include "../ChessGame/ChessException.hpp"

namespace {
    inline bool moveIsInBounds(std::pair<int, int> move, int boardWidth, int boardHeight){
        return move.first >= 0 && move.first < boardHeight && move.second >= 0 && move.second < boardWidth;
    }

    template <typename T, typename T2>
    std::pair<int, int> addPair(const std::pair<T, T2>& pair, const std::pair<T, T2>& pair2){
        return {pair.first + pair2.first, pair.second + pair2.second};
    }
}

StandardChessGameState::StandardChessGameState(StandardChessBoard board)
    : whitePoints{0}, blackPoints{0}, whiteTurn{true}, gameOver{false} {
    _board = std::make_unique<StandardChessBoard>(std::move(board));
}

StandardChessGameState::StandardChessGameState(const StandardChessGameState& other)
    : whitePoints{other.whitePoints}, blackPoints{other.blackPoints}, whiteTurn{other.whiteTurn}, gameOver{other.gameOver},
      whiteCaptured{other.whiteCaptured}, blackCaptured{other.blackCaptured}{
    _board = std::make_unique<StandardChessBoard>(*other._board);
}

const ChessBoard& StandardChessGameState::board() const noexcept {
    return *_board;
}

int StandardChessGameState::whiteScore() const noexcept {
    return whitePoints;
}

int StandardChessGameState::blackScore() const noexcept {
    return blackPoints;
}

bool StandardChessGameState::isGameOver() const noexcept {
    return gameOver;
}

bool StandardChessGameState::isWhiteTurn() const noexcept {
    return whiteTurn;
}

bool StandardChessGameState::isBlackTurn() const noexcept {
    return !whiteTurn;
}

void StandardChessGameState::isValidMoveThrow(std::pair<int, int> start, std::pair<int, int> end, bool isWhite) const {
    std::string startStr = '(' + std::to_string(start.first) + ", " + std::to_string(start.second) + ')';
    std::string endStr = '(' + std::to_string(end.first) + ", " + std::to_string(end.second) + ')';

    std::shared_ptr<ChessCell> startCell = _board->getCell(start.first, start.second);
    std::shared_ptr<ChessCell> endCell = _board->getCell(end.first, end.second);

    // If the start move position is not in bounds, throw a ChessException.
    if(!moveIsInBounds(start, _board->width(), _board->height())){
        //std::string endStr = '(' + std::to_string(end.first) + ", " + std::to_string(end.second) + ')';
        throw ChessException{"Invalid move: start position is not in bounds " + startStr + " -> " + endStr};
    }
    // If the end move position is not in bounds, throw a ChessException
    else if(!moveIsInBounds(end, _board->width(), _board->height())){
        //std::string endStr = '(' + std::to_string(end.first) + ", " + std::to_string(end.second) + ')';
        throw ChessException{"Invalid move: end position is not in bounds " + startStr + " -> " + endStr};
    }
    else if(startCell->getState() == ChessCellState::empty){
        throw ChessException{"Invalid move: start position is empty"  + startStr + " -> " + endStr};
    }
    else if(!(startCell->getPiece().isValidMove(start, end) || startCell->getPiece().isValidCaptureMove(start, end))){
        throw ChessException{"Invalid move: a " + startCell->getPiece().getName() +
                             " cannot move under any circumstances from " + startStr + " -> " + endStr};
    }
    // If the piece at the requested position does not belong to the player requesting the move, throw a ChessException.
    else if((startCell->getPiece().isWhite() && !isWhite) ||
            (startCell->getPiece().isBlack() && isWhite)){
        std::string currColor = isWhite ? "white" : "black";
        throw ChessException{"Invalid move request: the piece at " + startStr + " does not belong to " + currColor};
    }
    // If the player tries to take one of their own pieces, throw a ChessException.
    else if(endCell->getState() != ChessCellState::empty &&
            ((startCell->getPiece().isWhite() && endCell->getPiece().isWhite()) ||
             (startCell->getPiece().isBlack() && endCell->getPiece().isBlack()))){
        std::string currColor = isWhiteTurn() ? "white" : "black";
        throw ChessException{"Invalid move: the pieces at " + startStr + " and " + endStr + " both belong to " + currColor};
    }

    else if(endCell->getState() != ChessCellState::empty && startCell->getPiece().hasCaptureMove() && !startCell->getPiece().isValidCaptureMove(start, end)){
        throw ChessException{"Invalid capture move: a " + startCell->getPiece().getName() +
                             " cannot perform a capture from " + startStr + " -> " + endStr};
    }
    else if(!startCell->getPiece().isValidMove(start, end) && startCell->getPiece().isValidCaptureMove(start, end)
            && endCell->getState() == ChessCellState::empty){
        throw ChessException{"Invalid capture move: cannot capture an empty cell " + startStr + " -> " + endStr};
    }
//    else if(!checkPieceMobility(start, end)){
//
//    }
}

bool StandardChessGameState::isValidMove(std::pair<int, int> start, std::pair<int, int> end) const {
    try{
        isValidMoveThrow(start, end, whiteTurn);
    }
    catch(ChessException& e){
        return false;
    }

    return true;
}

bool StandardChessGameState::isValidMoveForPlayer(std::pair<int, int> start, std::pair<int, int> end, bool isWhite) const {
    try{
        isValidMoveThrow(start, end, isWhite);
    }
    catch(ChessException& e){
        return false;
    }

    return true;
}

void StandardChessGameState::makeMove(std::pair<int, int> start, std::pair<int, int> end) {
    // Check the validity of the move, which will throw a ChessException upon failure with an error message, which is caught by the main game loop.
    isValidMoveThrow(start, end, whiteTurn);

    // TODO make points more meaningful
    if(_board->getCell(end.first, end.second)->getState() != ChessCellState::empty){
        std::string capturedName = _board->getCell(end.first, end.second)->getPiece().getName();

        if(whiteTurn){
            ++whitePoints;
            ++whiteCaptured[capturedName];
        }
        else{
            ++blackPoints;
            ++blackCaptured[capturedName];
        }
    }
    _board->movePiece(start, end);
    whiteTurn = !whiteTurn;
}

std::unique_ptr<ChessGameState> StandardChessGameState::clone() const {
    return std::make_unique<StandardChessGameState>(*this);
}

std::vector<std::pair<int, int>> StandardChessGameState::getValidPieceMoves(std::pair<int, int> start) const {
    std::shared_ptr<ChessCell> startCell = _board->getCell(start.first, start.second);
    bool isWhite = startCell->getPiece().isWhite();
    std::vector<std::pair<int, int>> result;

    for(const ChessPieceMobility& move : startCell->getPiece().getMoveSet()){
        if(move.type == Mobility::jump){
            std::pair<int, int> add = addPair(start, move.direction);
            if(isValidMoveForPlayer(start, addPair(start, move.direction), isWhite))
                result.push_back(addPair(start, move.direction));
        }
        else{
            std::pair<int, int> currPos{start};
            while(moveIsInBounds(currPos, _board->width(), _board->height())){
                currPos = addPair(currPos, move.direction);

                if(!moveIsInBounds(currPos, _board->width(), _board->height()))
                    break;

                if(isValidMoveForPlayer(start, currPos, isWhite))
                    result.push_back(currPos);

                if(_board->getCell(currPos.first, currPos.second)->getState() != ChessCellState::empty)
                    break;
            }
        }

    }

    return result;
}


bool StandardChessGameState::checkmateAchieved(bool forWhite) {
    std::pair<int, int> kingLoc;
    bool kingFound = false;

    for(int row = 0; row != _board->height() && !kingFound; ++row){
        for(int col = 0; col != _board->width() && !kingFound; ++col){
            if(_board->getCell(row, col)->getState() != ChessCellState::empty && _board->getCell(row, col)->getPiece().isWhite() == !forWhite &&
               _board->getCell(row, col)->getPiece().getName() == "King"){
                kingLoc = {row, col};
                kingFound = true;
            }
        }
    }

    std::vector<std::pair<int, int>> kingMoves = getValidPieceMoves(kingLoc);

    return false;
}


const std::unordered_map<std::string, int>& StandardChessGameState::getCapturedPieces(bool forWhite) const {
    return forWhite ? whiteCaptured : blackCaptured;
}

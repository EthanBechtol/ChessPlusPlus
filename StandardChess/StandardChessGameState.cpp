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
}

StandardChessGameState::StandardChessGameState(StandardChessBoard board)
    : whitePoints{0}, blackPoints{0}, whiteTurn{true}, gameOver{false} {
    _board = std::make_unique<StandardChessBoard>(std::move(board));
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

bool StandardChessGameState::isValidMove(std::pair<int, int> start, std::pair<int, int> end) {
    std::shared_ptr<ChessCell> startCell = _board->getCell(start.first, start.second);

    if(startCell->getState() == ChessCellState::empty)
        return false;
    else
        return (startCell->getPiece().isValidMove(start, end) || startCell->getPiece().isValidCaptureMove(start, end));
}

void StandardChessGameState::makeMove(std::pair<int, int> start, std::pair<int, int> end) {
    std::string startStr = '(' + std::to_string(start.first) + ", " + std::to_string(start.second) + ')';
    std::string endStr = '(' + std::to_string(end.first) + ", " + std::to_string(end.second) + ')';

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
    // If the starting cell is either empty or the piece at the cell cannot make the requested move, throw a ChessException.
    else if(!isValidMove(start, end)){
        //std::string endStr = '(' + std::to_string(end.first) + ", " + std::to_string(end.second) + ')';
        throw ChessException{"Invalid move: " + startStr + " -> " + endStr};
    }
    // If the piece at the requested position does not belong to the player requesting the move, throw a ChessException.
    else if((_board->getCell(start.first, start.second)->getPiece().isWhite() && !isWhiteTurn()) ||
            (_board->getCell(start.first, start.second)->getPiece().isBlack() && !isBlackTurn())){
        std::string currColor = isWhiteTurn() ? "white" : "black";
        throw ChessException{"Invalid move request. The piece at " + startStr + " does not belong to " + currColor};
    }
    else {
        // TODO check jump abilities
        std::shared_ptr<ChessCell> startCell = _board->getCell(start.first, start.second);
        std::shared_ptr<ChessCell> endCell = _board->getCell(end.first, end.second);

        if(endCell->getState() != ChessCellState::empty){
            // TODO increment points
            if(startCell->getPiece().hasCaptureMove()) {
                if (startCell->getPiece().isValidCaptureMove(start, end))
                    _board->movePiece(start, end);
                else
                    throw ChessException{"Invalid capture move: a " + startCell->getPiece().getName() +
                                         " cannot perform a capture from " + startStr + " -> " + endStr};
            }
            else
                _board->movePiece(start, end);
        }
        else
            if(startCell->getPiece().isValidMove(start, end))
                _board->movePiece(start, end);
            else
                throw ChessException{"Invalid capture move: cannot capture an empty cell " + startStr + " -> " + endStr};

        whiteTurn = !whiteTurn;
    }
}

std::unique_ptr<ChessGameState> StandardChessGameState::clone() const {
    // TODO implement cloning that DEEP copies the current state.
    return std::unique_ptr<ChessGameState>();
}

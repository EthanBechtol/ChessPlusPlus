//
// Created by Ethan on 3/11/20.
//

#include "StandardChessGameState.hpp"
#include "StandardChessBoard.hpp"
#include "../ChessGame/ChessException.hpp"

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
        return startCell->getPiece().isValidMove(start, end);
}

void StandardChessGameState::makeMove(std::pair<int, int> start, std::pair<int, int> end) {
    std::string startStr = std::to_string(start.first) + ", " + std::to_string(start.second);

    // If the starting cell is either empty or the piece at the cell cannot make the requested move, throw a ChessException.
    if(!isValidMove(start, end)){
        std::string endStr = std::to_string(end.first) + ", " + std::to_string(end.second);
        throw ChessException{"Invalid move: " + startStr + "->" + endStr};
    }
    // If the piece at the requested position does not belong to the player requesting the move, throw a ChesException.
    else if((_board->getCell(start.first, start.second)->getPiece().isWhite() && !isWhiteTurn()) ||
            (_board->getCell(start.first, start.second)->getPiece().isBlack() && !isBlackTurn())){
        std::string currColor = isWhiteTurn() ? "white" : "black";
        throw ChessException{"Invalid move request. The piece at " + startStr + " does not belong to " + currColor};
    }
    else {
        // TODO different moves are allowed depending on whether or not a piece is being taken! -> pawns
        std::shared_ptr<ChessCell> endCell = _board->getCell(end.first, end.second);
        if(endCell->getState() != ChessCellState::empty){
            // TODO increment points
        }
        _board->movePiece(start, end);
        whiteTurn = !whiteTurn;
    }
}

std::unique_ptr<ChessGameState> StandardChessGameState::clone() const {
    // TODO implement cloning that DEEP copies the current state.
    return std::unique_ptr<ChessGameState>();
}

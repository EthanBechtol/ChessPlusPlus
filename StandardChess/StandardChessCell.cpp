//
// Created by Ethan on 2/26/20.
//

#include "StandardChessCell.hpp"
#include "../ChessGame/ChessCellState.hpp"

StandardChessCell::StandardChessCell() {
    piece = nullptr;
    state = ChessCellState::empty;
}

ChessCellState StandardChessCell::getState() const {
    return state;
}

ChessPiece& StandardChessCell::getPiece() const {
    return *piece;
}

std::unique_ptr<ChessPiece>& StandardChessCell::getPiecePtr() {
    return piece;
}

void StandardChessCell::setPiece(std::unique_ptr<ChessPiece> chessPiece) {
    piece = std::move(chessPiece);
    if(piece != nullptr){
        state = piece->isWhite() ? ChessCellState::white : ChessCellState::black;
    }
    else {
        state = ChessCellState::empty;
    }
}



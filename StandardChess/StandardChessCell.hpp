//
// Created by Ethan on 2/26/20.
//

#ifndef CHESSPLUSPLUS_STANDARDCHESSCELL_HPP
#define CHESSPLUSPLUS_STANDARDCHESSCELL_HPP


#include "../ChessGame/ChessCell.hpp"

class StandardChessCell : public ChessCell {
public:
    StandardChessCell();

    // getState() returns the state of this cell (i.e. empty, black, white, etc.)
    ChessCellState getState() const override;

    // getPiece() returns the piece occupying the cell.
    ChessPiece& getPiece() const override;

    std::unique_ptr<ChessPiece>& getPiecePtr() override;

    // setPiece() sets piece occupying this cell to the one given.
    void setPiece(std::unique_ptr<ChessPiece> chessPiece) override;
};


#endif //CHESSPLUSPLUS_STANDARDCHESSCELL_HPP

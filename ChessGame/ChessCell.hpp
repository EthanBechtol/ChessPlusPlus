//
// Created by Ethan on 2/24/20.
//

#ifndef CHESSPLUSPLUS_CHESSCELL_HPP
#define CHESSPLUSPLUS_CHESSCELL_HPP

#include "ChessCellState.hpp"
#include "ChessPiece.hpp"

class ChessCell {
public:
    virtual ~ChessCell() = default;

    // getState() returns the state of this cell (i.e. empty, black, white, etc.)
    virtual ChessCellState getState() const { return state; };

    // getPiece() returns the piece occupying the cell.
    virtual ChessPiece& getPiece() const = 0;

    virtual std::unique_ptr<ChessPiece>& getPiecePtr() = 0;

    // setPiece() sets piece occupying this cell to the one given.
    virtual void setPiece(std::unique_ptr<ChessPiece> piece) = 0;

protected:
    std::unique_ptr<ChessPiece> piece;
    ChessCellState state;
};


#endif //CHESSPLUSPLUS_CHESSCELL_HPP

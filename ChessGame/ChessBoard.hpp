//
// Created by Ethan on 2/24/20.
//

#ifndef CHESSPLUSPLUS_CHESSBOARD_HPP
#define CHESSPLUSPLUS_CHESSBOARD_HPP

#include "ChessCell.hpp"

class ChessBoard {
public:
    virtual ~ChessBoard() = default;

    virtual int width() const noexcept = 0;

    virtual int height() const noexcept = 0;

    virtual bool isValidCell(int row, int col) const noexcept = 0;

    virtual std::shared_ptr<ChessCell> getCell(int row, int col) = 0;
    virtual std::shared_ptr<const ChessCell> getCell(int row, int col) const = 0;

    // setCell() forcefully sets the cell at the given position to have the parameters
    // of the given ChessCell
    virtual void setCell(int row, int col, ChessCell cell) = 0;

    // movePiece() attempts to move a piece from one cell to another. The function
    // will NOT check that it is valid to do so, only that it will not overwrite
    // another piece. If the cell is already occupied, a ChessException is thrown.
    virtual void movePiece(std::pair<int, int> start, std::pair<int, int> end) = 0;

    // outputBoard() is a temporary function used to print the current board out to a stream
    // currently used for debugging purposes.
    virtual void outputBoard(std::ostream& stream) const = 0;
};


#endif //CHESSPLUSPLUS_CHESSBOARD_HPP

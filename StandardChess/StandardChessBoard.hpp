//
// Created by Ethan on 2/24/20.
//

#ifndef CHESSPLUSPLUS_STANDARDCHESSBOARD_HPP
#define CHESSPLUSPLUS_STANDARDCHESSBOARD_HPP

#include <vector>
#include "../ChessGame/ChessBoard.hpp"
#include "StandardChessCell.hpp"

class StandardChessBoard : public ChessBoard {
public:
    // Constructs a StandardChessBoard optionally empty using initCells, which initializes
    // the chess board as an 8x8 with a standard piece layout unless initCells is set to
    // false in which case the cells will be empty.
    explicit StandardChessBoard(bool initCells = true);

    // Constructs a StandardChessBoard of a custom width and height of empty ChessCells.
    StandardChessBoard(int width, int height);

    // Constructs a StandardChessBoard from an expiring one.
    StandardChessBoard(StandardChessBoard&& b);

    // width() returns the width of the Chess board.
    int width() const noexcept override;

    // height() returns the height of the Chess board.
    int height() const noexcept override;

    // isValidCell returns true if the given (x,y) coordinates are within the bounds
    // of the chess board (i.e. 0 <= x <= width-1 & 0 <= y <= height-1), and false otherwise.
    bool isValidCell(int row, int col) const noexcept override;

    // getCell() returns the a shared pointer for the ChessCell at the given (x, y) coordinates.
    std::shared_ptr<ChessCell> getCell(int row, int col) override;
    std::shared_ptr<const ChessCell> getCell(int row, int col) const override;

    // setCell() changes the contents of the ChessCell at the given (x, y) coordinates
    // to be that of the given cell parameter. NOTE: no error checking is done here.
    void setCell(int row, int col, ChessCell cell) override;

    // movePiece() moves the piece residing at the source (x, y) coordinate pair to the
    // ChessCell at the destination (x, y) coordinate pair. NOTE: no error checking is done here.
    void movePiece(std::pair<int, int> start, std::pair<int, int> dst) override;


    // outputBoard() is a temporary function used to print the current board out to a stream
    // currently used for debugging purposes.
    void outputBoard(std::ostream& stream) const override;

private:
    std::vector<std::vector<std::shared_ptr<StandardChessCell>>> cells;
    int _width;
    int _height;

    // initEmptyCells() initializes the cells of the chess board to be empty.
    void initEmptyCells();

    // initStandardLayout() initializes the cells of the chess board with the standard piece layout.
    void initStandardLayout();
};


#endif //CHESSPLUSPLUS_STANDARDCHESSBOARD_HPP

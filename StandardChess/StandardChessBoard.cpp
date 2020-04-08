//
// Created by Ethan on 2/24/20.
//

#include <iostream>
#include "StandardChessBoard.hpp"
#include "../ChessGame/ChessException.hpp"
#include "StandardChessCell.hpp"
#include "StandardChessPieces/Pawn.hpp"
#include "StandardChessPieces/Rook.hpp"
#include "StandardChessPieces/Knight.hpp"
#include "StandardChessPieces/Bishop.hpp"
#include "StandardChessPieces/King.hpp"
#include "StandardChessPieces/Queen.hpp"

StandardChessBoard::StandardChessBoard(int width, int height)
    : cells{std::vector<std::vector<std::shared_ptr<StandardChessCell>>>(height, std::vector<std::shared_ptr<StandardChessCell>>(width))},
      _width{width}, _height{height} {
    initEmptyCells();
}

StandardChessBoard::StandardChessBoard(bool initCells)
    : cells{std::vector<std::vector<std::shared_ptr<StandardChessCell>>>(8, std::vector<std::shared_ptr<StandardChessCell>>(8))},
      _width{8}, _height{8} {
    initEmptyCells();

    if(initCells){
        initStandardLayout();
    }
}


StandardChessBoard::StandardChessBoard(StandardChessBoard&& b): _width{0}, _height{0} {
    std::swap(cells, b.cells);
    std::swap(_width, b._width);
    std::swap(_height, b._height);
}

void StandardChessBoard::initEmptyCells(){
    for(int row = 0; row != _height; ++row){
        for(int col = 0; col != _width; ++col){
            cells[row][col] = std::make_shared<StandardChessCell>();
        }
    }
}

void StandardChessBoard::initStandardLayout() {
    // Set rows 1 & 6 to be pawns
    for(int col = 0; col != _width; ++col){
        cells[1][col]->setPiece(std::make_unique<Pawn>(false));
    }
    for(int col = 0; col != _width; ++col){
        cells[6][col]->setPiece(std::make_unique<Pawn>(true));
    }

    // Set Rooks
    cells[0][0]->setPiece(std::make_unique<Rook>(false));
    cells[0][7]->setPiece(std::make_unique<Rook>(false));
    cells[7][0]->setPiece(std::make_unique<Rook>(true));
    cells[7][7]->setPiece(std::make_unique<Rook>(true));

    // Set Knights
    cells[0][1]->setPiece(std::make_unique<Knight>(false));
    cells[0][6]->setPiece(std::make_unique<Knight>(false));
    cells[7][1]->setPiece(std::make_unique<Knight>(true));
    cells[7][6]->setPiece(std::make_unique<Knight>(true));

    // Set Bishops
    cells[0][2]->setPiece(std::make_unique<Bishop>(false));
    cells[0][5]->setPiece(std::make_unique<Bishop>(false));
    cells[7][2]->setPiece(std::make_unique<Bishop>(true));
    cells[7][5]->setPiece(std::make_unique<Bishop>(true));

    // Set Kings
    cells[0][3]->setPiece(std::make_unique<King>(false));
    cells[7][3]->setPiece(std::make_unique<King>(true));

    // Set Queens
    cells[0][4]->setPiece(std::make_unique<Queen>(false));
    cells[7][4]->setPiece(std::make_unique<Queen>(true));
}


int StandardChessBoard::width() const noexcept {
    return _width;
}

int StandardChessBoard::height() const noexcept {
    return _height;
}

bool StandardChessBoard::isValidCell(int row, int col) const noexcept {
    return 0 <= row && row < _height && 0 <= col && col < _width;
}

std::shared_ptr<ChessCell> StandardChessBoard::getCell(int row, int col) {
    if(!isValidCell(row, col))
        throw ChessException("Invalid cell coordinates: " + std::to_string(row) + ", " + std::to_string(col));

    return cells[row][col];
}

std::shared_ptr<const ChessCell> StandardChessBoard::getCell(int row, int col) const {
    if(!isValidCell(row, col))
        throw ChessException("Invalid cell coordinates: " + std::to_string(row) + ", " + std::to_string(col));

    return cells[row][col];
}

void StandardChessBoard::setCell(int row, int col, ChessCell cell) {

}

void StandardChessBoard::movePiece(std::pair<int, int> start, std::pair<int, int> dst) {
    cells[dst.first][dst.second]->setPiece(std::move(cells[start.first][start.second]->getPiecePtr()));
    cells[start.first][start.second]->setPiece(nullptr);
}

void StandardChessBoard::outputBoard(std::ostream& stream) const {
    for(int row = -1; row != _height; ++row){
        for(int col = -1; col != _width; ++col){
            if(row == -1 && col != -1){
                stream << col << "  ";
            }
            else if(col == -1){
                if(row != -1)
                    stream << row << " ";
                else
                    stream << "  ";
            }
            else{
                if(cells[row][col]->getState() != ChessCellState::empty) {
                    char color = cells[row][col]->getPiece().isWhite() ? 'w' : 'b';
                    stream << cells[row][col]->getPiece().getName()[0] << color << " ";
                }
                else
                    stream << "-- ";
            }
        }
        stream << '\n';
    }
}

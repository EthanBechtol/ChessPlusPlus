//
// Created by Ethan on 2/27/20.
//

#ifndef CHESSPLUSPLUS_KNIGHT_HPP
#define CHESSPLUSPLUS_KNIGHT_HPP


#include "../../ChessGame/ChessPiece.hpp"

class Knight : public ChessPiece {
public:
    Knight();
    explicit Knight(bool isWhite);

    bool isValidMove(std::pair<int, int> start, std::pair<int, int> end) const override;
};


#endif //CHESSPLUSPLUS_KNIGHT_HPP

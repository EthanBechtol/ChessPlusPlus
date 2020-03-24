//
// Created by Ethan on 2/27/20.
//

#ifndef CHESSPLUSPLUS_BISHOP_HPP
#define CHESSPLUSPLUS_BISHOP_HPP


#include "../../ChessGame/ChessPiece.hpp"

class Bishop : public ChessPiece {
public:
    Bishop();
    explicit Bishop(bool isWhite);

    bool isValidMove(std::pair<int, int> start, std::pair<int, int> end) const override;
};


#endif //CHESSPLUSPLUS_BISHOP_HPP

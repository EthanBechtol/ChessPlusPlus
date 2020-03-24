//
// Created by Ethan on 2/27/20.
//

#ifndef CHESSPLUSPLUS_KING_HPP
#define CHESSPLUSPLUS_KING_HPP


#include "../../ChessGame/ChessPiece.hpp"

class King : public ChessPiece {
public:
    King();
    explicit King(bool isWhite);

    bool isValidMove(std::pair<int, int> start, std::pair<int, int> end) const override;
};


#endif //CHESSPLUSPLUS_KING_HPP

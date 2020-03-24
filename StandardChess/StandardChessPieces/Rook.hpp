//
// Created by Ethan on 2/27/20.
//

#ifndef CHESSPLUSPLUS_ROOK_HPP
#define CHESSPLUSPLUS_ROOK_HPP


#include "../../ChessGame/ChessPiece.hpp"

class Rook : public ChessPiece {
public:
    Rook();
    explicit Rook(bool isWhite);

    bool isValidMove(std::pair<int, int> start, std::pair<int, int> end) const override;
};


#endif //CHESSPLUSPLUS_ROOK_HPP

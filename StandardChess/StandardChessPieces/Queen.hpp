//
// Created by Ethan on 2/27/20.
//

#ifndef CHESSPLUSPLUS_QUEEN_HPP
#define CHESSPLUSPLUS_QUEEN_HPP


#include "../../ChessGame/ChessPiece.hpp"

class Queen : public ChessPiece {
public:
    Queen();
    explicit Queen(bool isWhite);

    bool isValidMove(std::pair<int, int> start, std::pair<int, int> end) const override;
};


#endif //CHESSPLUSPLUS_QUEEN_HPP

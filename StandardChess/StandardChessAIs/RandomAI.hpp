//
// Created by Ethan on 3/27/20.
//

#ifndef CHESSPLUSPLUS_RANDOMAI_HPP
#define CHESSPLUSPLUS_RANDOMAI_HPP

#include <random>
#include "../../ChessGame/ChessAI.hpp"

class RandomAI : ChessAI {
public:
    ChessMove choseMove(const ChessGameState& state) override;
};


#endif //CHESSPLUSPLUS_RANDOMAI_HPP

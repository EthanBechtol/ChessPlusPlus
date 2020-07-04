//
// Created by Ethan on 3/27/20.
//

#ifndef CHESSPLUSPLUS_RANDOMAI_HPP
#define CHESSPLUSPLUS_RANDOMAI_HPP

#include <random>
#include "../../ChessGame/ChessAI.hpp"

class RandomAI : public ChessAI {
public:
    const static std::string AIName;
    const static std::string AIDesc;

    ChessMove choseMove(const ChessGameState& state) override;

    RandomAI* clone() const override;

    const std::string& name() const override { return AIName; };
    const std::string& description() const override { return AIDesc; };
};


#endif //CHESSPLUSPLUS_RANDOMAI_HPP

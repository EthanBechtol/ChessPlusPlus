//
// Created by Ethan on 4/28/20.
//

#ifndef CHESSPLUSPLUS_MINMAXAI_HPP
#define CHESSPLUSPLUS_MINMAXAI_HPP


#include "../../ChessGame/ChessAI.hpp"

class MinMaxAI : public ChessAI {
public:
    /*
     * OPTIONS:
     *  - MAX_DEPTH: the maximum depth the AI will recurse in exploring possible move options.
     *  - (DISABLED) ENABLE_MULTI_THREADING: allows this AI to use multi-threading to explore move options in parallel, thus reducing runtime.
     *  - ENABLE_ALPHA_BETA_PRUNING: allows the AI to make use of alpha-beta pruning to reduce the runtime of its move search by eliminating "loss" branches.
     */
    static constexpr unsigned short MAX_DEPTH = 2;
    static constexpr bool ENABLE_MULTI_THREADING = false;
    static constexpr bool ENABLE_ALPHA_BETA_PRUNING = false;

    const static std::string AIName;
    const static std::string AIDesc;

    ChessMove choseMove(const ChessGameState& state) override;

    const std::string& name() const override { return AIName; };
    const std::string& description() const override { return AIDesc; };
};


#endif //CHESSPLUSPLUS_MINMAXAI_HPP
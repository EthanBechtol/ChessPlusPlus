//
// Created by Ethan on 4/28/20.
//

#ifndef CHESSPLUSPLUS_MINMAXAI_HPP
#define CHESSPLUSPLUS_MINMAXAI_HPP


#include <thread>
#include "../../ChessGame/ChessAI.hpp"

class MinMaxAI : public ChessAI {
private:
    /*
     * OPTIONS:
     *  - MAX_DEPTH: the maximum depth the AI will recurse in exploring possible move options.
     *  - ENABLE_MULTI_THREADING: allows this AI to use multi-threading to explore move options in parallel, thus reducing runtime.
     *  - MAX_THREADS: determines how many threads can be created during multi-threaded calls.
     *  - ENABLE_ALPHA_BETA_PRUNING: allows the AI to make use of alpha-beta pruning to reduce the runtime of its move search by eliminating "loss" branches.
     */
    unsigned short MAX_DEPTH = 2;
    bool ENABLE_MULTI_THREADING = true;
    unsigned short MAX_THREADS = 12;
    bool ENABLE_ALPHA_BETA_PRUNING = true;

    static constexpr unsigned short DEFAULT_MAX_DEPTH = 2;
    static constexpr bool DEFAULT_ENABLE_MULTI_THREADING = true;
    static constexpr unsigned short DEFAULT_MAX_THREADS = 12;
    static constexpr bool DEFAULT_ENABLE_ALPHA_BETA_PRUNING = true;

public:
    const static std::string AIName;
    const static std::string AIDesc;

    MinMaxAI();
    MinMaxAI(unsigned short maxDepth, bool enableMultiThread, unsigned short maxThreads, bool enableAlphaBetaPrune);

    ChessMove choseMove(const ChessGameState& state) override;
    MinMaxAI* clone() const override;

    const std::string& name() const override { return AIName; };
    const std::string& description() const override { return AIDesc; };

private:
    std::mutex scoringMutex;

    ChessMove MTChooseMove(const ChessGameState& state);
    void MTSearchHelper(const ChessGameState& state, const std::vector<ChessMove>& moveQueue, int& maxScore, ChessMove& bestMove, bool isWhiteAI);
};


#endif //CHESSPLUSPLUS_MINMAXAI_HPP


#ifndef CHESSPLUSPLUS_ITERATIVEDEEPENINGAI_HPP
#define CHESSPLUSPLUS_ITERATIVEDEEPENINGAI_HPP


#include <chrono>
#include "../../ChessGame/ChessAI.hpp"

class IterativeDeepeningAI : public ChessAI {
private:
    /*
 * OPTIONS:
 *  - ENABLE_MULTI_THREADING: allows this AI to use multi-threading to explore move options in parallel, thus reducing runtime.
 *  - MAX_THREADS: determines how many threads can be created during multi-threaded calls.
 *  - ENABLE_ALPHA_BETA_PRUNING: allows the AI to make use of alpha-beta pruning to reduce the runtime of its move search by eliminating "loss" branches.
 */
    bool ENABLE_MULTI_THREADING = true;
    unsigned short MAX_THREADS = std::thread::hardware_concurrency();
    bool ENABLE_ALPHA_BETA_PRUNING = true;

public:
    const static std::string AIName;
    const static std::string AIDesc;

    IterativeDeepeningAI();
    explicit IterativeDeepeningAI(int msTimeLimit);

    ChessMove choseMove(const ChessGameState &state) override;
    IterativeDeepeningAI* clone() const override;

    const std::string& name() const override { return AIName; };
    const std::string& description() const override { return AIDesc; };

private:
    // timeLimit is how long the AI is allowed to spend choosing a move in milliseconds.
    int timeLimit = 800;

    // scoringMutex is used by the multi-threaded version of this AI when updating the current best known branch score.
    std::mutex scoringMutex;

    // Multi-threaded version of chooseMove.
    ChessMove MTChooseMove(const ChessGameState &state);
    void MTSearchHelper(const ChessGameState &state, const std::vector<ChessMove> &moveQueue, int &maxScore,
                        ChessMove &bestMove, bool isWhiteAI, int searchDepth, std::chrono::time_point<std::chrono::steady_clock>& cutoffTime);
};


#endif //CHESSPLUSPLUS_ITERATIVEDEEPENINGAI_HPP

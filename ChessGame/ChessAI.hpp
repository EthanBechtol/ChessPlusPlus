//
// Created by Ethan on 2/24/20.
//

#ifndef CHESSPLUSPLUS_CHESSAI_HPP
#define CHESSPLUSPLUS_CHESSAI_HPP


#include <utility>
#include "ChessGameState.hpp"
#include "ChessMove.hpp"

// A ChessAI is currently intended to be a *stateless* class that may be constructed and called upon at any time to make
// a move given solely the current state of the game in the form of a ChessGameState.

class ChessAI {
public:
    virtual ~ChessAI() = default;

    // choseMove() returns the best move this AI believes is the best. With that move, the game manager will make update
    // the current game state to reflect the move returned by this function. It is assumed that this function will only
    // be called upon when there is a move to make.
    virtual ChessMove choseMove(const ChessGameState& state) = 0;
};


#endif //CHESSPLUSPLUS_CHESSAI_HPP

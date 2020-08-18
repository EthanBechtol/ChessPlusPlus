//
// Created by Ethan on 7/3/20.
//

#ifndef CHESSPLUSPLUS_CHESSGAMEMANAGER_HPP
#define CHESSPLUSPLUS_CHESSGAMEMANAGER_HPP


#include "ChessGameState.hpp"
#include "../Input/InputReader.hpp"
#include "ChessGameStateFactory.hpp"


class ChessGameManager {
public:
    ChessGameManager();

    // run() begins the chess game loop. Each player is queried for move requests until an endgame condition is reached.
    void run();

private:
    ChessGameStateFactory stateFactory;
    std::unique_ptr<ChessGameState> gameState;
    InputReader* player1;
    InputReader* player2;
};


#endif //CHESSPLUSPLUS_CHESSGAMEMANAGER_HPP

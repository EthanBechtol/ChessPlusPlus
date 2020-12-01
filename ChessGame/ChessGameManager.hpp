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

    // setPlayer() sets either player 1 or 2 to be a new InputReader*. This function returns true if the assignment was
    // successful and false otherwise.
    bool setPlayer(int playerNumber, InputReader* newPlayer);

    ~ChessGameManager();

private:
    ChessGameStateFactory stateFactory;
    std::unique_ptr<ChessGameState> gameState;
    InputReader* player1;
    InputReader* player2;
};


#endif //CHESSPLUSPLUS_CHESSGAMEMANAGER_HPP

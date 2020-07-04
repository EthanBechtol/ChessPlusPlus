//
// Created by Ethan on 2/24/20.
//

#ifndef CHESSPLUSPLUS_CHESSGAMESTATEFACTORY_HPP
#define CHESSPLUSPLUS_CHESSGAMESTATEFACTORY_HPP


#include <memory>
#include "ChessGameState.hpp"

enum GameStateType {
    standard
};

class ChessGameStateFactory {
public:
    // makeNewGameState() generates a new game state and returns it as a unique_ptr.
    // For the moment, this will just generate a standard game setup.
    std::unique_ptr<ChessGameState> makeNewGameState(GameStateType gameType);

    //std::unique_ptr<ChessGameState> makeNewGameState(int width, int height);

    //std::unique_ptr<ChessGameState> makeGameState(int width, int height, bool isGameOver,
    //       bool isWhiteTurn, const std::vector<ChessCell>& cells);
};


#endif //CHESSPLUSPLUS_CHESSGAMESTATEFACTORY_HPP

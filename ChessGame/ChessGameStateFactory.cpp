//
// Created by Ethan on 2/24/20.
//

#include "ChessGameStateFactory.hpp"



std::unique_ptr<ChessGameState> ChessGameStateFactory::makeNewGameState(unsigned int gameType) {
    std::unique_ptr<ChessGameState> state = nullptr;
    switch(gameType){
        case 0:
            // TODO return standard game state
            // Return a fresh standard chess game state (filled)
            break;
        default:

            break;
    }

    return state;
}

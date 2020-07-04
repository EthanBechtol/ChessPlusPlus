//
// Created by Ethan on 2/24/20.
//

#include "ChessGameStateFactory.hpp"
#include "../StandardChess/StandardChessBoard.hpp"
#include "../StandardChess/StandardChessGameState.hpp"


std::unique_ptr<ChessGameState> ChessGameStateFactory::makeNewGameState(GameStateType gameType) {
    std::unique_ptr<ChessGameState> state = nullptr;
    switch(gameType){
        // Return a fresh standard chess game state (filled)
        case standard:
            state = std::make_unique<StandardChessGameState> (std::move(StandardChessBoard()));
            break;

        default:
            break;
    }

    return state;
}

//
// Created by Ethan on 7/3/20.
//

#include <iostream>
#include <sstream>
#include <chrono>
#include "ChessGameManager.hpp"
#include "../Input/InputReaderAI.hpp"
#include "../StandardChess/StandardChessAIs/RandomAI.hpp"
#include "../StandardChess/StandardChessAIs/MinMaxAI.hpp"

namespace {
    ChessMove lineToMove(std::istringstream& line){
        ChessMove move;

        line >> move.start.first >> move.start.second >> move.end.first >> move.end.second;
        return move;
    }

    template<typename T1, typename T2>
    std::string pairToStr(const std::pair<T1, T2>& pair) {
        return "(" + std::to_string(pair.first) + ", " + std::to_string(pair.second) + ")";
    }

    void printPairVector(const std::vector<std::pair<int, int>>& v){
        for(const std::pair<int, int>& p : v){
            std::cout << "\t" << p.first << ", " << p.second << "\n";
        }
        std::cout << std::endl;
    }
}


ChessGameManager::ChessGameManager(): gameState{stateFactory.makeNewGameState(GameStateType::standard)} {
    RandomAI randomAI;
    MinMaxAI minMaxAI(2, true, 12, true);
    player1 = new InputReaderAI(randomAI);
    player2 = new InputReaderAI(minMaxAI);
}

void ChessGameManager::run() {
    while(gameState->whiteScore() < 10 && gameState->blackScore() < 10){
        InputRequest playerRequest;
        std::string AIName;

        std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
        if(gameState->isWhiteTurn()) {
            playerRequest = player1->getInput(*gameState);

        }
        else {
            playerRequest = player2->getInput(*gameState);
        }

        std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::milli> elapsedTime = endTime - startTime;
        //std::chrono::steady_clock::duration elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);

        std::cout << playerRequest.requester << " chose move: " + pairToStr(playerRequest.moveRequest.start) + " -> " + pairToStr(playerRequest.moveRequest.end) << " in " << elapsedTime.count() << "ms" << std::endl;

        if(playerRequest.requestType == RequestType::move){
            gameState->makeMove(playerRequest.moveRequest.start, playerRequest.moveRequest.end);
            gameState->board().outputBoard(std::cout);
        }
    }
}

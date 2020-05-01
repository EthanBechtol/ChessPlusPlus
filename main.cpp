#include <iostream>
#include <chrono>
#include "StandardChess/StandardChessBoard.hpp"
#include "StandardChess/StandardChessGameState.hpp"
#include "ChessGame/ChessMove.hpp"
#include "ChessGame/ChessException.hpp"
#include "StandardChess/StandardChessAIs/RandomAI.hpp"
#include "StandardChess/StandardChessAIs/MinMaxAI.hpp"


template<typename T1, typename T2>
std::string pairToStr(const std::pair<T1, T2>& pair) {
    return "(" + std::to_string(pair.first) + ", " + std::to_string(pair.second) + ")";
}


int main() {
    StandardChessBoard board;
    StandardChessGameState gameState(std::move(board));


    // Proof of concept Min/Max AI showcase vs Random AI
    while(gameState.whiteScore() < 10 && gameState.blackScore() < 10){
        std::string AIName;
        ChessMove AIMove;

        std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
        if(gameState.isWhiteTurn()) {
            RandomAI ai;
            AIName = ai.AIName;
            AIMove = ai.choseMove(gameState);
        }
        else {
            MinMaxAI ai;
            AIName = ai.AIName;
            AIMove = ai.choseMove(gameState);
        }
        std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::milli> elapsedTime = endTime - startTime;

        std::cout << AIName << " chose move: " + pairToStr(AIMove.start) + " -> " + pairToStr(AIMove.end) << " in " << elapsedTime.count() << "ms" << std::endl;
        gameState.makeMove(AIMove.start, AIMove.end);
        gameState.board().outputBoard(std::cout);
    }

    return 0;
}
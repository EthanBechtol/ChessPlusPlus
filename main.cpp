#include <iostream>
#include <sstream>
#include "StandardChess/StandardChessBoard.hpp"
#include "StandardChess/StandardChessGameState.hpp"
#include "ChessGame/ChessMove.hpp"


ChessMove lineToMove(std::istringstream& line){
    ChessMove move;

    line >> move.start.first >> move.start.second >> move.end.first >> move.end.second;
    return move;
}

int main() {
    StandardChessBoard board;
//    board.outputBoard(std::cout);

    StandardChessGameState gameState(std::move(board));

    std::string line;

    gameState.board().outputBoard(std::cout);
    std::getline(std::cin, line);
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while(line.rfind("quit") != 0){
        std::istringstream input(line);
        ChessMove requestedMove = lineToMove(input);

        gameState.makeMove(requestedMove.start, requestedMove.end);

        gameState.board().outputBoard(std::cout);
        std::getline(std::cin, line);
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // TODO IMPORTANT StdChessGameState ->
    //  different moves are allowed depending on whether or not a piece is being taken.
    //  AND whether or not they are allowed to take that piece (i.e. white can't take white)

    return 0;
}
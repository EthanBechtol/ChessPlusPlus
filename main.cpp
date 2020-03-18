#include <iostream>
#include "StandardChess/StandardChessBoard.hpp"
#include "StandardChess/StandardChessGameState.hpp"

int main() {
    StandardChessBoard board;
//    board.outputBoard(std::cout);

    StandardChessGameState gameState(std::move(board));
    gameState.board().outputBoard(std::cout);
    gameState.makeMove({6, 0}, {4, 0});
    gameState.board().outputBoard(std::cout);

    // TODO IMPORTANT StdChessGameState ->
    //  different moves are allowed depending on whether or not a piece is being taken.
    //  AND whether or not they are allowed to take that piece (i.e. white can't take white)

    return 0;
}
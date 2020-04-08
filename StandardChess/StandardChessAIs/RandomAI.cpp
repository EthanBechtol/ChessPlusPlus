//
// Created by Ethan on 3/27/20.
//

#include <algorithm>
#include <random>
#include "RandomAI.hpp"
#include "../../ChessGame/ChessAIException.hpp"


ChessMove RandomAI::choseMove(const ChessGameState& state) {
    static std::random_device device;
    static std::default_random_engine engine{device()};

    bool AIisWhite = state.isWhiteTurn();
    const ChessBoard& board = state.board();
    std::vector<std::pair<int, int>> pieces;

    for(int row = 0; row != board.height(); ++row){
        for(int col = 0; col != board.width(); ++col){
            if(state.board().getCell(row, col)->getState() != ChessCellState::empty && state.board().getCell(row, col)->getPiece().isWhite() == AIisWhite){
                if(!state.getValidPieceMoves({row, col}).empty())
                    pieces.emplace_back(row, col);
            }
        }
    }

    if(pieces.empty()){
        throw ChessAIException{"Could not find any pieces to move."};
    }

    ChessMove result;

    std::uniform_int_distribution<int> pieceSelector{0, static_cast<int>(pieces.size()-1)};
    result.start = pieces[pieceSelector(engine)];

    std::vector<std::pair<int, int>> possibleMoves = state.getValidPieceMoves(result.start);
    std::uniform_int_distribution<int> moveSelector{0, static_cast<int>(possibleMoves.size()-1)};
    result.end = possibleMoves[moveSelector(engine)];

    return result;

    //return std::pair<int, int>();
}

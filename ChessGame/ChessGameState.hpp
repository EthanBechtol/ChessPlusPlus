//
// Created by Ethan on 2/24/20.
//

#ifndef CHESSPLUSPLUS_CHESSGAMESTATE_HPP
#define CHESSPLUSPLUS_CHESSGAMESTATE_HPP


#include "ChessBoard.hpp"

class ChessGameState {
public:
    virtual ~ChessGameState() = default;

    // board() returns a const reference to a ChessBoard containing the layout of the board
    // in the specific game state.
    virtual const ChessBoard& board() const noexcept = 0;

    // whiteScore() and blackScore() return the current white or black score respectively
    // as defined by the specific game state.
    virtual int whiteScore() const noexcept = 0;
    virtual int blackScore() const noexcept = 0;

    // isGameOver() returns true if the game is over as defined by the specific game state,
    // and false otherwise (i.e. in a standard game by reaching a checkmate.)
    virtual bool isGameOver() const noexcept = 0;

    // isWhiteTurn() and isBlackTurn() return true if it is the white or black player's turn
    // respectively, and false otherwise.
    virtual bool isWhiteTurn() const noexcept = 0;
    virtual bool isBlackTurn() const noexcept = 0;

    // isValidMove() returns true if the piece at start<x, y> can validly move to end<x, y>,
    // and false otherwise.
    virtual bool isValidMove(std::pair<int, int> start, std::pair<int, int> end) = 0;

    // makeMove() makes a move on behalf of the current player with the chess piece
    // at cell start<x, y> ending at end<x,y>. If the move is invalid either by not being
    // a move that piece can make, or by not belonging to the player, a ChessException
    // is thrown.
    virtual void makeMove(std::pair<int, int> start, std::pair<int, int> end) = 0;

    // clone() returns a unique_ptr copy of the current game state.
    // Generally intended for use by an AI to simulate moves.
    virtual std::unique_ptr<ChessGameState> clone() const = 0;

protected:
    std::unique_ptr<ChessBoard> _board;
};


#endif //CHESSPLUSPLUS_CHESSGAMESTATE_HPP

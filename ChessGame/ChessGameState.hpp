//
// Created by Ethan on 2/24/20.
//

#ifndef CHESSPLUSPLUS_CHESSGAMESTATE_HPP
#define CHESSPLUSPLUS_CHESSGAMESTATE_HPP


#include <unordered_map>
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
    virtual bool isValidMove(std::pair<int, int> start, std::pair<int, int> end) const = 0;

    // makeMove() makes a move on behalf of the current player with the chess piece
    // at cell start<x, y> ending at end<x,y>. If the move is invalid either by not being
    // a move that piece can make, or by not belonging to the player, a ChessException
    // is thrown.
    virtual void makeMove(std::pair<int, int> start, std::pair<int, int> end) = 0;

    // undoMove returns the current game state to <amount> moves in the past undoing any moves either player made along
    // the way. If the <amount> parameter is greater than the number of undo moves stored, a ChessException is thrown.
    virtual void undoMove(unsigned int amount) = 0;

    // undoMove returns the current game state to <amount> moves in the future redoing any moves undone via calling
    // undoMove(). If the <amount> parameter is greater than the number of redo moves stored, a ChessException is thrown.
    // If there are moves stored on the redo stack and a new move is made, the redo stack is completely cleared.
    virtual void redoMove(unsigned int amount) = 0;

    // clone() returns a unique_ptr copy of the current game state.
    // Generally intended for use by an AI to simulate moves.
    virtual std::unique_ptr<ChessGameState> clone() const = 0;

    // getValidPieceMoves() returns a vector of valid coordinates to which the piece at the given start coordinates
    // could move to.
    virtual std::vector<std::pair<int, int>> getValidPieceMoves(std::pair<int, int> start) const = 0;

    // getCapturedPieces() returns and unordered_map of <piece name, amount> for which either white or black has taken throughout
    // the course of the game. For example, an output for which forWhite=true and white has taken two pawns and a knight
    // would look as follows: { {"Pawn", 2}, {"Knight", 1} }
    virtual const std::unordered_map<std::string, int>& getCapturedPieces(bool forWhite) const = 0;
};


#endif //CHESSPLUSPLUS_CHESSGAMESTATE_HPP

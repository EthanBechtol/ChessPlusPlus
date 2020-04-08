//
// Created by Ethan on 3/11/20.
//

#ifndef CHESSPLUSPLUS_STANDARDCHESSGAMESTATE_HPP
#define CHESSPLUSPLUS_STANDARDCHESSGAMESTATE_HPP


#include "../ChessGame/ChessGameState.hpp"
#include "StandardChessBoard.hpp"

class StandardChessGameState : public ChessGameState {
public:
    explicit StandardChessGameState(StandardChessBoard board);

    // board() returns a const reference to a ChessBoard containing the layout of the board
    // in the specific game state.
    virtual const ChessBoard& board() const noexcept override;

    // whiteScore() and blackScore() return the current white or black score respectively
    // as defined by the specific game state.
    virtual int whiteScore() const noexcept override;
    virtual int blackScore() const noexcept override;

    // isGameOver() returns true if the game is over as defined by the specific game state,
    // and false otherwise (i.e. in a standard game by reaching a checkmate.)
    virtual bool isGameOver() const noexcept override;

    // isWhiteTurn() and isBlackTurn() return true if it is the white or black player's turn
    // respectively, and false otherwise.
    virtual bool isWhiteTurn() const noexcept override;
    virtual bool isBlackTurn() const noexcept override;

    // isValidMove() returns true if the piece at start<x, y> can validly move to end<x, y>,
    // and false otherwise.
    virtual bool isValidMove(std::pair<int, int> start, std::pair<int, int> end) const override;

    // makeMove() makes a move on behalf of the current player with the chess piece
    // at cell start<x, y> ending at end<x,y>. If the move is invalid either by not being
    // a move that piece can make, or by not belonging to the player, a ChessException
    // is thrown.
    virtual void makeMove(std::pair<int, int> start, std::pair<int, int> end) override;

    // clone() returns a unique_ptr copy of the current game state.
    // Generally intended for use by an AI to simulate moves.
    virtual std::unique_ptr<ChessGameState> clone() const override;


    virtual std::vector<std::pair<int, int>> getValidPieceMoves(std::pair<int, int> start) const override;

private:
    // [white/black]Points keeps track of the number of points amassed by each colored player.
    int whitePoints;
    int blackPoints;

    // whiteTurn is true if the current turn is white and false if it is black's turn.
    bool whiteTurn;

    // gameOver is true if a checkmate is achieved by either player and false otherwise.
    // If true, the winner can be determined by whose turn it current is.
    bool gameOver;

    // isValidMoveThrow() validates that a move from a start position to an end position given the color piece is valid to
    // make. If not, then a ChessException will be thrown with the reason why a specific move cannot be made. This is
    // a helper function used by isValidMove() above which passes the move along with the CURRENT player whose turn it is.
    void isValidMoveThrow(std::pair<int, int> start, std::pair<int, int> end, bool isWhite) const;

    // isValidMoveForPlayer() returns whether or not a piece at start can make a move to end validly given a particular
    // player color. Returns true if it is valid and false otherwise.
    bool isValidMoveForPlayer(std::pair<int, int> start, std::pair<int, int> end, bool isWhite) const;
};


#endif //CHESSPLUSPLUS_STANDARDCHESSGAMESTATE_HPP

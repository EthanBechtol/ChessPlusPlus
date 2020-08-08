//
// Created by Ethan on 3/11/20.
//

#ifndef CHESSPLUSPLUS_STANDARDCHESSGAMESTATE_HPP
#define CHESSPLUSPLUS_STANDARDCHESSGAMESTATE_HPP


#include <stack>
#include "../ChessGame/ChessGameState.hpp"
#include "StandardChessBoard.hpp"
#include "StandardChessMoveData.hpp"

class StandardChessGameState : public ChessGameState {
public:
    explicit StandardChessGameState(StandardChessBoard board);

    // Copy constructor
    explicit StandardChessGameState(const StandardChessGameState& other);

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

    // undoMove returns the current game state to <amount> moves in the past undoing any moves either player made along
    // the way. If the <amount> parameter is greater than the number of undo moves stored, a ChessException is thrown.
    virtual void undoMove(unsigned int amount = 1) override;

    // undoMove returns the current game state to <amount> moves in the future redoing any moves undone via calling
    // undoMove(). If the <amount> parameter is greater than the number of redo moves stored, a ChessException is thrown.
    // If there are moves stored on the redo stack and a new move is made, the redo stack is completely cleared.
    virtual void redoMove(unsigned int amount = 1) override;

    // clone() returns a unique_ptr copy of the current game state.
    // Generally intended for use by an AI to simulate moves.
    virtual std::unique_ptr<ChessGameState> clone() const override;

    virtual std::vector<std::pair<int, int>> getValidPieceMoves(std::pair<int, int> start) const override;

    virtual const std::unordered_map<std::string, int>& getCapturedPieces(bool forWhite) const override;

private:
    std::unique_ptr<StandardChessBoard> _board;

    // [white/black]Points keeps track of the number of points amassed by each colored player.
    int whitePoints;
    int blackPoints;

    // whiteTurn is true if the current turn is white and false if it is black's turn.
    bool whiteTurn;

    // gameOver is true if a checkmate is achieved by either player and false otherwise.
    // If true, the winner can be determined by whose turn it current is.
    bool gameOver;

    // whiteCaptured and blackCaptured store the names of the pieces white or black has captured from the opposing team
    // along with how many of each piece it has captured.
    std::unordered_map<std::string, int> whiteCaptured;
    std::unordered_map<std::string, int> blackCaptured;

    // [white/black]InCheck keeps track of whether the respective player's king is in check. This will prevent a player
    // from moving other pieces if their king is in danger of capture.
    bool whiteInCheck;
    bool blackInCheck;

    // [undo/redo]Stack are used to keep track of moves as they happen in order to support undoing/redoing moves
    // over the course of the game.
    std::stack<ChessMoveData> undoStack;
    std::stack<ChessMoveData> redoStack;

    // redoInProgress inhibits clearing the redoStack when redo() requests a move to be made.
    bool redoInProgress = false;

    // isValidMoveThrow() validates that a move from a start position to an end position given the color piece is valid to
    // make. If not, then a ChessException will be thrown with the reason why a specific move cannot be made. This is
    // a helper function used by isValidMove() above which passes the move along with the CURRENT player whose turn it is.
    void isValidMoveThrow(std::pair<int, int> start, std::pair<int, int> end, bool isWhite) const;

    // isValidMoveForPlayer() returns whether or not a piece at start can make a move to end validly given a particular
    // player color. Returns true if it is valid and false otherwise.
    bool isValidMoveForPlayer(std::pair<int, int> start, std::pair<int, int> end, bool isWhite) const;

    bool checkmateAchieved(bool forWhite);
};


#endif //CHESSPLUSPLUS_STANDARDCHESSGAMESTATE_HPP

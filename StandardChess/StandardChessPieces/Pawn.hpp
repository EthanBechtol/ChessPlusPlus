//
// Created by Ethan on 2/27/20.
//

#ifndef CHESSPLUSPLUS_PAWN_HPP
#define CHESSPLUSPLUS_PAWN_HPP


#include "../../ChessGame/ChessPiece.hpp"
#include "../StandardChessBoard.hpp"

class Pawn : public ChessPiece {
public:
    Pawn();
    explicit Pawn(bool isWhite);

    bool isValidMove(std::pair<int, int> start, std::pair<int, int> end) const override;

    bool isValidCaptureMove(std::pair<int, int> start, std::pair<int, int> end) const override;

    // setFirstMove() sets the pawn's isFirstMove flag thus altering the piece's moveSet.
    void setFirstMove(bool firstMoveState) { isFirstMove = firstMoveState; };

private:
    // isFirstMove keeps track of whether the pawn is in it's starting position. If set to true, the pawn
    // is allowed to move two spaces forward instead of one space forward.
    bool isFirstMove;
};


#endif //CHESSPLUSPLUS_PAWN_HPP

//
// Created by Ethan on 2/27/20.
//

#include "ChessPiece.hpp"


ChessPiece::ChessPiece(const ChessPiece& other): moveSet{other.moveSet}, name{other.name}, white{other.white},
    hasCaptureMoves{other.hasCaptureMoves}, hasJumpAbility{other.hasJumpAbility} {

}

bool ChessPiece::isValidMove(std::pair<int, int> start, std::pair<int, int> end) const {
    return true;
}

bool ChessPiece::isValidCaptureMove(std::pair<int, int> start, std::pair<int, int> end) const {
    // This shall be left as is, because this function only needs to be overridden IF the piece has capture moves.
    // For those that don't, it will return the right thing automatically since hasCaptureMoves = false by default
    return hasCaptureMoves;
}

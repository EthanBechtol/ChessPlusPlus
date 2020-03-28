//
// Created by Ethan on 2/27/20.
//

#include "Rook.hpp"

Rook::Rook() {
    name = "Rook";
    white = true;
    hasCaptureMoves = false;
    hasJumpAbility = false;
}

Rook::Rook(bool isWhite): Rook() {
    white = isWhite;
}

bool Rook::isValidMove(std::pair<int, int> start, std::pair<int, int> end) const {
    return (start.first == end.first && end.second - start.second == 0) || (start.second == end.second && end.first - start.first == 0);
}
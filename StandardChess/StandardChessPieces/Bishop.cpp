//
// Created by Ethan on 2/27/20.
//

#include "Bishop.hpp"

Bishop::Bishop() {
    name = "Bishop";
    white = true;
    hasCaptureMoves = false;
    hasJumpAbility = false;
}

Bishop::Bishop(bool isWhite): Bishop() {
    white = isWhite;
}

bool Bishop::isValidMove(std::pair<int, int> start, std::pair<int, int> end) const {
    int xDiff = std::abs(start.first - end.first);
    int yDiff = std::abs(start.second - end.second);

    return xDiff == yDiff;
}
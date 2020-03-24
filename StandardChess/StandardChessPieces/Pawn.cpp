//
// Created by Ethan on 2/27/20.
//

#include "Pawn.hpp"

Pawn::Pawn(): isFirstMove{true} {
    name = "Pawn";
    white = true;
}

Pawn::Pawn(bool isWhite): isFirstMove{true} {
    name = "Pawn";
    white = isWhite;
}

bool Pawn::isValidMove(std::pair<int, int> start, std::pair<int, int> end) const {
    if(isFirstMove) {
        return (std::abs(start.first - end.first) == 1 || std::abs(start.first - end.first) == 2) && start.second == end.second;
    }
    else {
        // FIXME Need to account for the fact that pawns can only take a piece diagonally
        return std::abs(start.first - end.first) == 1 && start.second == end.second;
    }
}
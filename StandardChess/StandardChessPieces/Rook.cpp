//
// Created by Ethan on 2/27/20.
//

#include "Rook.hpp"

Rook::Rook() {
    name = "Rook";
    white = true;
    hasCaptureMoves = false;
    hasJumpAbility = false;

    moveSet = {
            // Horizontal/vertical moves
            {Mobility::slide, {1, 0}},
            {Mobility::slide, {-1, 0}},
            {Mobility::slide, {0, 1}},
            {Mobility::slide, {0, -1}}
    };
}

Rook::Rook(bool isWhite): Rook() {
    white = isWhite;
}

bool Rook::isValidMove(std::pair<int, int> start, std::pair<int, int> end) const {
    return (start.first == end.first && end.second - start.second == 0) || (start.second == end.second && end.first - start.first == 0);
}
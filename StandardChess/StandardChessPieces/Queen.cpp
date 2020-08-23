//
// Created by Ethan on 2/27/20.
//

#include "Queen.hpp"

Queen::Queen() {
    name = "Queen";
    white = true;
    hasCaptureMoves = false;
    hasJumpAbility = false;

    moveSet = {
            // Diagonal moves
            {Mobility::slide, {1, 1}},
            {Mobility::slide, {-1, -1}},
            {Mobility::slide, {-1, 1}},
            {Mobility::slide, {1, -1}},

            // Horizontal/vertical moves
            {Mobility::slide, {1, 0}},
            {Mobility::slide, {-1, 0}},
            {Mobility::slide, {0, 1}},
            {Mobility::slide, {0, -1}}
    };
}

Queen::Queen(bool isWhite): Queen() {
    white = isWhite;
}

bool Queen::isValidMove(std::pair<int, int> start, std::pair<int, int> end) const {
    int xDiff = std::abs(start.first - end.first);
    int yDiff = std::abs(start.second - end.second);

    return (start.first == end.first)
        || (start.second == end.second)
        || xDiff == yDiff;
}
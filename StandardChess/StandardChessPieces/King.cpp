//
// Created by Ethan on 2/27/20.
//

#include "King.hpp"

King::King() {
    name = "King";
    white = true;
    hasCaptureMoves = false;
    hasJumpAbility = false;

    moveSet = {
            // Diagonal moves
            {Mobility::jump, {1, 1}},
            {Mobility::jump, {-1, -1}},
            {Mobility::jump, {-1, 1}},
            {Mobility::jump, {1, -1}},

            // Horizontal/vertical moves
            {Mobility::jump, {1, 0}},
            {Mobility::jump, {-1, 0}},
            {Mobility::jump, {0, 1}},
            {Mobility::jump, {0, -1}}
    };
}

King::King(bool isWhite): King() {
    white = isWhite;
}

bool King::isValidMove(std::pair<int, int> start, std::pair<int, int> end) const {
    return start.first-1 < end.first && end.first < start.first+1 && start.second-1 < end.second && end.second < start.second+1;
}
//
// Created by Ethan on 2/27/20.
//

#include "Knight.hpp"


Knight::Knight() {
    name = "Knight";
    white = true;
    hasCaptureMoves = false;
    hasJumpAbility = true;

    moveSet = {
            {Mobility::jump, {2, 1}},
            {Mobility::jump, {2, -1}},

            {Mobility::jump, {-2, 1}},
            {Mobility::jump, {-2, -1}},

            {Mobility::jump, {1, 2}},
            {Mobility::jump, {1, -2}},

            {Mobility::jump, {-1, 2}},
            {Mobility::jump, {-1, -2}}
    };
}

Knight::Knight(bool isWhite): Knight() {
    white = isWhite;
}

bool Knight::isValidMove(std::pair<int, int> start, std::pair<int, int> end) const {
    int x = std::abs(start.first - end.first);
    int y = std::abs(start.second - end.second);

    return x * y == 2;
}

//
// Created by Ethan on 2/27/20.
//

#include "Pawn.hpp"

Pawn::Pawn(): isFirstMove{true} {
    name = "Pawn";
    white = true;
    hasCaptureMoves = true;
    hasJumpAbility = false;
    
    moveSet = {
            // Vertical moves
            {Mobility::jump, {-1, 0}},

            // Opening 2 cell move TODO: check implementation
            {Mobility::jump, {-2, 0}},

            // Diagonal capture moves
            {Mobility::jump, {-1, 1}},
            {Mobility::jump, {-1, -1}}
    };
}

Pawn::Pawn(bool isWhite): Pawn() {
    white = isWhite;

    if(!isWhite){
        moveSet = {
                // Vertical moves
                {Mobility::jump, {1, 0}},

                // Opening 2 cell move TODO: check implementation
                {Mobility::jump, {2, 0}},

                // Diagonal capture moves
                {Mobility::jump, {1, 1}},
                {Mobility::jump, {1, -1}}
        };
    }
}

// FIXME account for directionality if the piece is either white or black.
//  Currently these methods allow pawns to go both forwards and backwards incorrectly.
bool Pawn::isValidMove(std::pair<int, int> start, std::pair<int, int> end) const {
    if(isFirstMove)
        return (std::abs(start.first - end.first) == 1 || std::abs(start.first - end.first) == 2) && start.second == end.second;
    else
        return std::abs(start.first - end.first) == 1 && start.second == end.second;
}

bool Pawn::isValidCaptureMove(std::pair<int, int> start, std::pair<int, int> end) const {
    /*
     *    Y N Y  | Y = capturable
     *    N P N  | N = uncapturable
     *    N N N  | P = pawn position
     */

    return std::abs(start.first - end.first) == 1 && std::abs(start.second - end.second) == 1;
}


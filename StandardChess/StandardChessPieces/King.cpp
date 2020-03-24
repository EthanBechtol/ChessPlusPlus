//
// Created by Ethan on 2/27/20.
//

#include "King.hpp"

King::King() {
    name = "King";
    white = true;
}

King::King(bool isWhite) {
    name = "King";
    white = isWhite;
}

bool King::isValidMove(std::pair<int, int> start, std::pair<int, int> end) const {
    return start.first-1 < end.first && end.first < start.first+1 && start.second-1 < end.second && end.second < start.second+1;
}
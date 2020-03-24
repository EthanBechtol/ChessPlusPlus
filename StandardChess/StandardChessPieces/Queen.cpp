//
// Created by Ethan on 2/27/20.
//

#include "Queen.hpp"

Queen::Queen() {
    name = "Queen";
    white = true;
}

Queen::Queen(bool isWhite) {
    name = "Queen";
    white = isWhite;
}

bool Queen::isValidMove(std::pair<int, int> start, std::pair<int, int> end) const {
    int xDiff = std::abs(start.first - end.first);
    int yDiff = std::abs(start.second - end.second);

    return (start.first == end.first && end.second - start.second == 0)
        || (start.second == end.second && end.first - start.first == 0)
        || xDiff == yDiff;
}
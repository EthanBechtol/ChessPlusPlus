//
// Created by Ethan on 4/2/20.
//

#ifndef CHESSPLUSPLUS_CHESSPIECEMOBILITY_HPP
#define CHESSPLUSPLUS_CHESSPIECEMOBILITY_HPP

#include <utility>
#include "../ChessUtility/PairHash.hpp"

enum Mobility {
    slide,  // a piece can slide infinitely many tiles, and must stop when encountering another piece blocking the way.
    jump    // a piece can make a single jump to a tile, and can jump over another piece blocking the way.
};

/*
 ChessPieceMobility (CPM) is a structure to be used to answer the question, "how does this piece move" rather than the already
 answered question, "can this piece move here". CPM allows more efficient solutions to cast rays and determine how far
 a piece can move before it is blocked for example. This also allows O(1) solutions to figure out which tiles a piece can move to
 as opposed to the O(w * h) solution that would be needed by iterating the width and height of a board and querying each individual tile.

 Each CPM is comprised of a Mobility enum and a direction integer pair.
    Mobility: This enum specifies the manner in which a piece moves; either sliding or jumping. In a slide, a piece can move
     in a particular direction until it is blocked by another piece in the way. EX: a Queen's movement.
     In a jump, a piece can move in a particular direction uninhibited by pieces in the way, being able to ignore them.
     EX: a knight's movement.
    Direction: This integer pair specifies the relative <row, column> direction which this particular CPM can be made.
     for example, direction = {1, 1} means a piece can move up one row and to the right one column, or diagonally one tile.
*/

struct ChessPieceMobility {
    ChessPieceMobility(Mobility type, std::pair<int, int> direction): type{type}, direction{std::move(direction)} {};

    Mobility type;
    std::pair<int, int> direction;

    bool operator==(const ChessPieceMobility& other) const {
        return type == other.type && direction == other.direction;
    }
};

// A hash function that allows ChessPieceMobility to be used in containers such as unordered_set.
namespace std {
    template <>
    struct hash<ChessPieceMobility> {
        size_t operator()(const ChessPieceMobility& cpm) const {
            auto first = std::hash<int>{}(cpm.direction.first);
            auto second = std::hash<int>{}(cpm.direction.second);

            return first ^ second;
        }
    };
}

#endif //CHESSPLUSPLUS_CHESSPIECEMOBILITY_HPP

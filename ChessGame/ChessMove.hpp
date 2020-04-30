#include <utility>

//
// Created by Ethan on 3/17/20.
//

#ifndef CHESSPLUSPLUS_CHESSMOVE_HPP
#define CHESSPLUSPLUS_CHESSMOVE_HPP

struct ChessMove {
    ChessMove() = default;
    ChessMove(std::pair<int, int>  start, std::pair<int, int>  end): start{std::move(start)}, end{std::move(end)} {};

    std::pair<int, int> start;
    std::pair<int, int> end;
};

#endif //CHESSPLUSPLUS_CHESSMOVE_HPP

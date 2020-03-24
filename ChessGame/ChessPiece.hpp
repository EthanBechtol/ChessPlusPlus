//
// Created by Ethan on 2/24/20.
//

#ifndef CHESSPLUSPLUS_CHESSPIECE_HPP
#define CHESSPLUSPLUS_CHESSPIECE_HPP


#include <string>
#include <vector>

class ChessPiece {
public:
    virtual ~ChessPiece() = default;

    // isValidMove() returns whether the piece can make a move given a starting and ending
    // position according to it's move set.
    // NOTE: This will NOT take into account whether another piece occupies the tile, or whether
    // it's move would otherwise be blocked. This ONLY asks the question whether the start and end
    // positions are possible given the piece's move rule set.
    virtual bool isValidMove(std::pair<int, int> start, std::pair<int, int> end) const;

    // getName() returns the name of the current piece
    virtual std::string getName() const { return name; };

    // isWhite() & isBlack() return whether the piece is colored white or black respectively.
    virtual bool isWhite() const { return white; }
    virtual bool isBlack() const { return !white; }

protected:
    //std::vector<ChessMove> moveSet;
    std::string name;
    bool white;
};


#endif //CHESSPLUSPLUS_CHESSPIECE_HPP

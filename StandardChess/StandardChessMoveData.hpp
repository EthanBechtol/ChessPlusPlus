//
// Created by Ethan on 8/7/20.
//

#ifndef CHESSPLUSPLUS_STANDARDCHESSMOVEDATA_HPP
#define CHESSPLUSPLUS_STANDARDCHESSMOVEDATA_HPP

#include <utility>

#include "../ChessGame/ChessPiece.hpp"
#include "../ChessGame/ChessMove.hpp"

struct ChessMoveData {
    ChessMoveData(const ChessPiece& takenPiece, ChessMove move):
        takenPiece(takenPiece.getName().empty() ? nullptr : std::make_unique<ChessPiece>(takenPiece)),
        moveCoords(std::move(move)) {};

    ChessMoveData(const ChessMoveData& other):
        takenPiece{other.takenPiece == nullptr ? nullptr : std::make_unique<ChessPiece>(*other.takenPiece)},
        moveCoords(other.moveCoords) {};

    std::unique_ptr<ChessPiece> takenPiece = nullptr;
    ChessMove moveCoords;
};

#endif //CHESSPLUSPLUS_STANDARDCHESSMOVEDATA_HPP

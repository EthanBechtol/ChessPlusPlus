//
// Created by Ethan on 7/2/20.
//

#include "InputReaderAI.hpp"
#include "../StandardChess/StandardChessAIs/RandomAI.hpp"

InputReaderAI::InputReaderAI(ChessAI& source): InputReader(), source{source.clone()} {
    readerType = AI;
}

InputRequest InputReaderAI::getInput(const ChessGameState& state) const {
    ChessMove move = source->choseMove(state);
    return InputRequest{RequestType::move, move, source->name(), ""};
}

InputReaderAI::~InputReaderAI() {
    delete source;
}

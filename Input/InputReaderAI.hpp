//
// Created by Ethan on 7/2/20.
//

#ifndef CHESSPLUSPLUS_INPUTREADERAI_HPP
#define CHESSPLUSPLUS_INPUTREADERAI_HPP

#include "InputReader.hpp"
#include "InputRequest.hpp"
#include "../ChessGame/ChessAI.hpp"

class InputReaderAI : public InputReader {
public:
    InputReaderAI(ChessAI& source);

    InputRequest getInput(const ChessGameState& state) const override;

    ~InputReaderAI() override;

private:
    ChessAI* source;
};


#endif //CHESSPLUSPLUS_INPUTREADERAI_HPP

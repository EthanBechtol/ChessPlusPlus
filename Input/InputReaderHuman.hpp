//
// Created by Ethan on 9/24/20.
//

#ifndef CHESSPLUSPLUS_INPUTREADERHUMAN_HPP
#define CHESSPLUSPLUS_INPUTREADERHUMAN_HPP


#include "InputReader.hpp"

class InputReaderHuman : public InputReader{
public:
    InputReaderHuman();

    InputRequest getInput(const ChessGameState& state) const override;
};


#endif //CHESSPLUSPLUS_INPUTREADERHUMAN_HPP

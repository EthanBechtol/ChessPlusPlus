//
// Created by Ethan on 3/17/20.
//

#ifndef CHESSPLUSPLUS_INPUTREADER_HPP
#define CHESSPLUSPLUS_INPUTREADER_HPP

#include "InputRequest.hpp"
#include "../ChessGame/ChessGameState.hpp"

enum ReaderType {
    human,
    AI
};

class InputReader {
public:
    // Returns an input request type which contains the type of request made, as well as the data to go along with such
    // request if necessary (i.e. the move coordinates). Valid requests are specified in InputRequest.hpp
    virtual InputRequest getInput(const ChessGameState& state) const = 0;

    virtual ~InputReader() = default;

    ReaderType readerType;
};


#endif //CHESSPLUSPLUS_INPUTREADER_HPP

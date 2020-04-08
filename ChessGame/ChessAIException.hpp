//
// Created by Ethan on 4/6/20.
//

#ifndef CHESSPLUSPLUS_CHESSAIEXCEPTION_HPP
#define CHESSPLUSPLUS_CHESSAIEXCEPTION_HPP

#include <string>
#include <utility>

class ChessAIException : public std::logic_error {
public:
    explicit ChessAIException(const std::string& reason);
};

inline ChessAIException::ChessAIException(const std::string& reason): std::logic_error{reason} {

}

#endif //CHESSPLUSPLUS_CHESSAIEXCEPTION_HPP

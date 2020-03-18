//
// Created by Ethan on 2/24/20.
//

#ifndef CHESSPLUSPLUS_CHESSEXCEPTION_HPP
#define CHESSPLUSPLUS_CHESSEXCEPTION_HPP


#include <string>
#include <utility>

class ChessException : public std::logic_error {
public:
    explicit ChessException(const std::string& reason);
};

inline ChessException::ChessException(const std::string& reason): std::logic_error{reason} {

}

#endif //CHESSPLUSPLUS_CHESSEXCEPTION_HPP

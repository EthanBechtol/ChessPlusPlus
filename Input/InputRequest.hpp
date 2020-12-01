//
// Created by Ethan on 7/2/20.
//

#ifndef CHESSPLUSPLUS_INPUTREQUEST_HPP
#define CHESSPLUSPLUS_INPUTREQUEST_HPP

#include <string>
#include "../ChessGame/ChessMove.hpp"

/*
 * Input Request:
 * When reading from an input source, multiple types of input requests may be received; the most common of which will be
 * a move request. However, a player may request other things such as to quit the game, get game statistics, etc.
 */

enum RequestType {
    move,  // makes a move on the chess board
    quit,  // exits the game (only able to be made by a human player)
    stats,  // returns statistics about the game (not currently implemented)
    invalid, // used internally to indicate a malformed request
};

struct InputRequest {
    RequestType requestType;
    ChessMove moveRequest;
    std::string requester;
    std::string data;
};

#endif //CHESSPLUSPLUS_INPUTREQUEST_HPP

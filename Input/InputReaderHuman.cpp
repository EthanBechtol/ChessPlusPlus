//
// Created by Ethan on 9/24/20.
//

#include <iostream>
#include <sstream>
#include "InputReaderHuman.hpp"
#include "../ChessGame/ChessMove.hpp"
#include "InputRequest.hpp"

namespace {
    template <typename Output>
    void split(const std::string &s, char delimeter, Output result) {
        std::istringstream iss(s);
        std::string item;
        while (std::getline(iss, item, delimeter)) {
            if(!item.empty())
                *result++ = item;
        }
    }

    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, std::back_inserter(elems));
        return elems;
    }

    std::string getHelpString(){
        const static std::string result = "Available command formats:\n"
                                          "[] = required, <> = optional\n"
                                          "\t- Move: [m/move] [startRow] [startColumn] [endRow] [endColumn]\n"
                                          "\t- Statistics: [s/stats]\n"
                                          "\t- Quit: [q/quit]";

        return result;
    }

    InputRequest readInput(std::ostream& output){
        std::string rawInput;
        std::getline(std::cin, rawInput);
        std::vector<std::string> splitInput = split(rawInput, ' ');

        InputRequest result;

        bool validRequest = false;

        do {
            if (splitInput[0] == "m" || splitInput[0] == "move") {
                if (splitInput.size() == 5) {
                    result.requestType = RequestType::move;
                    result.moveRequest.start.first = std::stoi(splitInput[1]);
                    result.moveRequest.start.second = std::stoi(splitInput[2]);
                    result.moveRequest.end.first = std::stoi(splitInput[3]);
                    result.moveRequest.end.second = std::stoi(splitInput[4]);
                    validRequest = true;
                }
            }
            else if (splitInput[0] == "s" || splitInput[0] == "stats") {
                result.requestType = RequestType::stats;
                validRequest = true;
            }
            else if (splitInput[0] == "q" || splitInput[0] == "quit") {
                result.requestType = RequestType::quit;
                validRequest = true;
            }

            if(!validRequest){
                output << "Invalid request.\n" << getHelpString() << std::endl;
                std::getline(std::cin, rawInput);
                splitInput = split(rawInput, ' ');
            }
        }
        while(!validRequest);

        return result;
    }
}

InputReaderHuman::InputReaderHuman() {
    readerType = ReaderType::human;
}

InputRequest InputReaderHuman::getInput(const ChessGameState& state) const {
    InputRequest humanRequest =  readInput(std::cout);
    humanRequest.requester = "Human";
    return humanRequest;
}

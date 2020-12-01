#include <vector>
#include <unordered_map>
#include "ChessGame/ChessGameManager.hpp"
#include "Input/InputReaderHuman.hpp"
#include "Input/InputReaderAI.hpp"
#include "StandardChess/StandardChessAIs/MinMaxAI.hpp"
#include "StandardChess/StandardChessAIs/RandomAI.hpp"


InputReader* getNewReader(const std::string& type){
    if(type == "human")
        return new InputReaderHuman;
    else if(type == "minimax") {
        MinMaxAI ai;
        return new InputReaderAI(ai);
    }
    else if(type == "random") {
        RandomAI ai;
        return new InputReaderAI(ai);
    }
    else
        throw std::runtime_error("Unknown player type: " + type + ".");
}

void applyOptions(const std::vector<std::string>& args, ChessGameManager& manager){
    if(args.empty())
        return;

    if(args.size() == 1)
        manager.setPlayer(1, getNewReader(args[0]));
    else if(args.size() == 2){
        manager.setPlayer(1, getNewReader(args[0]));
        manager.setPlayer(2, getNewReader(args[1]));
    }
    else
        throw std::runtime_error("Invalid number of command line arguments.");
}

int main(int argc, char **argv) {
    std::vector<std::string> args;
    for(int i = 1; i < argc; ++i){
        args.emplace_back(argv[i]);
    }

    ChessGameManager manager;
    applyOptions(args, manager);
    manager.run();

    return 0;
}
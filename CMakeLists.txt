cmake_minimum_required(VERSION 3.15)
project(ChessPlusPlus)

set(CMAKE_CXX_STANDARD 17)

add_executable(ChessPlusPlus main.cpp
        ChessGame/ChessBoard.hpp
        ChessGame/ChessCellState.hpp
        ChessGame/ChessCell.hpp
        ChessGame/ChessPiece.hpp
        ChessGame/ChessException.hpp
        ChessGame/ChessAI.hpp
        ChessGame/ChessGameState.hpp
        ChessGame/ChessGameStateFactory.cpp
        ChessGame/ChessGameStateFactory.hpp
        ChessGame/ChessMove.hpp
        ChessGame/ChessPiece.cpp

        StandardChess/StandardChessBoard.cpp
        StandardChess/StandardChessBoard.hpp
        StandardChess/StandardChessCell.cpp
        StandardChess/StandardChessCell.hpp
        StandardChess/StandardChessGameState.cpp
        StandardChess/StandardChessGameState.hpp

        StandardChess/StandardChessPieces/Knight.cpp
        StandardChess/StandardChessPieces/Knight.hpp
        StandardChess/StandardChessPieces/Pawn.cpp
        StandardChess/StandardChessPieces/Pawn.hpp
        StandardChess/StandardChessPieces/Queen.cpp
        StandardChess/StandardChessPieces/Queen.hpp
        StandardChess/StandardChessPieces/Bishop.cpp
        StandardChess/StandardChessPieces/Bishop.hpp
        StandardChess/StandardChessPieces/Rook.cpp
        StandardChess/StandardChessPieces/Rook.hpp
        StandardChess/StandardChessPieces/King.cpp
        StandardChess/StandardChessPieces/King.hpp


        Experimental/EXPChessMove.hpp

        Input/InputReader.cpp
        Input/InputReader.hpp StandardChess/StandardChessAIs/RandomAI.cpp StandardChess/StandardChessAIs/RandomAI.hpp ChessGame/ChessPieceMobility.hpp ChessUtility/PairHash.hpp ChessGame/ChessAIException.hpp)
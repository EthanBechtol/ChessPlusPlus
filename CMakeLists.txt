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
        ChessGame/ChessAIException.hpp
        ChessGame/ChessGameState.hpp
        ChessGame/ChessGameStateFactory.cpp
        ChessGame/ChessGameStateFactory.hpp
        ChessGame/ChessMove.hpp
        ChessGame/ChessPiece.cpp
        ChessGame/ChessPieceMobility.hpp

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

        StandardChess/StandardChessAIs/RandomAI.cpp
        StandardChess/StandardChessAIs/RandomAI.hpp
        StandardChess/StandardChessAIs/MinMaxAI.cpp
        StandardChess/StandardChessAIs/MinMaxAI.hpp

        Input/InputReader.hpp
        Input/InputRequest.hpp
        Input/InputReaderAI.cpp
        Input/InputReaderAI.hpp

        ChessUtility/PairHash.hpp)
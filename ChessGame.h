#pragma once
#include <cinttypes>
#include <map>
#include <array>
#include <vector>
#include <memory>

#include "DefaultValues.h"

class ChessGame 
{
    public:
    ChessGame();
    ChessGame(const ChessGame &source);

    ~ChessGame();

    std::array<std::array<int_fast8_t, ROWS>, COLUMNS> *board;
    std::map<std::pair<int_fast8_t, int_fast8_t>, std::vector<std::pair<int_fast8_t, int_fast8_t>>>* whiteLegalMoves;
    std::map<std::pair<int_fast8_t, int_fast8_t>, std::vector<std::pair<int_fast8_t, int_fast8_t>>>* blackLegalMoves;

    // Vector (size 6), which tracks each move set, pair of moves (piece, position)
    std::vector<std::pair<std::pair<int_fast8_t, int_fast8_t>, std::pair<int_fast8_t, int_fast8_t>>> *lastMoves;
    bool whiteCanCastle;
    bool blackCanCastle;
    bool whiteLeftRookMoved;
    bool whiteRightRookMoved;
    bool blackLeftRookMoved;
    bool blackRightRookMoved;
    bool whiteTurn;
    long currentMove;

    // Used to check basic game state
    bool gameWon;

    // Used to check exact game state 
    // PlayingGame = 0, WhiteWon = 1, BlackWon = 2, GameDrawn = 3
    int_fast8_t gameState;
    
};
#pragma once
#include "ChessGame.h"

class BoardHandler
{
public:
    BoardHandler() = default;
    ~BoardHandler() = default;

    void calculateLegalMoves(ChessGame &cg);

    bool checkForRepition
    (std::vector<std::pair<std::pair<int_fast8_t, int_fast8_t>, std::pair<int_fast8_t, int_fast8_t>>> &lastMoves);

    void calculateWhiteMoves(std::map<std::pair<int_fast8_t, int_fast8_t>, std::vector<std::pair<int_fast8_t, int_fast8_t>>>& whiteLegalMoves, 
    std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board);

    void calculateBlackMoves(std::map<std::pair<int_fast8_t, int_fast8_t>, std::vector<std::pair<int_fast8_t, int_fast8_t>>>& blackLegalMoves,
    std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board);

    bool checkWhiteCheck(std::map<std::pair<int_fast8_t, int_fast8_t>, std::vector<std::pair<int_fast8_t, int_fast8_t>>>& blackLegalMoves,
    std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board);
    bool checkBlackCheck(std::map<std::pair<int_fast8_t, int_fast8_t>, std::vector<std::pair<int_fast8_t, int_fast8_t>>>& whiteLegalMoves,
    std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board);
    void handleWhiteCheck(
    std::map<std::pair<int_fast8_t, int_fast8_t>, std::vector<std::pair<int_fast8_t, int_fast8_t>>>& whiteLegalMoves, 
    std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board);
    void handleBlackCheck(
    std::map<std::pair<int_fast8_t, int_fast8_t>, std::vector<std::pair<int_fast8_t, int_fast8_t>>>& blackLegalMoves, 
    std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board);

    void handleWhiteCastling(ChessGame &cg);
    void handleBlackCastling(ChessGame &cg);

    // White Move Handlers
    std::vector<std::pair<int_fast8_t, int_fast8_t>> handleWhitePawn
    (std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x);
    std::vector<std::pair<int_fast8_t, int_fast8_t>> handleUnmovedWhitePawn
    (std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x);
    std::vector<std::pair<int_fast8_t, int_fast8_t>> handleWhiteRook
    (std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x);
    std::vector<std::pair<int_fast8_t, int_fast8_t>> handleWhiteKnight
    (std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x);
    std::vector<std::pair<int_fast8_t, int_fast8_t>> handleWhiteBishop
    (std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x);
    std::vector<std::pair<int_fast8_t, int_fast8_t>> handleWhiteQueen
    (std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x);
    std::vector<std::pair<int_fast8_t, int_fast8_t>> handleWhiteKing
    (std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x);
    
    
    
    // Black Move Handlers
    std::vector<std::pair<int_fast8_t, int_fast8_t>> handleBlackPawn
    (std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x);
    std::vector<std::pair<int_fast8_t, int_fast8_t>> handleUnmovedBlackPawn
    (std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x);
    std::vector<std::pair<int_fast8_t, int_fast8_t>> handleBlackRook
    (std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x);
    std::vector<std::pair<int_fast8_t, int_fast8_t>> handleBlackKnight
    (std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x);
    std::vector<std::pair<int_fast8_t, int_fast8_t>> handleBlackBishop
    (std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x);
    std::vector<std::pair<int_fast8_t, int_fast8_t>> handleBlackQueen
    (std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x);
    std::vector<std::pair<int_fast8_t, int_fast8_t>> handleBlackKing
    (std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x);

    // Takes Board, and Moveset as parameters (Piece current position, piece desired position)
    void handleMove(std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, std::pair<std::pair<int_fast8_t, int_fast8_t>, std::pair<int_fast8_t, int_fast8_t>>& moveSet);
    void updateLastMoves(std::vector<std::pair<std::pair<int_fast8_t, int_fast8_t>, std::pair<int_fast8_t, int_fast8_t>>> &lastMoves, 
    std::pair<std::pair<int_fast8_t, int_fast8_t>, std::pair<int_fast8_t, int_fast8_t>>& moveSet);
    void printBoard(ChessGame &cg);
    void printTurn(bool whiteTurn);
    void printLegalMoves(ChessGame &cg);
    std::string translateToNotation(int_fast8_t y, int_fast8_t x);
    std::string translateToPiece(int_fast8_t pieceNum);
};
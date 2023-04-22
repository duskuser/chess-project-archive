#pragma once
#include <iostream>
#include <cinttypes>
#include <stack>
#include <map>
#include <array>
#include <vector>
#include <algorithm>
#include <thread>
#include <memory>

#define ROWS 8
#define COLUMNS 8
#define MAX_MOVES 8
#define STARTING_MOVES 20
#define MOVE_ERROR 99
#define BOARD_TOP 0
#define BOARD_BOTTOM 7
#define BOARD_LEFT 0
#define BOARD_RIGHT 7
#define FIRST_ROW 7
#define SECOND_ROW 6
#define THIRD_ROW 5
#define FOURTH_ROW 4
#define FIFTH_ROW 3
#define SIXTH_ROW 2
#define SEVENTH_ROW 1
#define EIGHTH_ROW 0

#define REPEATABLE_MOVES 6
#define CODE_SIZE 265

#define toDigit(c) (c-'0')

const auto CPU_THREADS = std::thread::hardware_concurrency();

enum ChessPiece : const int_fast8_t 
{
    EmptySpace = 0, 
    // White Pieces
    WhitePawn = 1, UnmovedWhitePawn = 2, WhiteRook = 3, WhiteKnight = 4, WhiteBishop = 5,
    WhiteQueen = 6, WhiteKing = 7,
    // Black Pieces
    BlackPawn = 8, UnmovedBlackPawn = 9, BlackRook = 10, BlackKnight = 11, BlackBishop =12,
    BlackQueen = 13, BlackKing = 14
};

enum GameState : const int_fast8_t
{
    PlayingGame = 0, WhiteWon = 1, BlackWon = 2, GameDrawn = 3
};


const std::pair<int_fast8_t, int_fast8_t> A1 = 
{7, 0};
const std::pair<int_fast8_t, int_fast8_t> A2 = 
{6, 0};
const std::pair<int_fast8_t, int_fast8_t> A3 = 
{5, 0};
const std::pair<int_fast8_t, int_fast8_t> A4 = 
{4, 0};
const std::pair<int_fast8_t, int_fast8_t> A5 = 
{3, 0};
const std::pair<int_fast8_t, int_fast8_t> A6 = 
{2, 0};
const std::pair<int_fast8_t, int_fast8_t> A7 = 
{1, 0};
const std::pair<int_fast8_t, int_fast8_t> A8 = 
{0, 0};

const std::pair<int_fast8_t, int_fast8_t> B1 = 
{7, 1};
const std::pair<int_fast8_t, int_fast8_t> B2 = 
{6, 1};
const std::pair<int_fast8_t, int_fast8_t> B3 = 
{5, 1};
const std::pair<int_fast8_t, int_fast8_t> B4 = 
{4, 1};
const std::pair<int_fast8_t, int_fast8_t> B5 = 
{3, 1};
const std::pair<int_fast8_t, int_fast8_t> B6 = 
{2, 1};
const std::pair<int_fast8_t, int_fast8_t> B7 = 
{1, 1};
const std::pair<int_fast8_t, int_fast8_t> B8 = 
{0, 1};

const std::pair<int_fast8_t, int_fast8_t> C1 = 
{7, 2};
const std::pair<int_fast8_t, int_fast8_t> C2 = 
{6, 2};
const std::pair<int_fast8_t, int_fast8_t> C3 = 
{5, 2};
const std::pair<int_fast8_t, int_fast8_t> C4 = 
{4, 2};
const std::pair<int_fast8_t, int_fast8_t> C5 = 
{3, 2};
const std::pair<int_fast8_t, int_fast8_t> C6 = 
{2, 2};
const std::pair<int_fast8_t, int_fast8_t> C7 = 
{1, 2};
const std::pair<int_fast8_t, int_fast8_t> C8 = 
{0, 2};

const std::pair<int_fast8_t, int_fast8_t> D1 = 
{7, 3};
const std::pair<int_fast8_t, int_fast8_t> D2 = 
{6, 3};
const std::pair<int_fast8_t, int_fast8_t> D3 = 
{5, 3};
const std::pair<int_fast8_t, int_fast8_t> D4 = 
{4, 3};
const std::pair<int_fast8_t, int_fast8_t> D5 = 
{3, 3};
const std::pair<int_fast8_t, int_fast8_t> D6 = 
{2, 3};
const std::pair<int_fast8_t, int_fast8_t> D7 = 
{1, 3};
const std::pair<int_fast8_t, int_fast8_t> D8 = 
{0, 3};

const std::pair<int_fast8_t, int_fast8_t> E1 = 
{7, 4};
const std::pair<int_fast8_t, int_fast8_t> E2 = 
{6, 4};
const std::pair<int_fast8_t, int_fast8_t> E3 = 
{5, 4};
const std::pair<int_fast8_t, int_fast8_t> E4 = 
{4, 4};
const std::pair<int_fast8_t, int_fast8_t> E5 = 
{3, 4};
const std::pair<int_fast8_t, int_fast8_t> E6 = 
{2, 4};
const std::pair<int_fast8_t, int_fast8_t> E7 = 
{1, 4};
const std::pair<int_fast8_t, int_fast8_t> E8 = 
{0, 4};

const std::pair<int_fast8_t, int_fast8_t> F1 = 
{7, 5};
const std::pair<int_fast8_t, int_fast8_t> F2 = 
{6, 5};
const std::pair<int_fast8_t, int_fast8_t> F3 = 
{5, 5};
const std::pair<int_fast8_t, int_fast8_t> F4 = 
{4, 5};
const std::pair<int_fast8_t, int_fast8_t> F5 = 
{3, 5};
const std::pair<int_fast8_t, int_fast8_t> F6 = 
{2, 5};
const std::pair<int_fast8_t, int_fast8_t> F7 = 
{1, 5};
const std::pair<int_fast8_t, int_fast8_t> F8 = 
{0, 5};

const std::pair<int_fast8_t, int_fast8_t> G1 = 
{7, 6};
const std::pair<int_fast8_t, int_fast8_t> G2 = 
{6, 6};
const std::pair<int_fast8_t, int_fast8_t> G3 = 
{5, 6};
const std::pair<int_fast8_t, int_fast8_t> G4 = 
{4, 6};
const std::pair<int_fast8_t, int_fast8_t> G5 = 
{3, 6};
const std::pair<int_fast8_t, int_fast8_t> G6 = 
{2, 6};
const std::pair<int_fast8_t, int_fast8_t> G7 = 
{1, 6};
const std::pair<int_fast8_t, int_fast8_t> G8 = 
{0, 6};

const std::pair<int_fast8_t, int_fast8_t> H1 = 
{7, 7};
const std::pair<int_fast8_t, int_fast8_t> H2 = 
{6, 7};
const std::pair<int_fast8_t, int_fast8_t> H3 = 
{5, 7};
const std::pair<int_fast8_t, int_fast8_t> H4 = 
{4, 7};
const std::pair<int_fast8_t, int_fast8_t> H5 = 
{3, 7};
const std::pair<int_fast8_t, int_fast8_t> H6 = 
{2, 7};
const std::pair<int_fast8_t, int_fast8_t> H7 = 
{1, 7};
const std::pair<int_fast8_t, int_fast8_t> H8 = 
{0, 7};

// Rooks
const std::pair<int_fast8_t, int_fast8_t> RookShortCastle(0, -2);
const std::pair<int_fast8_t, int_fast8_t> RookLongCastle(0, 3);

// Kings
const std::pair<int_fast8_t, int_fast8_t> KingShortCastle(0, 2);
const std::pair<int_fast8_t, int_fast8_t> KingLongCastle(0, -2);

// Pawns (White)
const std::pair<int_fast8_t, int_fast8_t> UnmovedWhitePawnForward(-2, 0);
const std::pair<int_fast8_t, int_fast8_t> WhitePawnForward(-1, 0);
const std::pair<int_fast8_t, int_fast8_t> WhitePawnTakeLeft(-1, -1);
const std::pair<int_fast8_t, int_fast8_t> WhitePawnTakeRight(-1, 1);

// Pawns (Black)
const std::pair<int_fast8_t, int_fast8_t> UnmovedBlackPawnForward(2, 0);
const std::pair<int_fast8_t, int_fast8_t> BlackPawnForward(1, 0);
const std::pair<int_fast8_t, int_fast8_t> BlackPawnTakeLeft(1, -1);
const std::pair<int_fast8_t, int_fast8_t> BlackPawnTakeRight(1, 1);

// Knights
const std::pair<int_fast8_t, int_fast8_t> KnightLeftForward(-1, -2);
const std::pair<int_fast8_t, int_fast8_t> KnightRightForward(-1, 2);
const std::pair<int_fast8_t, int_fast8_t> KnightLeftBack(1, -2);
const std::pair<int_fast8_t, int_fast8_t> KnightRightBack(1, 2);
const std::pair<int_fast8_t, int_fast8_t> KnightForwardLeft(-2, -1);
const std::pair<int_fast8_t, int_fast8_t> KnightForwardRight(-2, 1);
const std::pair<int_fast8_t, int_fast8_t> KnightBackLeft(2, -1);
const std::pair<int_fast8_t, int_fast8_t> KnightBackRight(2, 1);

// Generic Piece Moves
const std::pair<int_fast8_t, int_fast8_t> PieceForwardLeft(-1, -1);
const std::pair<int_fast8_t, int_fast8_t> PieceForwardRight(-1, 1);
const std::pair<int_fast8_t, int_fast8_t> PieceBackLeft(1, -1);
const std::pair<int_fast8_t, int_fast8_t> PieceBackRight(1, 1);
const std::pair<int_fast8_t, int_fast8_t> PieceForward(-1, 0);
const std::pair<int_fast8_t, int_fast8_t> PieceBack(1, 0);
const std::pair<int_fast8_t, int_fast8_t> PieceLeft(0, -1);
const std::pair<int_fast8_t, int_fast8_t> PieceRight(0, 1);

const std::array<std::array<int_fast8_t, ROWS>, COLUMNS> defaultBoard
{
    {
    {BlackRook, BlackKnight, BlackBishop, BlackQueen, BlackKing, BlackBishop, BlackKnight, BlackRook},
    {UnmovedBlackPawn, UnmovedBlackPawn, UnmovedBlackPawn, UnmovedBlackPawn, UnmovedBlackPawn, UnmovedBlackPawn, UnmovedBlackPawn, UnmovedBlackPawn},
    {EmptySpace, EmptySpace, EmptySpace, EmptySpace, EmptySpace, EmptySpace, EmptySpace, EmptySpace},
    {EmptySpace, EmptySpace, EmptySpace, EmptySpace, EmptySpace, EmptySpace, EmptySpace, EmptySpace},
    {EmptySpace, EmptySpace, EmptySpace, EmptySpace, EmptySpace, EmptySpace, EmptySpace, EmptySpace},
    {EmptySpace, EmptySpace, EmptySpace, EmptySpace, EmptySpace, EmptySpace, EmptySpace, EmptySpace},
    {UnmovedWhitePawn, UnmovedWhitePawn, UnmovedWhitePawn, UnmovedWhitePawn, UnmovedWhitePawn, UnmovedWhitePawn, UnmovedWhitePawn, UnmovedWhitePawn},
    {WhiteRook, WhiteKnight, WhiteBishop, WhiteQueen, WhiteKing, WhiteBishop, WhiteKnight, WhiteRook}
    }
};

const std::map<std::pair<int_fast8_t, int_fast8_t>, std::vector<std::pair<int_fast8_t, int_fast8_t>>> defaultBlackLegalMoves
    {
    // Black Pawns
    {A7, {A6, A5}},
    {B7, {B6, B5}},
    {C7, {C6, C5}},
    {D7, {D6, D5}},
    {E7, {E6, E5}},
    {F7, {F6, F5}},
    {G7, {G6, G5}},
    {H7, {H6, H5}},
    // Black Knights
    {B8, {A6, C6}},
    {G8, {F6, H6}},
    };

const std::map<std::pair<int_fast8_t, int_fast8_t>, std::vector<std::pair<int_fast8_t, int_fast8_t>>> defaultWhiteLegalMoves

{
    // White Pawns
    {A2, {A3, A4}},
    {B2, {B3, B4}},
    {C2, {C3, C4}},
    {D2, {D3, D4}},
    {E2, {E3, E4}},
    {F2, {F3, F4}},
    {G2, {G3, G4}},
    {H2, {H3, H4}},
    // White Knights
    {B1, {B3, B4}},
    {G1, {F3, H3}},
};
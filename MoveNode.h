#pragma once

#include "BoardHandler.h"

inline BoardHandler handler;

class MoveNode
{
    public:
    MoveNode();
    MoveNode(ChessGame &cg);
    ~MoveNode();
    ChessGame *currentBoard;
    MoveNode *next;
};
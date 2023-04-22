#pragma once

#include "MoveNode.h"

struct GameHandler
{
    MoveNode* playerGame();
    std::pair<int_fast8_t, int_fast8_t> selectPiece(MoveNode *&currentMove);
    std::pair<int_fast8_t, int_fast8_t> selectMove(MoveNode *&currentMove, std::pair<int_fast8_t, int_fast8_t> &currentPiece);
    std::pair<int_fast8_t, int_fast8_t> parseInput(std::string &playerInput);
    void deleteGameStore(std::vector<MoveNode*> &gameStore);
};
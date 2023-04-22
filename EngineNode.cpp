#include "EngineNode.h"

EngineNode::EngineNode() : gameState(new ChessGame()), eval(NULL), boardID("") {}

// Simple Generation of Node using ChessGame object, performs very few logic checks
EngineNode::EngineNode(ChessGame &cg) : gameState(new ChessGame(cg)), eval(new Evaluation())
{
    // Copies board from previous
    this->gameState->whiteLegalMoves->clear();
    this->gameState->blackLegalMoves->clear();
    handler.calculateLegalMoves(*this->gameState);
}

EngineNode::EngineNode(const EngineNode &source) : eval(source.eval), boardID("")
{
    this->gameState = source.gameState;
    this->gameState->whiteLegalMoves->clear();
    this->gameState->blackLegalMoves->clear();
    handler.calculateLegalMoves(*this->gameState);
}

EngineNode::~EngineNode()
{
    delete this->gameState;
    delete this->eval;
    delete this->children;
}
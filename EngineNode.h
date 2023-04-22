#pragma once
#include <mutex>

#include "Evaluation.h"

class EngineNode
{
    public:
    EngineNode();
    EngineNode(const EngineNode &source);
    EngineNode(ChessGame &cg);
    ~EngineNode();
    std::mutex nodeLock;

    // Extracts relevant data from children before returning to higher level 
    void extractData(std::vector<EngineNode*>& childrenData)
    {
        for (int i = 0; i < childrenData.size(); i++)
        {
            *this += *childrenData[i]->eval;
        }
        this->eval->setCurrentEval();
    }
    // BoardID is the identifier used by the program to construct / deconstruct the Node
    // It is not assigned by instruction and must be manually assigned by the CodeHandler class (inherited by EngineAI)
    std::string boardID;
    ChessGame *gameState;
    std::vector<EngineNode*> *children;
    Evaluation *eval;

    // Extracts total white wins / black wins / draws from children, extracts current evaluation and
    // inputs it into map
    EngineNode& operator +=(Evaluation &rhs)
    {
        this->eval->whiteWins += rhs.whiteWins;
        this->eval->blackWins += rhs.blackWins;
        this->eval->gameDraws += rhs.gameDraws;
        this->eval->dataSet->insert(std::make_pair(eval->moves, rhs.currentEval));
        this->eval->moves++;
        return *this;
    } 
};
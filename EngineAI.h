#pragma once

#include "ThreadManager.h"

class EngineAI : public CodeHandler
{
    public:
    EngineAI();
    ~EngineAI();
    // BoardCode, EvaluationCode
    std::map<std::string, std::string> *database;
    void gatherData(double dataPoints, int level);
    EngineNode *head;

    protected:
    void processBranch(EngineNode*& currentNode);
    void generateBranch(EngineNode*& currentNode);
    void InsertData(EngineNode *& currentNode);
    double nodesEvaluated;
};
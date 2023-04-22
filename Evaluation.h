#pragma once

#include "GameHandler.h"

// Class contained inside of each EngineNode which contains it's own evaluation string (currentEval) along with
// logic to extract evaluation data from lower Nodes
class Evaluation 
{
    public:
    Evaluation() : whiteWins(false), blackWins(false), gameDraws(false), moves(0) {};
    ~Evaluation()
    {
        delete dataSet;
    }
    double moves;
    double whiteWins;
    double blackWins;
    double gameDraws;
    std::string currentEval;
    // Stores 'currentEval' string by Node index
    std::map<int, std::string> *dataSet;


    // Sets current eval
    void setCurrentEval()
    {
        this->currentEval.push_back(whiteWins);
        this->currentEval.push_back('W');
        this->currentEval.push_back(blackWins);
        this->currentEval.push_back('B');
        this->currentEval.push_back(gameDraws);
        this->currentEval.push_back('D');
    }
};
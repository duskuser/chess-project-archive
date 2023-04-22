#include "EngineAI.h"

// Generates 20 starting boards for each legal white move at the beginning of a game
EngineAI::EngineAI() : database(new std::map<std::string, std::string>), head(new EngineNode)
{
    this->head->boardID = this->generateCode(*head->gameState);
    // this->generateBranch(head);
}

EngineAI::~EngineAI() 
{
    delete this->database;
    delete this->head;
}

// Takes first Node not found in dataSet, uses InstructionHandler class to multithread searching through children
// Searches / generates to the bottom of its data set a determinate amount of times
// Level determines how far down the tree will search in it's initial pass through
void EngineAI::gatherData(double dataPoints, int level)
{
    // dataPoints += database->size();
    // double nodesFound = database->size();
    // while (nodesFound < dataPoints)
    // {
    //     for (auto &node : *this->head->children)
    //     {
    //         this->threads->push_back(std::thread(&EngineAI::processBranch, this, std::ref(node)));
    //     }
    //     // Join threads
    // }
}

// Generates new branch of moves if not already generated for specific node level
void EngineAI::generateBranch(EngineNode*& currentNode)
{
    auto it = this->database->find(currentNode->boardID);
    if (it == this->database->end())
    {
    if (!currentNode->gameState->gameWon)
    {
        // Handles move checking for White
        if (currentNode->gameState->whiteTurn)
        {
            if (currentNode->children->size() == 0)
            {
                auto it = currentNode->gameState->whiteLegalMoves->begin();
                while (it != currentNode->gameState->whiteLegalMoves->end())
                {
                    for (auto &move : it->second)
                    {
                        EngineNode *newNode = new EngineNode(*currentNode);
                        std::pair<std::pair<int_fast8_t, int_fast8_t>, std::pair<int_fast8_t, int_fast8_t>> moveSet;
                        moveSet.first = it->first;
                        moveSet.second = move;
                        handler.handleMove(*newNode->gameState->board, moveSet);
                        handler.updateLastMoves(*newNode->gameState->lastMoves, moveSet);
                        newNode->boardID = this->generateCode(*currentNode->gameState);
                        currentNode->children->push_back(newNode);
                    }
                }
            }
        }

        else
        {
            if (currentNode->children->size() == 0)
            {
                auto it = currentNode->gameState->blackLegalMoves->begin();
                while (it != currentNode->gameState->blackLegalMoves->end())
                {
                    for (auto &move : it->second)
                    {
                        EngineNode *newNode = new EngineNode(*currentNode);
                        std::pair<std::pair<int_fast8_t, int_fast8_t>, std::pair<int_fast8_t, int_fast8_t>> moveSet;
                        moveSet.first = it->first;
                        moveSet.second = move;
                        handler.handleMove(*newNode->gameState->board, moveSet);
                        handler.updateLastMoves(*newNode->gameState->lastMoves, moveSet);
                        currentNode->children->push_back(newNode);
                    }
                }
            }
        }
    }
    else
    {
        // Increments current evaluation counter to be extracted later before ending downward search
        // Adds to database
        std::cout << "Data found, adding to database" << "\n";
        switch (currentNode->gameState->gameState)
        {
            case WhiteWon:
            currentNode->eval->whiteWins++;
            break;

            case BlackWon:
            currentNode->eval->blackWins++;
            break;

            case GameDrawn:
            currentNode->eval->gameDraws++;
            break;
        }
        this->database->insert(
        std::pair<std::string, std::string>(currentNode->boardID, this->generateEvaluationCode(*currentNode->eval)));
    }
    }
}
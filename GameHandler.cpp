#include "GameHandler.h"

MoveNode* GameHandler::playerGame()
{
    MoveNode* gameStart = new MoveNode();
    MoveNode* currentMove = gameStart;
    while (!currentMove->currentBoard->gameWon)
    {
        std::pair<std::pair<int_fast8_t, int_fast8_t>, std::pair<int_fast8_t, int_fast8_t>> moveSet;
        moveSet.first = selectPiece(currentMove);
        moveSet.second = selectMove(currentMove, moveSet.first);
        std::cout << "Moving " << handler.translateToNotation(moveSet.first.first, moveSet.first.second) << " to " << 
        handler.translateToNotation(moveSet.second.first, moveSet.second.second) << "\n";
        handler.handleMove(*currentMove->currentBoard->board, moveSet);
        MoveNode *nextMove = new MoveNode(*currentMove->currentBoard);
        currentMove->next = nextMove;
        currentMove = nextMove;
    }
    if (currentMove->currentBoard->whiteTurn)
    {
        std::cout << "Black has won the game!" << "\n";
    }
    else
    {
        std::cout << "White has won the game!" << "\n";
    }
    return gameStart;
}

std::pair<int_fast8_t, int_fast8_t> GameHandler::selectPiece(MoveNode *&currentMove)
{
    std::pair<int_fast8_t, int_fast8_t> playerSelection;
    bool validInput = false;

    while (!validInput)
    {
        std::string squareSelection;
        std::cout << "Input selection: ";
        std::cin >> squareSelection;
        if (squareSelection.size() == 2)
        {
            playerSelection = parseInput(squareSelection);
            if (playerSelection.first == MOVE_ERROR)
            {
                std::cout << "Invalid input (moves are case sensitive)" << "\n";
            }
            else
            {

                if (currentMove->currentBoard->whiteTurn)
                {
                    auto it = currentMove->currentBoard->whiteLegalMoves->find(playerSelection);
                    if (it != currentMove->currentBoard->whiteLegalMoves->end())
                    {
                        validInput = true;
                        std::cout << "Legal moves for: " << squareSelection << "\n";
                        for (auto move : it->second)
                        {
                            std::cout << handler.translateToNotation(move.first, move.second) << " ";

                        }
                        std::cout << " " << std::endl;
                    }

                    else
                    {
                        std::cout << "Piece not found" << "\n";
                    }
                }
                else
                {
                    auto it = currentMove->currentBoard->blackLegalMoves->find(playerSelection);
                    if (it != currentMove->currentBoard->blackLegalMoves->end())
                    {
                        validInput = true;
                        std::cout << "Legal moves for: " << squareSelection << "\n";
                        for (auto move : it->second)
                        {
                            std::cout << handler.translateToNotation(move.first, move.second) << " ";

                        }
                        std::cout << " " << std::endl;
                    }

                    else 
                    {
                        std::cout << "Piece not found" << "\n";
                    }
                }
            }
        }
        else
        {
            std::cout << "Invalid input." << "\n";
        }
    }

    return playerSelection;
}

std::pair<int_fast8_t, int_fast8_t> GameHandler::selectMove(MoveNode *&currentMove, std::pair<int_fast8_t, int_fast8_t> &currentPiece)
{
    std::pair<int_fast8_t, int_fast8_t> playerSelection;
    bool validInput = false;

    while (!validInput)
    {
        std::string squareSelection;
        std::cout << "Input selection: ";
        std::cin >> squareSelection;
        if (squareSelection.size() == 2)
        {
            playerSelection = parseInput(squareSelection);
            if (playerSelection.first == MOVE_ERROR)
            {
                std::cout << "Invalid input (moves are case sensitive)" << "\n";
            }
            else
            {
                if (currentMove->currentBoard->whiteTurn)
                {
                    auto piece = currentMove->currentBoard->whiteLegalMoves->find(currentPiece);
                    if (piece != currentMove->currentBoard->whiteLegalMoves->end())
                    {
                        for (auto move : piece->second)
                        {
                            if (move == playerSelection)
                            {
                                validInput = true;
                            }
                        }
                        if (!validInput)
                        {
                            std::cout << "Illegal move" << "\n";
                        }
                        std::cout << " " << std::endl;
                    }
                    else
                    {
                        std::cout << "Error finding piece (something went wrong)" << "\n";
                    }

                }

                else
                {
                    auto piece = currentMove->currentBoard->blackLegalMoves->find(currentPiece);
                    if (piece != currentMove->currentBoard->blackLegalMoves->end())
                    {
                        for (auto move : piece->second)
                        {
                            if (move == playerSelection)
                            {
                                validInput = true;
                            }
                        }
                        if (!validInput)
                        {
                            std::cout << "Illegal move" << "\n";
                        }
                        std::cout << " " << std::endl;
                    }
                    else
                    {
                        std::cout << "Error finding piece (something went wrong)" << "\n";
                    }

                }
            }
        }
        else
        {
            std::cout << "Invalid input." << "\n";
        }
    }
    return playerSelection;
}

std::pair<int_fast8_t, int_fast8_t> GameHandler::parseInput(std::string &playerInput)
{
    std::pair<int_fast8_t, int_fast8_t> playerMove;
    switch (playerInput[0])
    {
        case 'A':
        playerMove.second = A1.second;
        break;

        case 'B':
        playerMove.second = B1.second;
        break;

        case 'C':
        playerMove.second = C1.second;
        break;

        case 'D':
        playerMove.second = D1.second;
        break;

        case 'E':
        playerMove.second = E1.second;
        break;

        case 'F':
        playerMove.second = F1.second;
        break;

        case 'G':
        playerMove.second = G1.second;
        break;

        case 'H':
        playerMove.second = H1.second;
        break;

        default:
        std::cout << "Letter error" << "\n";
        playerMove.first = MOVE_ERROR;
        return playerMove;
        break;

    }

    switch (playerInput[1])
    {
        case '1':
        playerMove.first = 7;
        break;

        case '2':
        playerMove.first = 6;
        break;

        case '3':
        playerMove.first = 5;
        break;

        case '4':
        playerMove.first = 4;
        break;

        case '5':
        playerMove.first = 3;
        break;

        case '6':
        playerMove.first = 2;
        break;

        case '7':
        playerMove.first = 1;
        break;

        case '8':
        playerMove.first = 0;
        break;

        default:
        std::cout << "Number error" << "\n";
        playerMove.first = MOVE_ERROR;
        return playerMove;
    }

    return playerMove;
}
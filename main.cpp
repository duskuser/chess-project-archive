#include "Engine.h"

enum UserInputs  : const int
{
    ExitProgram = 0, SinglePlayer = 1, EngineTest = 2
};

std::vector<MoveNode*> gameStore;
inline GameHandler gameHandler;

void testEngine();
int promptUser();

int main()
{
    bool usingProgram = true;
    while (usingProgram)
    {
        switch (promptUser())
        {
            case ExitProgram:
            usingProgram = false;
            break;

            case SinglePlayer:
            gameStore.push_back(gameHandler.playerGame());
            break;

            case EngineTest:
            testEngine();
            break;
        }
    }

    // deleteGame(gameStart);
}

int promptUser()
{
    int userChoice;
    bool choiceMade;
    while (!choiceMade)
    {
        std::cout << "Choose Game Type:\n" << "0. Exit Program" << "\n" << 
        "1. Play Normal Chess Game" << 
        "\n" << "2. Test Engine " << "\n";
        std::cin >> userChoice;
        choiceMade = true;
    }

    return userChoice;
}   

void testEngine()
{
    std::cout << "Creating engine..." << "\n";
    Engine *engine = new Engine();
    std::cout << engine->head->boardID << "\n";
    delete engine;
}

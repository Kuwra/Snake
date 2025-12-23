#include <iostream>
#include "GameController.h"

int main()
{
    try
    {
        GameController game;

        std::string difficulty;
        std::cout << "Choose difficulty (easy, normal, hard): ";
        std::cin >> difficulty;
        game.setDifficulty(difficulty);

        game.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

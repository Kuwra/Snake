#include <iostream>
#include "GameController.h"

int main()
{
    try
    {
        GameController game;
        game.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Food.h"
class GameController
{
public:
    GameController();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void handleInput(sf::Keyboard::Key key);
    void showMenu();
    bool showGameOverScreen();
    void resetGame();

    sf::RenderWindow window;
    Snake snake;
    Food food;
    int score;
    sf::Font font;
    sf::Text scoreText;
    bool gameOver;
    float speed; 
};


#endif // GAMECONTROLLER_H

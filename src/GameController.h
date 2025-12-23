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
    void setDifficulty(const std::string &difficulty); // Dodane do ustawiania poziomu trudności

private:
    void processEvents();
    void update();
    void render();
    void handleInput(sf::Keyboard::Key key);

    sf::RenderWindow window;
    Snake snake;
    Food food;
    int score;
    sf::Font font;
    sf::Text scoreText;
    bool gameOver;
    float speed; // Dodane do ustawiania prędkości gry
};

#endif // GAMECONTROLLER_H

#include "GameController.h"

GameController::GameController()
        : window(sf::VideoMode(800, 600), "Snake Game"),
          score(0),
          gameOver(false),
          speed(0.1f) // Domyślna prędkość
{
    window.setFramerateLimit(10);

    if (!font.loadFromFile("../resources/font/tuffy.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(700, 10);
}

void GameController::run()
{
    sf::Clock clock;
    while (window.isOpen())
    {
        processEvents();
        if (!gameOver)
        {
            if (clock.getElapsedTime().asSeconds() > speed)
            {
                update();
                clock.restart();
            }
        }
        render();
    }
}

void GameController::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            handleInput(event.key.code);
        }
    }
}

void GameController::update()
{
    snake.move();

    if (snake.checkCollision() || snake.checkWallCollision(window.getSize()))
    {
        gameOver = true;
    }

    if (snake.getPosition() == food.getPosition())
    {
        snake.grow();
        food.spawn();
        score++;
    }

    scoreText.setString("Score: " + std::to_string(score));
}

void GameController::render()
{
    window.clear(sf::Color::White);

    if (gameOver)
    {
        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setString("You lose");
        gameOverText.setCharacterSize(50);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setPosition(250, 250);
        window.draw(gameOverText);
    }
    else
    {
        snake.draw(window);
        food.draw(window);
        window.draw(scoreText);
    }

    window.display();
}

void GameController::handleInput(sf::Keyboard::Key key)
{
    switch (key)
    {
        case sf::Keyboard::W:
            snake.setDirection(sf::Keyboard::Up);
            break;
        case sf::Keyboard::S:
            snake.setDirection(sf::Keyboard::Down);
            break;
        case sf::Keyboard::A:
            snake.setDirection(sf::Keyboard::Left);
            break;
        case sf::Keyboard::D:
            snake.setDirection(sf::Keyboard::Right);
            break;
        default:
            break;
    }
}

void GameController::setDifficulty(const std::string &difficulty)
{
    if (difficulty == "easy")
    {
        speed = 0.15f;
    }
    else if (difficulty == "normal")
    {
        speed = 0.1f;
    }
    else if (difficulty == "hard")
    {
        speed = 0.05f;
    }
}

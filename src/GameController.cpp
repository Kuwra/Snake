#include "GameController.h"

GameController::GameController()
    : window(sf::VideoMode(800, 600), "Snake Game"),
      score(0),
      gameOver(false),
      speed(0.1f)
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
void GameController::showMenu()
{
    sf::Text easyText, normalText, hardText;
    
    easyText.setFont(font);
    easyText.setString("Easy");
    easyText.setCharacterSize(40);
    easyText.setFillColor(sf::Color::Green);
    easyText.setPosition(350, 200);

    normalText.setFont(font);
    normalText.setString("Normal");
    normalText.setCharacterSize(40);
    normalText.setFillColor(sf::Color::Blue);
    normalText.setPosition(320, 280);

    hardText.setFont(font);
    hardText.setString("Hard");
    hardText.setCharacterSize(40);
    hardText.setFillColor(sf::Color::Red);
    hardText.setPosition(350, 360);

    bool inMenu = true;
    while (window.isOpen() && inMenu)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return;
            }
            
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                
                if (easyText.getGlobalBounds().contains(mousePos))
                {
                    speed = 0.15f;
                    inMenu = false;
                }
                else if (normalText.getGlobalBounds().contains(mousePos))
                {
                    speed = 0.1f;
                    inMenu = false;
                }
                else if (hardText.getGlobalBounds().contains(mousePos))
                {
                    speed = 0.05f;
                    inMenu = false;
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(easyText);
        window.draw(normalText);
        window.draw(hardText);
        window.display();
    }
}

void GameController::run()
{
    showMenu();

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
            window.close();
        else if (event.type == sf::Event::KeyPressed)
            handleInput(event.key.code);
    }
}

void GameController::update()
{
    snake.move();
    
    if (snake.checkCollision() || snake.checkWallCollision(window.getSize()))
        gameOver = true;

    if (snake.getPosition() == food.getPosition())
    {
        snake.grow();
        food.spawn();
        score++;
        scoreText.setString("Score: " + std::to_string(score));
    }
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
        case sf::Keyboard::Up:
            snake.setDirection(sf::Keyboard::Up);
            break;
        case sf::Keyboard::S:
        case sf::Keyboard::Down:
            snake.setDirection(sf::Keyboard::Down);
            break;
        case sf::Keyboard::A:
        case sf::Keyboard::Left:
            snake.setDirection(sf::Keyboard::Left);
            break;
        case sf::Keyboard::D:
        case sf::Keyboard::Right:
            snake.setDirection(sf::Keyboard::Right);
            break;
        default:
            break;
    }
}

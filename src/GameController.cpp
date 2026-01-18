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
    normalText.setPosition(330, 280);

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
    resetGame();               

    sf::Clock clock;
    while (window.isOpen())
    {
        
        if (!gameOver)
        {
                    processEvents();

            if (clock.getElapsedTime().asSeconds() > speed)
            {
                update();
                clock.restart();
            }
        render();
        }
        else
        {
            const bool restart = showGameOverScreen();
            if (!window.isOpen()) return;
 
            if (restart)
            {
                resetGame();    
                clock.restart();
            }
            else
            {
                window.close();
            }
        }
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


    if (directionQueued)
    {
        snake.setDirection(pendingDirection); 
        directionQueued = false;              
    }

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
    snake.draw(window);
    food.draw(window);
    window.draw(scoreText);
    window.display();
}

void GameController::handleInput(sf::Keyboard::Key key)
{
    if (directionQueued)
        return;

    sf::Keyboard::Key desired;
    bool isDirectionKey = true;

    switch (key)
    {
        case sf::Keyboard::W:
        case sf::Keyboard::Up:
            desired = sf::Keyboard::Up;
            break;

        case sf::Keyboard::S:
        case sf::Keyboard::Down:
            desired = sf::Keyboard::Down;
            break;

        case sf::Keyboard::A:
        case sf::Keyboard::Left:
            desired = sf::Keyboard::Left;
            break;

        case sf::Keyboard::D:
        case sf::Keyboard::Right:
            desired = sf::Keyboard::Right;
            break;

        default:
            isDirectionKey = false;
            break;
    }

    if (!isDirectionKey)
        return;


    if (!snake.canChangeDirection(desired))
        return;

    pendingDirection = desired;
    directionQueued = true;
}

bool GameController::showGameOverScreen()
{
    sf::Text title, restartText, closeText;

    title.setFont(font);
    title.setString("Game Over");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::Red);
    title.setPosition(270.f, 180.f);

    restartText.setFont(font);
    restartText.setString("Restart");
    restartText.setCharacterSize(40);
    restartText.setFillColor(sf::Color::Green);
    restartText.setPosition(330.f, 290.f);

    closeText.setFont(font);
    closeText.setString("Close Game");
    closeText.setCharacterSize(40);
    closeText.setFillColor(sf::Color::Blue);
    closeText.setPosition(290.f, 370.f);

    bool waiting = true;

    while (window.isOpen() && waiting)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return false;
            }

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePos((float)event.mouseButton.x, (float)event.mouseButton.y);

                if (restartText.getGlobalBounds().contains(mousePos))
                    return true;

                if (closeText.getGlobalBounds().contains(mousePos))
                    return false;
            }
        }

        window.clear(sf::Color::White);
        window.draw(title);
        window.draw(restartText);
        window.draw(closeText);
        window.display();
    }

    return false;
}

void GameController::resetGame()
{

    gameOver = false;        
    score = 0;

    snake.reset();           
    food.spawn();            

    scoreText.setString("Score: 0"); 
}

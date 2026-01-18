#include "Snake.h"

Snake::Snake()
{
    headTextureUp.loadFromFile("../resources/textures/head_up.png");
    headTextureDown.loadFromFile("../resources/textures/head_down.png");
    headTextureLeft.loadFromFile("../resources/textures/head_left.png");
    headTextureRight.loadFromFile("../resources/textures/head_right.png");

    bodyTextureHorizontal.loadFromFile("../resources/textures/body_horizontal.png");
    bodyTextureVertical.loadFromFile("../resources/textures/body_vertical.png");
    bodyTextureTopLeft.loadFromFile("../resources/textures/body_topleft.png");
    bodyTextureTopRight.loadFromFile("../resources/textures/body_bottomleft.png");
    bodyTextureBottomLeft.loadFromFile("../resources/textures/body_topright.png");
    bodyTextureBottomRight.loadFromFile("../resources/textures/body_bottomright.png");

    tailTextureUp.loadFromFile("../resources/textures/tail_down.png");
    tailTextureDown.loadFromFile("../resources/textures/tail_up.png");
    tailTextureLeft.loadFromFile("../resources/textures/tail_right.png");
    tailTextureRight.loadFromFile("../resources/textures/tail_left.png");

    sf::RectangleShape segment(sf::Vector2f(20.0f, 20.0f));
    segment.setTexture(&headTextureRight);
    segment.setPosition(400, 300);
    body.push_back(segment);

    direction = sf::Vector2f(20.0f, 0.0f);
}

void Snake::move()
{
    for (size_t i = body.size() - 1; i > 0; --i)
    {
        body[i].setPosition(body[i - 1].getPosition());
    }
    body[0].move(direction);
    updateTextures();
}

void Snake::grow()
{
    sf::RectangleShape newSegment(sf::Vector2f(20.0f, 20.0f));
    newSegment.setPosition(body.back().getPosition());
    body.push_back(newSegment);
    updateTextures();
}

bool Snake::checkCollision()
{
    for (size_t i = 1; i < body.size(); ++i)
    {
        if (body[0].getPosition() == body[i].getPosition())
            return true;
    }
    return false;
}

bool Snake::checkWallCollision(sf::Vector2u windowSize)
{
    sf::Vector2f position = body[0].getPosition();
    if (position.x < 0 || position.x >= windowSize.x || position.y < 0 || position.y >= windowSize.y)
    {
        return true;
    }
    return false;
}

void Snake::setDirection(sf::Keyboard::Key key)
{
    switch (key)
    {
        case sf::Keyboard::Up:
            if (direction.y == 0)
                direction = sf::Vector2f(0.0f, -20.0f);
            break;
        case sf::Keyboard::Down:
            if (direction.y == 0)
                direction = sf::Vector2f(0.0f, 20.0f);
            break;
        case sf::Keyboard::Left:
            if (direction.x == 0)
                direction = sf::Vector2f(-20.0f, 0.0f);
            break;
        case sf::Keyboard::Right:
            if (direction.x == 0)
                direction = sf::Vector2f(20.0f, 0.0f);
            break;
        default:
            break;
    }
}
bool Snake::canChangeDirection(sf::Keyboard::Key key) const
{
    switch (key)
    {
        case sf::Keyboard::Up:
        case sf::Keyboard::Down:
            return direction.y == 0;

        case sf::Keyboard::Left:
        case sf::Keyboard::Right:
            return direction.x == 0;

        default:
            return false;
    }
}
sf::Vector2f Snake::getPosition() const
{
    return body[0].getPosition();
}

void Snake::draw(sf::RenderWindow &window)
{
    for (const auto &segment : body)
    {
        window.draw(segment);
    }
}

void Snake::updateTextures()
{
    if (body.size() > 1)
    {
        // Ustawianie tekstury głowy
        if (direction.x > 0)
            body[0].setTexture(&headTextureRight);
        else if (direction.x < 0)
            body[0].setTexture(&headTextureLeft);
        else if (direction.y > 0)
            body[0].setTexture(&headTextureDown);
        else if (direction.y < 0)
            body[0].setTexture(&headTextureUp);

        // Ustawianie tekstury ogona
        sf::Vector2f tailDirection = body[body.size() - 2].getPosition() - body.back().getPosition();
        if (tailDirection.x > 0) {
            body.back().setTexture(&tailTextureRight);
            body.back().setRotation(0);
        } else if (tailDirection.x < 0) {
            body.back().setTexture(&tailTextureLeft);
            body.back().setRotation(0);
        } else if (tailDirection.y > 0) {
            body.back().setTexture(&tailTextureDown);
            body.back().setRotation(0);
        } else if (tailDirection.y < 0) {
            body.back().setTexture(&tailTextureUp);
            body.back().setRotation(0);
        }

        // Ustawianie tekstur ciała
        for (size_t i = 1; i < body.size() - 1; ++i)
        {
            sf::Vector2f prevSegment = body[i - 1].getPosition() - body[i].getPosition();
            sf::Vector2f nextSegment = body[i + 1].getPosition() - body[i].getPosition();

            if (prevSegment.x == nextSegment.x) {
                body[i].setTexture(&bodyTextureVertical);
                body[i].setRotation(0);
            } else if (prevSegment.y == nextSegment.y) {
                body[i].setTexture(&bodyTextureHorizontal);
                body[i].setRotation(0);
            } else if ((prevSegment.x > 0 && nextSegment.y < 0) || (prevSegment.y < 0 && nextSegment.x > 0)) {
                body[i].setTexture(&bodyTextureBottomLeft);
                body[i].setRotation(0);
            } else if ((prevSegment.x < 0 && nextSegment.y < 0) || (prevSegment.y < 0 && nextSegment.x < 0)) {
                body[i].setTexture(&bodyTextureTopLeft);
                body[i].setRotation(0);
            } else if ((prevSegment.x > 0 && nextSegment.y > 0) || (prevSegment.y > 0 && nextSegment.x > 0)) {
                body[i].setTexture(&bodyTextureBottomRight);
                body[i].setRotation(0);
            } else if ((prevSegment.x < 0 && nextSegment.y > 0) || (prevSegment.y > 0 && nextSegment.x < 0)) {
                body[i].setTexture(&bodyTextureTopRight);
                body[i].setRotation(0);
            }
        }
    }
    else
    {
        // Jeśli wąż ma tylko głowę, ustawiamy tylko teksturę głowy
        if (direction.x > 0)
            body[0].setTexture(&headTextureRight);
        else if (direction.x < 0)
            body[0].setTexture(&headTextureLeft);
        else if (direction.y > 0)
            body[0].setTexture(&headTextureDown);
        else if (direction.y < 0)
            body[0].setTexture(&headTextureUp);
    }
}
void Snake::reset()
{
    body.clear();

    sf::RectangleShape segment(sf::Vector2f(20.0f, 20.0f));
    segment.setTexture(&headTextureRight);
    segment.setPosition(400, 300);
    body.push_back(segment);

    direction = sf::Vector2f(20.0f, 0.0f);
    updateTextures();
}

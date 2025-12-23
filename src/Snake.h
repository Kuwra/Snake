#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <deque>

class Snake
{
public:
    Snake();
    void move();
    void grow();
    bool checkCollision();
    bool checkWallCollision(sf::Vector2u windowSize);
    void setDirection(sf::Keyboard::Key key);
    sf::Vector2f getPosition() const;
    void draw(sf::RenderWindow &window);

private:
    std::deque<sf::RectangleShape> body;
    sf::Vector2f direction;

    sf::Texture headTextureUp;
    sf::Texture headTextureDown;
    sf::Texture headTextureLeft;
    sf::Texture headTextureRight;

    sf::Texture bodyTextureHorizontal;
    sf::Texture bodyTextureVertical;
    sf::Texture bodyTextureTopLeft;
    sf::Texture bodyTextureTopRight;
    sf::Texture bodyTextureBottomLeft;
    sf::Texture bodyTextureBottomRight;

    sf::Texture tailTextureUp;
    sf::Texture tailTextureDown;
    sf::Texture tailTextureLeft;
    sf::Texture tailTextureRight;

    void updateTextures();
};

#endif // SNAKE_H

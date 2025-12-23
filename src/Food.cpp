#include "Food.h"

Food::Food()
{
    texture.loadFromFile("../resources/textures/apple.png");
    food.setRadius(10.0f);
    food.setTexture(&texture);
    spawn();
}

void Food::spawn()
{
    int x = rand() % 40 * 20;
    int y = rand() % 30 * 20;
    food.setPosition(x, y);
}

void Food::draw(sf::RenderWindow &window)
{
    window.draw(food);
}

sf::Vector2f Food::getPosition() const
{
    return food.getPosition();
}

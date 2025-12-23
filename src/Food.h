#ifndef FOOD_H
#define FOOD_H

#include <SFML/Graphics.hpp>

class Food
{
public:
    Food();
    void spawn();
    void draw(sf::RenderWindow &window);
    sf::Vector2f getPosition() const;

private:
    sf::CircleShape food;
    sf::Texture texture;
};

#endif // FOOD_H

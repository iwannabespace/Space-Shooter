#pragma once

#include <SFML/Graphics.hpp>

class SpaceBomb
{
private:
    sf::Clock timer_clock;
    sf::Texture textures[3];
    sf::Sprite sprite;
    int win_width;
    int win_height;
    int pos;
    bool is_alive;
public:
    SpaceBomb(int win_width, int win_height);
    ~SpaceBomb();
    void reset();
    void setAlive(bool is_alive);
    void update();
    void draw(sf::RenderWindow& window) const;
    sf::Sprite getSprite() const;
    bool getAlive() const;
};
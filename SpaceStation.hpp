#pragma once

#include <SFML/Graphics.hpp>

class SpaceStation
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
    SpaceStation(int win_width, int win_height);
    ~SpaceStation();
    void reset();
    void update();
    void draw(sf::RenderWindow& window) const;
    void setAlive(bool is_alive);
    sf::Sprite getSprite() const;
    bool getAlive() const;
};
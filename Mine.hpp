#pragma once

#include <SFML/Graphics.hpp>

class Mine
{
private:
    sf::Clock timer_clock;
    sf::Texture textures[2];
    sf::Sprite sprite;
    int win_width;
    int win_height;
    int pos;
    bool is_alive;
public:
    Mine(int win_width, int win_height);
    ~Mine();
    void reset();
    void setAlive(bool is_alive);
    void update();
    void draw(sf::RenderWindow& window) const;
    sf::Sprite getSprite() const;
    bool getAlive() const;
};
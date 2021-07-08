#pragma once

#include <SFML/Graphics.hpp>
#include "Pilot.hpp"

class Pilot;

class BatPlane
{
private:
    sf::Clock timer_clock;
    sf::Clock timer_for_shooting;
    sf::Texture textures_of_plane[4];
    sf::Texture texture_of_bullet;
    sf::Sprite sprite_of_plane;
    sf::Sprite sprite_of_bullet;
    int win_width;
    int win_height;
    int pos;
    bool is_alive;
public:
    BatPlane(int win_width, int win_height);
    ~BatPlane();
    void reset();
    void setAlive(bool is_alive);
    void update(Pilot& pilot);
    void draw(sf::RenderWindow& window, const Pilot& pilot) const;
    sf::Sprite getSprite() const;
    bool getAlive() const;
};
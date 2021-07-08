#pragma once

#include <SFML/Graphics.hpp>
#include "Pilot.hpp"

class Pilot;

class SmallPlane
{
private:
    sf::Clock timer_clock;
    sf::Clock timer_for_shooting;
    sf::Texture textures_of_plane[5];
    sf::Texture texture_of_bullet;
    sf::Sprite sprite_of_plane;
    sf::Sprite sprite_of_bullet;
    int win_width;
    int win_height;
    int pos;
    bool is_alive;
public:
    SmallPlane(int win_width, int win_height);
    ~SmallPlane();
    void reset();
    void setAlive(bool is_alive);
    void update(Pilot& pilot);
    void draw(sf::RenderWindow& window, const Pilot& pilot) const;
    sf::Sprite getSprite() const;
    bool getAlive() const;
};
#include "SpaceStation.hpp"
#include <cstdlib>

SpaceStation::SpaceStation(int win_width, int win_height)
    : win_width(win_width), win_height(win_height), pos(0),
        is_alive(true)
{
    for (int i = 0; i < 3; i++)
        textures[i].loadFromFile(std::string("resimler/uzay/comm/" + std::to_string(i + 1) + ".png"));

    sprite.setScale({ 0.05f, 0.05f });
    sprite.setPosition({ static_cast<float>(std::rand() % (this->win_width - 50)) + 50.f, 10.f });
}

SpaceStation::~SpaceStation()
{

}

void SpaceStation::reset()
{
    sprite.setPosition({ static_cast<float>(std::rand() % (this->win_width - 50)) + 50.f, 10.f });
    is_alive = true;
}

void SpaceStation::update()
{
    if (is_alive)
    {
        if (timer_clock.getElapsedTime().asSeconds() > 0.1f)
        {
            sprite.setTexture(textures[pos++]);
            timer_clock.restart();

            if (pos == 3)
                pos = 0;
        }

        sprite.move({ 0.f, 0.4f });
    }
}

void SpaceStation::draw(sf::RenderWindow& window) const
{
    if (sprite.getPosition().y < win_height + sprite.getGlobalBounds().height && is_alive)
        window.draw(sprite);
}

void SpaceStation::setAlive(bool is_alive)
{
    this->is_alive = is_alive;
}

sf::Sprite SpaceStation::getSprite() const
{
    return sprite;
}

bool SpaceStation::getAlive() const
{
    return is_alive;
}
#include "Mine.hpp"

Mine::Mine(int win_width, int win_height)
    : win_width(win_width), win_height(win_height), pos(0),
        is_alive(true)
{
    for (int i = 0; i < 2; i++)
        textures[i].loadFromFile(std::string("resimler/uzay/Spacemines/" + std::to_string(i + 1) + ".png"));

    sprite.setScale({ 0.2f, 0.2f });
    sprite.setPosition({ static_cast<float>(std::rand() % (this->win_width - 50)) + 50.f, 10.f });
}

Mine::~Mine()
{

}

void Mine::reset()
{
    sprite.setPosition({ static_cast<float>(std::rand() % (this->win_width - 50)) + 50.f, 10.f });
    is_alive = true;
}

void Mine::setAlive(bool is_alive)
{
    this->is_alive = is_alive;
}

void Mine::update()
{
    if (is_alive)
    {
        if (timer_clock.getElapsedTime().asSeconds() > 0.1f)
        {
            sprite.setTexture(textures[pos++]);
            timer_clock.restart();

            if (pos == 2)
                pos = 0;
        }

        sprite.move({ 0.f, 0.4f });
    }
}

void Mine::draw(sf::RenderWindow& window) const
{
    if (is_alive)
        window.draw(sprite);
}

sf::Sprite Mine::getSprite() const
{
    return sprite;
}

bool Mine::getAlive() const
{
    return is_alive;
}
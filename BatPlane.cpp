#include "BatPlane.hpp"

BatPlane::BatPlane(int win_width, int win_height)
    : win_width(win_width), win_height(win_height), pos(0),
        is_alive(true)
{
    for (int i = 0; i < 4; i++)
        textures_of_plane[i].loadFromFile(std::string("resimler/uzay/yarasaucak/" + std::to_string(i + 1) + ".png"));
    
    texture_of_bullet.loadFromFile(std::string("resimler/uzay/bullet_red.png"));
    
    sprite_of_plane.setScale({ 0.1f, 0.1f });
    sprite_of_plane.setPosition({ static_cast<float>(std::rand() % (this->win_width - 50)) + 50.f, 10.f });
    sprite_of_plane.rotate(180);

    sprite_of_bullet.setTexture(texture_of_bullet);
    sprite_of_bullet.setScale({ 0.5f, 0.5f });
    sprite_of_bullet.setPosition({ sprite_of_plane.getPosition().x + 10.f, sprite_of_plane.getPosition().y + 45.f });
    sprite_of_bullet.rotate(180);
}

BatPlane::~BatPlane()
{

}

void BatPlane::reset()
{
    sprite_of_plane.setPosition({ static_cast<float>(std::rand() % (this->win_width - 50)) + 50.f, 10.f });
    sprite_of_bullet.setPosition({ sprite_of_plane.getPosition().x + 10.f, sprite_of_plane.getPosition().y + 45.f });
    is_alive = true;
}

void BatPlane::setAlive(bool is_alive)
{
    this->is_alive = is_alive;
}

void BatPlane::update(Pilot& pilot)
{
    if (timer_clock.getElapsedTime().asSeconds() > 0.3f)
    {
        sprite_of_plane.setTexture(textures_of_plane[pos++]);
        timer_clock.restart();

        if (pos == 4)
            pos = 0;
    }

    //if (timer_for_shooting.getElapsedTime().asSeconds() > 5.f)
    //{
        if (sprite_of_bullet.getPosition().y > win_height + sprite_of_bullet.getGlobalBounds().height)
        {
            sprite_of_bullet.setPosition({ sprite_of_plane.getPosition().x + 10.f, sprite_of_plane.getPosition().y + 45.f });
            timer_for_shooting.restart();
        }
    //}

    if (sprite_of_bullet.getGlobalBounds().contains(pilot.getSprite().getPosition()))
    {
        pilot.setAlive(false);
        sprite_of_bullet.setPosition({ sprite_of_plane.getPosition().x + 10.f, sprite_of_plane.getPosition().y + 45.f });
    }

    if (pilot.getAlive())
    {
        sprite_of_plane.move({ 0.f, 0.4f });
        sprite_of_bullet.move({ 0.f, 1.f });
    }
}

void BatPlane::draw(sf::RenderWindow& window, const Pilot& pilot) const
{
    if (is_alive)
    {
        window.draw(sprite_of_plane);
        window.draw(sprite_of_bullet);
    }
}

sf::Sprite BatPlane::getSprite() const
{
    return sprite_of_plane;
}

bool BatPlane::getAlive() const
{
    return is_alive;
}
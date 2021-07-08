#include "Pilot.hpp"

Pilot::Pilot(int win_width, int win_height)
    : win_width(win_width), win_height(win_height), score(0),
        pos(0), anim_pos(0), pos_for_bullets(0), max_bullets(1000), which(-1),
        is_alive(true), animate(false), who("")
{
    for (int i = 0; i < 8; i++)
        textures_for_pilot[i].loadFromFile(std::string("resimler/uzay/user/" + std::to_string(i + 1) + ".png"));

    texture_for_bullet.loadFromFile(std::string("resimler/uzay/bullet.png"));

    sprite_for_pilot.setScale({ 0.1f, 0.1f });
    sprite_for_pilot.setPosition({ win_width / 2.f, win_height - 50.f });

    sprite_for_bullet.setTexture(texture_for_bullet);
    sprite_for_bullet.setScale({ 0.5f, 0.5f });

    for (int i = 0; i < max_bullets; i++)
        bullets.push_back(std::make_pair(sprite_for_bullet, false));
    
    for (int i = 0; i < 16; i++)
        anim_textures[i].loadFromFile(std::string("resimler/uzay/Effects/1_" + std::to_string(i) + ".png"));

    anim_sprite.setScale({ 0.4f, 0.4f });
}

Pilot::~Pilot()
{

}

void Pilot::setAlive(bool is_alive)
{
    this->is_alive = is_alive;
}

void Pilot::update(std::vector<SpaceStation>& stations, std::vector<SmallPlane*>& planes, std::vector<BatPlane*>& bat_planes,
        std::vector<Mine>& mines, std::vector<SpaceBomb>& bombs)
{
    if (is_alive)
    {
        if (timer_clock.getElapsedTime().asSeconds() > 0.1f)
        {
            sprite_for_pilot.setTexture(textures_for_pilot[pos++]);
            timer_clock.restart();

            if (pos == 8)
                pos = 0;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            sprite_for_pilot.move({ -1.f, 0.f });

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            sprite_for_pilot.move({ 1.f, 0.f });
    }

    for (std::pair<sf::Sprite, bool>& pair : bullets)
    {
        if (pair.second)
        {
            for (int i = 0; i < stations.size(); i++)
                if (pair.first.getGlobalBounds().contains(stations.at(i).getSprite().getPosition()) && stations.at(i).getAlive())
                {
                    animate = true;
                    pair.second = false;
                    stations.at(i).setAlive(false);
                    which = i;
                    who = "station";
                }

            for (int i = 0; i < planes.size(); i++)
                if (pair.first.getGlobalBounds().contains(planes.at(i)->getSprite().getPosition()) && planes.at(i)->getAlive())
                {
                    animate = true;
                    pair.second = false;
                    planes.at(i)->setAlive(false);
                    which = i;
                    who = "small_plane";
                }

            for (int i = 0; i < bat_planes.size(); i++)
                if (pair.first.getGlobalBounds().contains(bat_planes.at(i)->getSprite().getPosition()) && bat_planes.at(i)->getAlive())
                {
                    animate = true;
                    pair.second = false;
                    bat_planes.at(i)->setAlive(false);
                    which = i;
                    who = "bat_plane";
                }

            for (int i = 0; i < mines.size(); i++)
                if (pair.first.getGlobalBounds().contains(mines.at(i).getSprite().getPosition()) && mines.at(i).getAlive())
                {
                    animate = true;
                    pair.second = false;
                    mines.at(i).setAlive(false);
                    which = i;
                    who = "mine";
                }

            for (int i = 0; i < bombs.size(); i++)
                if (pair.first.getGlobalBounds().contains(bombs.at(i).getSprite().getPosition()) && bombs.at(i).getAlive())
                {
                    animate = true;
                    pair.second = false;
                    bombs.at(i).setAlive(false);
                    which = i;
                    who = "bomb";
                }

            pair.first.move({ 0.f, -1.f });
        }
    }

    if (animate)
    {
        if (who == "station")
            Animate({ stations.at(which).getSprite().getPosition().x - 20.f, stations.at(which).getSprite().getPosition().y - 14.f });

        else if (who == "small_plane")
            Animate({ planes.at(which)->getSprite().getPosition().x - 50.f, planes.at(which)->getSprite().getPosition().y - 40.f });

        else if (who == "bat_plane")
            Animate({ bat_planes.at(which)->getSprite().getPosition().x - 50.f, bat_planes.at(which)->getSprite().getPosition().y - 40.f });

        else if (who == "mine")
            Animate({ mines.at(which).getSprite().getPosition().x - 50.f, mines.at(which).getSprite().getPosition().y - 40.f });

        else if (who == "bomb")
            Animate({ bombs.at(which).getSprite().getPosition().x - 50.f, bombs.at(which).getSprite().getPosition().y - 40.f });

        if (anim_pos == 16)
        {
            animate = false;
            anim_pos = 0;
        }
    }
}

void Pilot::control_bullets()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        bullets[pos_for_bullets].first.setPosition({ sprite_for_pilot.getPosition().x - 7.f, sprite_for_pilot.getPosition().y - 45.f });
        bullets[pos_for_bullets++].second = true;

        if (pos_for_bullets == 500)
            pos_for_bullets = 0;
    }
}

void Pilot::draw(sf::RenderWindow& window) const
{
    if (is_alive)
        window.draw(sprite_for_pilot);

    for (const std::pair<sf::Sprite, bool>& pair : bullets)
        if (pair.second)
            window.draw(pair.first);

    if (animate)
        window.draw(anim_sprite);
}

sf::Sprite Pilot::getSprite() const
{
    return sprite_for_pilot;
}

bool Pilot::getAlive() const
{
    return is_alive;
}

void Pilot::Animate(sf::Vector2f pos)
{
    anim_sprite.setPosition(pos);

    if (anim_clock.getElapsedTime().asSeconds() > 0.05f)
    {
        anim_sprite.setTexture(anim_textures[anim_pos++]);
        anim_clock.restart();
    }
}
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>

#include "SpaceStation.hpp"
#include "SmallPlane.hpp"
#include "BatPlane.hpp"
#include "Mine.hpp"
#include "SpaceBomb.hpp"

class SmallPlane;
class BatPlane;

class Pilot
{
private:
	sf::Clock timer_clock;
	sf::Texture textures_for_pilot[8];
	sf::Texture texture_for_bullet;
	sf::Sprite sprite_for_pilot;
	sf::Sprite sprite_for_bullet;
	std::vector<std::pair<sf::Sprite, bool>> bullets;
	int win_width;
	int win_height;
	int pos;
	int pos_for_bullets;
	int max_bullets;
	int score;
	int which;
	bool is_alive;
	bool animate;
	std::string who;
private:
	sf::Clock anim_clock;
	sf::Texture anim_textures[16];
	sf::Sprite anim_sprite;
	int anim_pos;
public:
	Pilot(int win_width, int win_height);
	~Pilot();
	void setAlive(bool is_alive);
	void update(std::vector<SpaceStation>& stations, std::vector<SmallPlane*>& planes, std::vector<BatPlane*>& bat_planes,
			std::vector<Mine>& mines, std::vector<SpaceBomb>& bombs);
	void control_bullets();
	void draw(sf::RenderWindow& window) const;
	sf::Sprite getSprite() const;
	bool getAlive() const;
private:
	void Animate(sf::Vector2f pos);
};
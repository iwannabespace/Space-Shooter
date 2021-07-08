#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Pilot.hpp"
#include "SpaceStation.hpp"
#include "SmallPlane.hpp"
#include "BatPlane.hpp"
#include "Mine.hpp"
#include "SpaceBomb.hpp"

int main()
{
	std::srand(std::time(0));

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(400, 700), "SFML Game", sf::Style::Close, settings);
	window.setFramerateLimit(70);

	Pilot pilot(400, 700);

	std::vector<SpaceStation> stations;
	std::vector<SmallPlane*> planes;
	std::vector<BatPlane*> bat_planes;
	std::vector<Mine> mines;
	std::vector<SpaceBomb> bombs;

	stations.push_back(SpaceStation(400, 700));
	planes.push_back(new SmallPlane(400, 700));
	bat_planes.push_back(new BatPlane(400, 700));
	mines.push_back(Mine(400, 700));
	bombs.push_back(SpaceBomb(400, 700));

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}

			pilot.control_bullets();
		}

		if (!pilot.getAlive())
			window.close();

		pilot.update(stations, planes, bat_planes, mines, bombs);

		for (int i = 0; i < stations.size(); i++)
		{
			stations.at(i).update();
			planes.at(i)->update(pilot);
			bat_planes.at(i)->update(pilot);
			mines.at(i).update();
			bombs.at(i).update();
		}

		for (int i = 0; i < stations.size(); i++)
		{
			if (!stations.at(i).getAlive())
				stations.at(i).reset();

			if (!planes.at(i)->getAlive())
				planes.at(i)->reset();

			if (!bat_planes.at(i)->getAlive())
				bat_planes.at(i)->reset();

			if (!mines.at(i).getAlive())
				mines.at(i).reset();

			if (!bombs.at(i).getAlive())
				bombs.at(i).reset();
		}

		window.clear(sf::Color::White);

		pilot.draw(window);
		for (int i = 0; i < stations.size(); i++)
		{
			stations.at(i).draw(window);
			planes.at(i)->draw(window, pilot);
			bat_planes.at(i)->draw(window, pilot);
			mines.at(i).draw(window);
			bombs.at(i).draw(window);
		}

		window.display();
	}

	return 0;
}
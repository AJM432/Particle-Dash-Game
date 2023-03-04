#pragma once
#include <SFML/Graphics.hpp>

class Particle
{
	public:
		sf::CircleShape shape;
		sf::Vector2f pos;
		sf::Vector2f vel;
		sf::Vector2f acc;
		double radius;
		double mass;

	public:
		Particle();
		Particle(long int seed);
		Particle(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f acc, double radius, double mass, sf::Color color);
		void check_wall_collision(sf::RenderWindow& window, double delta_time);
		void update(sf::RenderWindow& window, double delta_time);

};


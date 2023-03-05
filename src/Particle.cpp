#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <vector>

#include <Particle.hpp>
#include <Global.hpp>
#include <Helper.hpp>

// default class
// used to create random particles
Particle::Particle()
{
	radius=HelperFunc::randNum(std::rand(), MIN_RADIUS, MAX_RADIUS);
	pos=sf::Vector2f(HelperFunc::randNum(std::rand(), 0, (int)(WIDTH-2*radius)), 
			HelperFunc::randNum(std::rand(), 0, (int)(HEIGHT-2*radius)));

	vel=sf::Vector2f(HelperFunc::randNum(std::rand(), 0, MAX_VELOCITY), 
			HelperFunc::randNum(std::rand(), 0, MAX_VELOCITY));

	acc=sf::Vector2f(0, 98.1);
	mass=1;
	shape.setRadius(radius);
	sf::Color color(radius*(255/MAX_RADIUS), vel.x*(255/MAX_VELOCITY), vel.y*(255/MAX_VELOCITY)); // red
	shape.setFillColor(color);
}

Particle::Particle(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f acc, double radius, double mass, sf::Color color)
{
	pos=pos;
	vel=vel;
	acc=acc;
	radius=radius;
	mass=mass;
	shape.setFillColor(color);
	shape.setRadius(radius);
}


void Particle::check_wall_collision(sf::RenderWindow& window, double delta_time) {

	if (pos.x  <= 0) {
		vel.x *= -1;
		pos.x=0;

	}
	if (pos.x + 2*shape.getRadius() >= WIDTH) {
		vel.x *= -1;
		pos.x = WIDTH-shape.getRadius()*2;
	}

	if (pos.y <= 0) {
		vel.y *= -1;
		pos.y = 0;
	}

	if (pos.y + 2*shape.getRadius() >= HEIGHT) {
		vel.y *= -1;
		pos.y = HEIGHT-shape.getRadius()*2;
	}
}

void Particle::update(sf::RenderWindow& window, double delta_time)
{
	check_wall_collision(window, delta_time);

	pos.x = pos.x + vel.x*delta_time;
	pos.y = pos.y + vel.y*delta_time;

	shape.setPosition(pos);

	window.draw(shape);
}

bool Particle::collided(Particle other)
{
	double xDistance = (other.pos.x - other.radius) - (this->pos.x - this->radius);
	double yDistance = (other.pos.y - other.radius) - (this->pos.y - this->radius);
	double dist = sqrt(pow(xDistance, 2) + pow(yDistance, 2)); // compute distance
	return dist <= this->radius + other.radius;

}
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>

#include <Particle.hpp>
#include <Global.hpp>
#include <type_traits>
#include <Helper.hpp>


int main()
{
	sf::Clock clock;
	std::vector<Particle> particle_array(NUM_PARTICLES);

	std::srand(time(NULL)); // init rand seed

	// creates particle array
	for (int i=0; i < NUM_PARTICLES; i++){
		Particle p;
		particle_array.push_back(p); 
	}

	// creates mouse shape
	Particle mouseShape(sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Vector2f(0, 0), 10, 1, sf::Color::White);

	Particle p1(sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Vector2f(0, 0), 10, 1, sf::Color::White);


	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Particle Fluid Simulation");
	window.setFramerateLimit(FPS);


	while (window.isOpen())
	{

		sf::Vector2i localPosition = sf::Mouse::getPosition(window);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		sf::Time delta_time = clock.restart();

		for (int i=0; i < NUM_PARTICLES; i++) {
			particle_array[i].update(window, delta_time.asSeconds());
			if (mouseShape.collided(particle_array[i])) {
				std::cout << mouseShape.pos.x << std::endl;
			}
		}
		mouseShape.pos.x = localPosition.x;
		mouseShape.pos.y=  localPosition.y-mouseShape.radius;
		mouseShape.update(window, delta_time.asSeconds());
		window.display();
	}

	return 0;
}

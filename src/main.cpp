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
	 
	// creates array that records mouse positions
	std::vector<sf::Vector2f> position_array;

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Particle Fluid Simulation");
	window.setFramerateLimit(FPS);

	sf::Vector2i localPosition = sf::Mouse::getPosition(window);
	double totalDistance;


	while (window.isOpen())
	{

		localPosition = sf::Mouse::getPosition(window); // gets mouse position
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
			// if (mouseShape.collided(particle_array[i])) {
			// 	std::cout << mouseShape.pos.x << std::endl;
			// }
		}

		mouseShape.pos.x = localPosition.x;
		mouseShape.pos.y=  localPosition.y-mouseShape.radius;
		mouseShape.update(window, delta_time.asSeconds());
		if (position_array.size() <= 1) {
			position_array.push_back(mouseShape.pos); // records position of mouse
		}
		else if (mouseShape.pos != position_array.back()) {
			totalDistance += HelperFunc::distance(position_array.back().x, position_array.back().y, mouseShape.pos.x, mouseShape.pos.y);
			position_array.push_back(mouseShape.pos); // records position of mouse
		}
		for (int i=0; i < position_array.size()-1; ++i) {
			sf::Vertex line[] = {sf::Vertex(position_array[i]), sf::Vertex(position_array[i+1])};
			window.draw(line, 2, sf::Lines);
		}
		std::cout << totalDistance << std::endl;



		window.display();
	}

	return 0;
}

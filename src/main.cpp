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
	sf::Clock gameClock;
	std::vector<Particle> particle_array(NUM_PARTICLES);

	std::srand(time(NULL)); // init rand seed

	// creates particle array
	for (int i=0; i < NUM_PARTICLES; i++){
		Particle p;
		particle_array.push_back(p); 
	}

	// creates player
	Particle player(sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Vector2f(0, 0), 10, 1, sf::Color::White);

	Particle startP(sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Vector2f(0, 0), 10, 1, sf::Color::Red);
	Particle endP(sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Vector2f(0, 0), 10, 1, sf::Color::Green);
	endP.pos = sf::Vector2f(WIDTH-11, HEIGHT - 11); // BUG, must declare position again, defaulting to zero?
	 
	// creates array that records mouse positions
	std::vector<sf::Vector2f> position_array;

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Particle Dash");
	window.setFramerateLimit(FPS);

	double totalDistance;


	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		sf::Time delta_time = clock.restart();

        // Keyboard Input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player.vel.x -=10;

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player.vel.x +=10;

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            player.vel.y -=10;

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            player.vel.y +=10;

        }

		for (int i=0; i < NUM_PARTICLES; i++) {
			particle_array[i].update(window, delta_time.asSeconds());
			if (player.collided(particle_array[i])) {
				std::cout << "COLLIDED!" << std::endl;
				window.close();
				break;
			}
		}

		if (player.collided(endP)) {
			std::cout << "WON!" << std::endl;
			std::cout << "Total Distance: " << totalDistance << std::endl;
			sf::Time elapsedTime = gameClock.getElapsedTime();
			std::cout << "Time Elapsed: " << elapsedTime.asSeconds() << std::endl;
			window.close();
		}



		if (position_array.size() <= 1) {
			position_array.push_back(sf::Vector2f(player.pos.x-player.radius, player.pos.y-player.radius)); // records position of mouse
		}
		else if (player.pos != position_array.back()) {
			totalDistance += HelperFunc::distance(position_array.back().x, position_array.back().y, player.pos.x, player.pos.y);
			position_array.push_back(player.pos); // records position of mouse
		}
		for (int i=0; i < position_array.size()-1; ++i) {
			sf::Vertex line[] = {sf::Vertex(position_array[i]), sf::Vertex(position_array[i+1])};
			window.draw(line, 2, sf::Lines);
		}

		startP.update(window, delta_time.asSeconds());
		endP.update(window, delta_time.asSeconds());
		player.update(window, delta_time.asSeconds());

		window.display();
	}

	return 0;
}

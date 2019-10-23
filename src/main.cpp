#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>
#include <globals.h>
#include <iostream>
#include "player.h"
#include "platform.h"

int main()
{

	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SAE GPR4100 window");
	window.setVerticalSyncEnabled(true);
	
	b2World world(b2Vec2(0.0f, 9.81f));
	
	PlayerCharacter playerCharacter;
	Platform platform(sf::Vector2f(400.0f, 550));

	playerCharacter.Init(world);
	platform.Init(world);

	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();

		}
		
		playerCharacter.Update(deltaTime.asSeconds());
		world.Step(deltaTime.asSeconds(), velocityIterations, positionIterations);
		// Clear screen
		window.clear(sf::Color::White);
		//Draw everything here
		platform.Draw(window);
		playerCharacter.Draw(window);
		// Update the window
		window.display();
	}
	return EXIT_SUCCESS;

#if WIN32
	system("pause");
#endif
	return 0;
}
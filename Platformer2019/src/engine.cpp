#include "engine.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>
#include <globals.h>
#include <iostream>
#include "player.h"
#include "platform.h"

Engine::Engine() : platformListener_(this)
{
}


void Engine::Loop()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SAE GPR4100 window");
	window.setVerticalSyncEnabled(true);

	b2World world(b2Vec2(0.0f, 9.81f));
	world.SetContactListener(&platformListener_);

	std::vector<Platform> platforms = {
		{sf::Vector2f(400.0f, 550), sf::Vector2f(800,50) },
		{sf::Vector2f(50, 300), sf::Vector2f(50,600) },
		{sf::Vector2f(750, 300), sf::Vector2f(50,600) },
		/*{sf::Vector2f(600, 450), sf::Vector2f(200, 50) },*/
	};

	MovingPlatform movingPlatform = MovingPlatform(sf::Vector2f(600, 450), sf::Vector2f(200, 50));

	playerCharacter_.Init(world);
	for (auto& platform : platforms)
	{
		platform.Init(world);
	}

	movingPlatform.Init(world);
	
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
		
		playerCharacter_.Update(deltaTime.asSeconds());
		movingPlatform.Moving();
		world.Step(deltaTime.asSeconds(), velocityIterations, positionIterations);
		// Clear screen
		window.clear(sf::Color::White);
		//Draw everything here
		for (auto& platform : platforms)
		{
			platform.Draw(window);
		}

		movingPlatform.Draw(window);
		playerCharacter_.Draw(window);
		// Update the window
		window.display();
	}
}

void Engine::OnContactEnter(b2Fixture* c1, b2Fixture* c2)
{
	GameObject* g1 = (GameObject*)(c1->GetUserData());
	GameObject* g2 = (GameObject*)(c2->GetUserData());
	if (g1->GetGameObjectType() == GameObjectType::PLAYER_CHARACTER ||
		g2->GetGameObjectType() == GameObjectType::PLATFORM)
	{
		playerCharacter_.OnContactBegin();
	}
}

void Engine::OnContactExit(b2Fixture* c1, b2Fixture* c2)
{
	GameObject* g1 = (GameObject*)(c1->GetUserData());
	GameObject* g2 = (GameObject*)(c2->GetUserData());
	if (g1->GetGameObjectType() == GameObjectType::PLAYER_CHARACTER ||
		g2->GetGameObjectType() == GameObjectType::PLATFORM)
	{
		playerCharacter_.OnContactEnd();
	}
}

PlatformContactListener::PlatformContactListener(Engine* engine) : engine_(engine)
{
}

void PlatformContactListener::BeginContact(b2Contact* contact)
{
	engine_->OnContactEnter(contact->GetFixtureA(), contact->GetFixtureB());
}

void PlatformContactListener::EndContact(b2Contact* contact)
{
	engine_->OnContactExit(contact->GetFixtureA(), contact->GetFixtureB());
}
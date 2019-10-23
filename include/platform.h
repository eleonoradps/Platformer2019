#pragma once
#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"

class Platform
{
public:
	Platform(sf::Vector2f position);
	void Init(b2World& world);
	void Draw(sf::RenderWindow& window);
private:
	sf::RectangleShape rectShape_;
	b2Body* platformBody_ = nullptr;
	const sf::Vector2f size_ = sf::Vector2f(600, 50);
};
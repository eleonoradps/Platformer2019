#pragma once
#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"
#include "globals.h"

class Platform : public GameObject
{
public:
	Platform(sf::Vector2f position, sf::Vector2f size);
	void Init(b2World& world);
	void Draw(sf::RenderWindow& window);
private:
	sf::RectangleShape rectShape_;
	b2Body* platformBody_ = nullptr;
	sf::Vector2f size_;
	sf::Vector2f position_;
};
#pragma once
#include "SFML/Graphics.hpp"
#include <Box2D/Box2D.h>

class PlayerCharacter
{
public:
	PlayerCharacter();
	void Init(b2World& world);
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
private:
	b2Body* playerBody_ = nullptr;
	sf::Texture playerTexture_; //player 
	sf::Sprite playerSprite_;
	sf::Vector2f playerPosition_ = sf::Vector2f(400, 300);
	const sf::Vector2f boxSize = sf::Vector2f(12, 19);
	const float playerSpeed_ = 120.0f;//in pixels
};
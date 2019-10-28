#pragma once
#include "SFML/Graphics.hpp"
#include <Box2D/Box2D.h>
#include "globals.h"

class PlayerCharacter : public GameObject
{
public:
	PlayerCharacter();
	void Init(b2World& world);
	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	void OnContactBegin();
	void OnContactEnd();
private:
	b2Body* playerBody_ = nullptr;
	sf::Texture playerTexture_; //player 
	sf::Sprite playerSprite_;
	sf::RectangleShape boxRectDebug_;
	sf::Vector2f playerPosition_ = sf::Vector2f(400, 300);
	const sf::Vector2f boxSize = sf::Vector2f(66, 92);
	const pixel playerSpeed_ = 120.0f;//in pixels
	const float movementFactor_ = 0.7f;
	const meter jumpVelocity_ = -5.0f;//in meter
	bool previousJumpButton_ = false;
	int contactNmb_ = 0;
};
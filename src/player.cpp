#include "player.h"
#include "globals.h"
#include <iostream>

PlayerCharacter::PlayerCharacter()
{
	if (!playerTexture_.loadFromFile("data/hero1.png"))
	{
		std::cerr << "[Error] Could not load hero texture\n";
	}
	playerSprite_.setTexture(playerTexture_);

}

void PlayerCharacter::Init(b2World& world)
{

	const auto playerSize = sf::Vector2f(playerSprite_.getLocalBounds().width, playerSprite_.getLocalBounds().height);
	playerSprite_.setOrigin(playerSize / 2.0f);
	b2BodyDef bodyDef;
	bodyDef.position = pixel2meter(playerPosition_);
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	playerBody_ = world.CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(pixel2meter(boxSize.x) / 2.0f, pixel2meter(boxSize.y) / 2.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;

	playerBody_->CreateFixture(&fixtureDef);
}

void PlayerCharacter::Update(float dt)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		playerBody_->SetLinearVelocity(b2Vec2(playerBody_->GetLinearVelocity().x, 100.0f));
	}

	float move = 0.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		move -= 1.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		move += 1.0f;
	}
	
	playerBody_->SetLinearVelocity(b2Vec2(move * pixel2meter(playerSpeed_), playerBody_->GetLinearVelocity().y));
	
}

void PlayerCharacter::Draw(sf::RenderWindow& window)
{
	playerPosition_ = meter2pixel(playerBody_->GetPosition());
	playerSprite_.setPosition(playerPosition_);
	window.draw(playerSprite_);
}

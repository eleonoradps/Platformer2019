#include "platform.h"
#include "globals.h"

Platform::Platform(sf::Vector2f position)
{
	rectShape_.setPosition(position);
	rectShape_.setSize(size_);
	rectShape_.setOrigin(size_ / 2.0f);
	rectShape_.setFillColor(sf::Color::Blue);
}

void Platform::Init(b2World& world)
{
	b2BodyDef platformBodyDef;
	platformBodyDef.position = pixel2meter(rectShape_.getPosition());

	platformBody_ = world.CreateBody(&platformBodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(pixel2meter(size_.x) / 2.0f, pixel2meter(size_.y) / 2.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	platformBody_->CreateFixture(&fixtureDef);
}

void Platform::Draw(sf::RenderWindow& window)
{
	window.draw(rectShape_);
}

#ifndef UTILITY_H
#define UTILITY_H

#include <SFML/System.hpp>
#include <Box2D/Box2D.h>

const float framerate = 60.f;
//For pixel to meter conversion
const float pixelPerMeter = 100.0f;

//For b2World step
const int velocityIterations = 8;
const int positionIterations = 8;


float pixel2meter(float pixel);
b2Vec2 pixel2meter(sf::Vector2f pixels);
float meter2pixel(float meter);
sf::Vector2f meter2pixel(b2Vec2 meters);

enum class ContactDataType
{
	PLATFORM_CHARACTER,
	PLATFORM
};

struct ContactData
{
	void* data;
	ContactDataType contactDataType;
};

#endif
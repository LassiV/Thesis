#include "Lighting/Light.h"

Light::Light(void)
{
}

Light::~Light(void)
{
}

Light::Light(sf::Vector2f position, sf::Color color, int depth, float size, float range, float intensity)
{
	this->position = position;
	this->color = color;
	this->depth = depth;
	this->size = size;
	this->range = range;
	this->intensity = intensity;
}

sf::Color Light::GetColor()
{
	return color;
}

float Light::GetSize()
{
	return size;
}

float Light::GetRange()
{
	return range;
}

float Light::GetIntensity()
{
	return intensity;
}

sf::Vector2f Light::GetPosition()
{
	return position;
}
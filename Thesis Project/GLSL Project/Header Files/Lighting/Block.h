#ifndef BLOCK_H
#define BLOCK_H

#include <Lighting/PrimitiveShape.h>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Block : public PrimitiveShape
{
public:
	Block();
	Block(sf::Vector2f position, sf::Vector2f size, sf::FloatRect texCoords, sf::PrimitiveType type);
	~Block();

	void SetPosition(sf::Vector2f position);
	void SetRadius(float radius);
	void SetRotation(float rotation);

	sf::Vector2f GetPosition();
	float GetRadius();
	float GetRotation();

	void SetTexture(const sf::Texture& texture);

private:
	sf::Vector2f position;
	float radius;
	float rotation;

	sf::Sprite sprite;
};

#endif
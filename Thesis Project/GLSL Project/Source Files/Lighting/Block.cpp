#include "Lighting/Block.h"

Block::Block()
{
	position = sf::Vector2f(0.0f, 0.0f);
	radius = 0.0f;
	rotation = 0.0f;


	toRad = 0.01745329251994f;
	this->position = position;
	this->size = size;
	animTimer = 0.0f;
	currentFrame = 0;

	animSpeed = 0.08f;
	//Randomize starting frame for testing
	frameX = rand() % 6;
	frameY = rand() % 4;
	spriteRows = 3;
	spriteColumns = 5;

	sf::Vertex tempVertex = sf::Vertex();
	//if (type == sf::Quads)
	//{
		sf::FloatRect vertRect = sf::FloatRect(position.x - size.x / 2.f, position.y - size.y / 2.f, size.x, size.y);
		//Top left
		tempVertex.position = sf::Vector2f(vertRect.left, vertRect.top);
		//tempVertex.texCoords = sf::Vector2f(texCoords.left, texCoords.top);
		points.push_back(tempVertex);

		//Top right
		tempVertex.position = sf::Vector2f(vertRect.left + vertRect.width, vertRect.top);
		//tempVertex.texCoords = sf::Vector2f(texCoords.left + texCoords.width, texCoords.top);
		points.push_back(tempVertex);

		//Bottom right
		tempVertex.position = sf::Vector2f(vertRect.left + vertRect.width, vertRect.top + vertRect.height);
		//tempVertex.texCoords = sf::Vector2f(texCoords.left + texCoords.width, texCoords.top + texCoords.height);
		points.push_back(tempVertex);

		//Bottom left
		tempVertex.position = sf::Vector2f(vertRect.left, vertRect.top + vertRect.height);
		//tempVertex.texCoords = sf::Vector2f(texCoords.left, texCoords.top + texCoords.height);
		points.push_back(tempVertex);
	//}
}

Block::~Block()
{

}

void Block::SetPosition(sf::Vector2f position)
{
	this->position = position;
}

void Block::SetRadius(float radius)
{
	this->radius = radius;
}

void Block::SetRotation(float rotation)
{
	this->rotation = rotation;
}

sf::Vector2f Block::GetPosition()
{
	return position;
}

float Block::GetRadius()
{
	return radius;
}

float Block::GetRotation()
{
	return rotation;
}

void Block::SetTexture(const sf::Texture& texture)
{
	sprite.setTexture(texture);
}
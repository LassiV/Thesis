#ifndef PRIMITIVESHAPE_H
#define PRIMITIVESHAPE_H

#include <vector>
#include <SFML\Graphics.hpp>

class PrimitiveShape
{
public:
	PrimitiveShape(void);
	~PrimitiveShape(void);

	PrimitiveShape(sf::Vector2f position, sf::Vector2f size, sf::FloatRect rect, sf::PrimitiveType type);

	std::vector<sf::Vertex*> GetPoints();

	void SetDepth(int depth);

	void SetPosition(sf::Vector2f position);

	void SetAngle(float angle);

	void SetFrameInfo(sf::FloatRect frameInfo);

	void Update(float &deltaTime);


protected:
	std::vector<sf::Vertex*> points; //Points that define the drawable shape
	int depth;
	sf::Vector2f size;
	int shadowDepthOffset;
	sf::Vector2f position;
	float angle;
	
	sf::FloatRect frameInfo;

	int currentFrame;

	int frameX;
	int frameY;

	int spriteRows;
	int spriteColumns;

	float animTimer;
	float animSpeed;

	float toRad;

	//sf::Vertex already contains this information
	//std::vector<sf::Color> pointColors;
	//std::vector<sf::FloatRect> pointTextureCoords;
};

#endif
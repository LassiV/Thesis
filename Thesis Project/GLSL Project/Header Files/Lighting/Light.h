#ifndef LIGHT_H
#define LIGHT_H
#include <SFML/Graphics.hpp>

//#include <Lighting/Block.h>

//#include <Lighting/ShadowCalculation.h>

class Light
{
public:
	Light(void);
	Light(sf::Vector2f position, sf::Color color, int depth, float size, float range, float intensity);
	~Light(void);

	sf::Color GetColor();
	float GetSize();
	float GetRange();
	float GetIntensity();
	sf::Vector2f GetPosition();

	//void Render(sf::RenderTexture* renderTexture, const sf::Shader& lightShader, std::vector<Block*> blocks);

private:
	sf::Vector2f position;
	int depth;
	float size, range, intensity;
	sf::Color color;

	sf::VertexArray tempVertices;
	std::vector<short> tempIndices;

//	ShadowCalculation* shadowCalc;
};

#endif
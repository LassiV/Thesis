#ifndef PRIMITIVERENDERER_H
#define PRIMITIVERENDERER_H

#include "Lighting/PrimitiveShape.h"
#include "Lighting/Block.h"

#include <SFML/Graphics.hpp>
#include <vector>

class PrimitiveRenderer
{
public:
	PrimitiveRenderer();
	~PrimitiveRenderer();

	void SetVertices(std::vector<PrimitiveShape*> shapes);

	void BatchBlocks(std::vector<Block*> blocks);

	void SetTexture(sf::Texture* texture);

	void SetShader(const sf::Shader& shader);

	void Render(sf::RenderWindow &renderWindow, sf::RenderStates* renderState);

	void RenderToTexture(sf::RenderTexture &renderTexture, const sf::Shader& shader);

private:

	//sf::VertexArray vertices;

	std::vector<sf::Vertex> vertices; 

	sf::Texture* texture;

	sf::Shader* shader;

	sf::RenderStates states;
};

#endif
#ifndef RENDERER_H
#define RENDERER_H

#include "Lighting/PrimitiveShape.h"
#include "Rendering/Effect.h"

#include <SFML/Graphics.hpp>
#include <vector>

class Renderer
{
public:
	Renderer();
	~Renderer();

	void SetVertices(std::vector<PrimitiveShape*> shapes);

	void SetTexture(sf::Texture* texture);

	void SetShader(const sf::Shader& shader);

	void Render(sf::RenderWindow &renderWindow, sf::RenderStates* renderState);

	void RenderToTexture(sf::RenderTexture &renderTexture, const Effect& effect);

private:

	std::vector<sf::Vertex> vertices; 

	sf::Texture* atlas;

	sf::Shader* shader;

	sf::RenderStates states;
};

#endif
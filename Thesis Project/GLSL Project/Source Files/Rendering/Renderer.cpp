#include "Rendering/Renderer.h"


Renderer::Renderer()
{
	states = sf::RenderStates::Default;
	atlas = new sf::Texture();
	atlas->loadFromFile("Textures/groundsprites.png");
}


Renderer::~Renderer()
{
}

void Renderer::Render(sf::RenderWindow &renderWindow, sf::RenderStates* renderState)
{
	//sf::RenderStates states = sf::RenderStates::Default;
	atlas->setRepeated(true);
	renderState->texture = atlas;
	//renderstates.shader = &shader;
	renderWindow.draw(&vertices[0], vertices.size(), sf::Quads, *renderState);
}

void Renderer::RenderToTexture(sf::RenderTexture &renderTexture, const Effect& shader)
{
	sf::RenderStates states = sf::RenderStates::Default;
	atlas->setRepeated(true);
	states.texture = atlas;
	//states.shader = &shader;
	renderTexture.draw(&vertices[0], vertices.size(), sf::Quads, states);
}


void Renderer::SetVertices(std::vector<PrimitiveShape*> shapes)
{
	vertices.clear();
	std::vector<sf::Vertex*> tempPoints;
	for (unsigned int i = 0; i < shapes.size(); i++)
	{
		tempPoints = shapes[i]->GetPoints();
		for (unsigned int y = 0; y < tempPoints.size(); y++)
		{
			vertices.push_back(*tempPoints[y]);
		}
	}
}
/*
void Renderer::BatchBlocks(std::vector<Block*> blocks)
{
	vertices.clear();
	std::vector<sf::Vertex> tempPoints;
	for (unsigned int i = 0; i < blocks.size(); i++)
	{
		tempPoints = blocks[i]->GetPoints();
		for (unsigned int y = 0; y < tempPoints.size(); y++)
		{
			vertices.push_back(tempPoints[y]);
		}
	}
}
*/
void Renderer::SetTexture(sf::Texture* texture)
{
	this->atlas = texture;
}


void Renderer::SetShader(const sf::Shader& Shader)
{
	this->shader = shader;
}
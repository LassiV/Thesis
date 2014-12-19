#include "Rendering\PrimitiveRenderer.h"


PrimitiveRenderer::PrimitiveRenderer()
{
	states = sf::RenderStates::Default;
}


PrimitiveRenderer::~PrimitiveRenderer()
{
}

void PrimitiveRenderer::Render(sf::RenderWindow &renderWindow, sf::RenderStates* renderState)
{
	//sf::RenderStates states = sf::RenderStates::Default;
	texture->setRepeated(true);
	renderState->texture = texture;
	//renderstates.shader = &shader;
	renderWindow.draw(&vertices[0], vertices.size(), sf::Quads, *renderState);
}

void PrimitiveRenderer::RenderToTexture(sf::RenderTexture &renderTexture, const sf::Shader& shader)
{
	sf::RenderStates states = sf::RenderStates::Default;
	texture->setRepeated(true);
	states.texture = texture;
	//states.shader = &shader;
	renderTexture.draw(&vertices[0], vertices.size(), sf::Quads, states);
}


void PrimitiveRenderer::SetVertices(std::vector<PrimitiveShape*> shapes)
{
	vertices.clear();
	std::vector<sf::Vertex> tempPoints;
	for (unsigned int i = 0; i < shapes.size(); i++)
	{
		tempPoints = shapes[i]->GetPoints();
		for (unsigned int y = 0; y < tempPoints.size(); y++)
		{
			vertices.push_back(tempPoints[y]);
		}
	}
}

void PrimitiveRenderer::BatchBlocks(std::vector<Block*> blocks)
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

void PrimitiveRenderer::SetTexture(sf::Texture* texture)
{
	this->texture = texture;
}


void PrimitiveRenderer::SetShader(const sf::Shader& Shader)
{
	this->shader = shader;
}
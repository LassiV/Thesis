#include "Rendering/Effect.h"


Effect::Effect(std::string vertexShaderPath, std::string fragmentShaderPath)
{
	shaderEffect = new sf::Shader();
	renderState = new sf::RenderStates();
	this->vertexShaderPath = vertexShaderPath;
	this->fragmentShaderPath = fragmentShaderPath;

	if (!shaderEffect->loadFromFile(vertexShaderPath, fragmentShaderPath))
	{
		printf("There was an error loading the shader effect");
	}
}

Effect::Effect()
{

}

Effect::~Effect()
{
	delete shaderEffect;
	delete renderState;
}

const sf::Shader& Effect::Get()
{
	return *shaderEffect;
}

const sf::RenderStates& Effect::GetRenderState()
{
	return *renderState;
}

void Effect::Reload(std::string vertexShaderPath, std::string fragmentShaderPath)
{
	delete shaderEffect;

	shaderEffect = new sf::Shader();

	this->vertexShaderPath = vertexShaderPath;
	this->fragmentShaderPath = fragmentShaderPath;

	if (!shaderEffect->loadFromFile(vertexShaderPath, fragmentShaderPath))
	{
		printf("There was an error reloading the shader effect");
	}
}

void Effect::SetFloat(std::string paramName, float value)
{
	shaderEffect->setParameter(paramName, value);
}

void Effect::SetVector2(std::string paramName, sf::Vector2f value)
{
	shaderEffect->setParameter(paramName, value);
}

void Effect::SetColor(std::string paramName, sf::Color value)
{
	shaderEffect->setParameter(paramName, value);
}

void Effect::SetTexture(std::string paramName, sf::Sprite* value)
{
	shaderEffect->setParameter(paramName, *value->getTexture());
}

void Effect::SetRenderState(sf::RenderStates* renderState)
{
	this->renderState = renderState;
}

void Effect::SetBlendMode(sf::BlendMode blendMode)
{
	renderState->blendMode = blendMode;
}

void Effect::ApplyEffect(sf::RenderTarget& output,const sf::Shader& shader)
{
	sf::Vector2f outputSize = static_cast<sf::Vector2f>(output.getSize());

	sf::VertexArray vertices(sf::TrianglesStrip, 4);

	vertices[0] = sf::Vertex(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 1.f));

	vertices[1] = sf::Vertex(sf::Vector2f(outputSize.x, 0.f), sf::Vector2f(1.f, 1.f));

	vertices[2] = sf::Vertex(sf::Vector2f(0.f, outputSize.y), sf::Vector2f(0.f, 0.f));

	vertices[3] = sf::Vertex(sf::Vector2f(outputSize), sf::Vector2f(1.f, 0.f));

	//renderState->texture = output.gette

	renderState->shader = &shader;

	renderState->blendMode = sf::BlendNone;

	output.draw(vertices, *renderState);
}

void Effect::ApplyEffectToTexture(sf::RenderTexture& output, sf::Sprite* sprite, sf::BlendMode blendMode)
{
	sf::Vector2f outputSize = static_cast<sf::Vector2f>(output.getSize());

	sf::VertexArray vertices(sf::TrianglesStrip, 4);

	vertices[0] = sf::Vertex(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 1.f));

	vertices[1] = sf::Vertex(sf::Vector2f(outputSize.x, 0.f), sf::Vector2f(1.f, 1.f));

	vertices[2] = sf::Vertex(sf::Vector2f(0.f, outputSize.y), sf::Vector2f(0.f, 0.f));

	vertices[3] = sf::Vertex(sf::Vector2f(outputSize), sf::Vector2f(0.f, 1.f));

	sf::Sprite tempSprite(output.getTexture());

	renderState->shader = shaderEffect;
	
	renderState->texture = sprite->getTexture();

	renderState->blendMode = blendMode;

	output.draw(*sprite, *renderState);

	//output.display();
}
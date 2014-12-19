#ifndef EFFECT_H
#define EFFECT_H

#include <string>
#include <SFML/Graphics.hpp>

class Effect
{
public:
	
	Effect(std::string vertexShaderPath, std::string fragmentShaderPath);
	Effect();
	~Effect();

	const sf::Shader& Get();

	const sf::RenderStates& GetRenderState();

	void Reload(std::string vertexShaderPath, std::string fragmentShaderPath);
		
	void SetFloat(std::string paramName, float value);

	void SetVector2(std::string paramName, sf::Vector2f value);

	void SetColor(std::string paramName, sf::Color value);

	void SetTexture(std::string paramName, sf::Sprite* value);

	void SetRenderState(sf::RenderStates* renderState);

	void SetBlendMode(sf::BlendMode blendMode);

	void ApplyEffect(sf::RenderTarget& output, const sf::Shader& shader);
	
	void ApplyEffectToTexture(sf::RenderTexture& output, sf::Sprite* sprite, sf::BlendMode blendMode);

protected:
	sf::Shader* shaderEffect;
	sf::RenderStates* renderState;
	std::string vertexShaderPath;
	std::string fragmentShaderPath;
};
#endif
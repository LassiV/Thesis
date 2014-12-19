#ifndef BLOOMEFFECT_H
#define BLOOMEFFECT_H

#include "Rendering/Effect.h"

#include <vector>

class BloomEffect : public Effect
{
public:
	BloomEffect();
	BloomEffect::BloomEffect(std::string vertexShaderPath, std::string fragmentShaderPath);
	~BloomEffect();

	void ApplyBloomEffect(sf::RenderTexture& input, sf::RenderTarget& output);

	void PrepareTextures(sf::Vector2u size);

private:

	//std::vector<sf::RenderTexture> textures;

	sf::RenderTexture brightnessPassTexture;
	sf::RenderTexture firstPass1;
	sf::RenderTexture firstPass2;
	sf::RenderTexture secondPass1;
	sf::RenderTexture secondPass2;

	sf::Shader blend;
	sf::Shader brightness;
	sf::Shader downsampler;
	sf::Shader gaussian;

	void	FilterBrightness(const sf::RenderTexture& input, sf::RenderTexture& output);
	void	BlurMultipass(int pass);
	void	Blur(const sf::RenderTexture& input, sf::RenderTexture& output, sf::Vector2f offsetFactor);
	void	Downsample(const sf::RenderTexture& input, sf::RenderTexture& output);
	void	AddEffect(const sf::RenderTexture& source, const sf::RenderTexture& bloom, sf::RenderTarget& target);
};

#endif
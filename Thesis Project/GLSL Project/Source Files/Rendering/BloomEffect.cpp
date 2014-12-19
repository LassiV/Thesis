#include "Rendering/BloomEffect.h"


BloomEffect::BloomEffect()
{
	
	blend.loadFromFile("Shaders/default.vert", "Shaders/blend.frag");
	brightness.loadFromFile("Shaders/default.vert", "Shaders/brightness.frag");
	downsampler.loadFromFile("Shaders/default.vert", "Shaders/downsample.frag");
	gaussian.loadFromFile("Shaders/default.vert", "Shaders/gaussianblur.frag");
}

BloomEffect::BloomEffect(std::string vertexShaderPath, std::string fragmentShaderPath)
{
	shaderEffect = new sf::Shader();
	renderState = new sf::RenderStates();
	this->vertexShaderPath = vertexShaderPath;
	this->fragmentShaderPath = fragmentShaderPath;

	if (!shaderEffect->loadFromFile(vertexShaderPath, fragmentShaderPath))
	{
		printf("There was an error loading the shader effect");
	}

	blend.loadFromFile("Shaders/default.vert", "Shaders/blend.frag");
	brightness.loadFromFile("Shaders/default.vert", "Shaders/brightness.frag");
	downsampler.loadFromFile("Shaders/default.vert", "Shaders/downsample.frag");
	gaussian.loadFromFile("Shaders/default.vert", "Shaders/gaussianblur.frag");
}

BloomEffect::~BloomEffect()
{

}

void BloomEffect::ApplyBloomEffect(sf::RenderTexture& input, sf::RenderTarget& output)
{
	PrepareTextures(input.getSize());

	FilterBrightness(input, brightnessPassTexture);

	Downsample(brightnessPassTexture, firstPass1);

	BlurMultipass(0);

	Downsample(firstPass1, secondPass1);

	BlurMultipass(1);

	AddEffect(firstPass1, secondPass1, firstPass2);

	AddEffect(input, firstPass2, output);
}

void BloomEffect::PrepareTextures(sf::Vector2u size)
{
	if(size != brightnessPassTexture.getSize())
	{
		brightnessPassTexture.create(size.x, size.y);
		brightnessPassTexture.setSmooth(true);

		firstPass1.create(size.x / 2, size.y / 2);		
		firstPass1.setSmooth(true);

		firstPass2.create(size.x / 2, size.y / 2);
		firstPass2.setSmooth(true);


		secondPass1.create(size.x / 4, size.y / 4);
		secondPass1.setSmooth(true);
		
		secondPass2.create(size.x / 4, size.y / 4);
		secondPass2.setSmooth(true);
	}
}

void BloomEffect::FilterBrightness(const sf::RenderTexture& input, sf::RenderTexture& output)
{
	brightness.setParameter("texture", input.getTexture());

	ApplyEffect(output, brightness);
	output.display();
}

void BloomEffect::BlurMultipass(int pass)
{
	sf::Vector2u textureSize = firstPass1.getSize();
	for (int i = 0; i < 2; ++i)
	{
		if(pass == 0)
		{
			Blur(firstPass1, firstPass2, sf::Vector2f(0.f, 1.f / textureSize.y));
			Blur(firstPass2, firstPass1, sf::Vector2f(1.f / textureSize.x, 0.f));
		}
		else if(pass == 1)
		{
			Blur(secondPass1, secondPass2, sf::Vector2f(0.f, 1.f / textureSize.y));
			Blur(secondPass2, secondPass1, sf::Vector2f(1.f / textureSize.x, 0.f));
		}
	}
}
void BloomEffect::Blur(const sf::RenderTexture& input, sf::RenderTexture& output, sf::Vector2f offsetFactor)
{
	gaussian.setParameter("texture", input.getTexture());
	gaussian.setParameter("offsetFactor", offsetFactor);
	ApplyEffect(output, gaussian);
	output.display();
}

void BloomEffect::Downsample(const sf::RenderTexture& input, sf::RenderTexture& output)
{
	downsampler.setParameter("texture", input.getTexture());
	downsampler.setParameter("sourceSize", sf::Vector2f(input.getSize()));
	ApplyEffect(output, downsampler);
	output.display();
}
void BloomEffect::AddEffect(const sf::RenderTexture& source, const sf::RenderTexture& bloom, sf::RenderTarget& output)
{
	blend.setParameter("texture", source.getTexture());
	blend.setParameter("bloom", bloom.getTexture());
	ApplyEffect(output, blend);
}
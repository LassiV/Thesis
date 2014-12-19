#ifndef GAME_H
#define GAME_H

#include "Lighting/PrimitiveShape.h"
#include "Lighting/Light.h"
#include "Rendering/Renderer.h"
#include "Rendering/Effect.h"
#include "Rendering/BloomEffect.h"
#include "Game/Player.h"
#include "Game/Enemy.h"
#include "Game/Bullet.h"


class Game
{
public:
	Game();
	~Game();
	void Initialise();
	void Update();

	void Draw();

	void DrawColorMap();

	void DrawLightMap(float ambientLightStrength);
	
private:

	enum DrawState
	{
		Normal,
		Lights,
		Bloom,
		LightsAndBloom
	};

	Player player;

	std::vector<Enemy*> enemies;

	std::vector<Bullet*> bullets;

	DrawState drawState;

	sf::Clock ticker;

	float deltaTime;
	float effectTimer;
	float spawnTimer;
	float shootTimer;
	
	sf::RenderWindow* renderWindow;

	sf::Texture enemyTex;
	sf::Texture bulletTex;

	Renderer* renderer;
	
	std::vector<Light*> lights;

	std::vector<PrimitiveShape*> backgroundTiles;

	std::vector<sf::Sprite*> sprites;

	sf::RenderTexture* lightRender;
	sf::RenderTexture* normalRender;
	sf::RenderTexture* brightnessRender;

	sf::RenderTexture* outputTex;

	sf::RenderWindow* window;
	
	Effect* defaultEffect;
	
	Effect* lightEffect;
	BloomEffect* bloomEffect;
	


	Effect* brightnessEffect;
	/*
	Effect* blurEffect;
	

	sf::Texture* rectTexture;
	sf::Texture* glowTexture;
	*/
    void UpdateObjects();

	void ApplyLightEffects(sf::Sprite* target);


	void NormalDraw();

	void DrawLights();

	void DrawBloom();

	void DrawLightsAndBloom();

	void Shoot(Player& player);

	void CheckCollisions();

};
#endif
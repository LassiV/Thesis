#include <Game/Game.h>

Game::Game()
{
		
};

Game::~Game()
{
		delete renderWindow;
		delete renderer;
		delete lightRender;
		delete normalRender;
		delete brightnessRender;
		delete outputTex;
		delete defaultEffect;
		delete lightEffect;
		delete brightnessEffect;
		delete bloomEffect;

		for (int i = lights.size()-1; lights.size() > 0; i--)
		{
			delete lights[i];
			lights.erase(lights.begin() + i);
		}

		for (int i = backgroundTiles.size() - 1; backgroundTiles.size() > 0; i--)
		{
			delete backgroundTiles[i];
			backgroundTiles.erase(backgroundTiles.begin() + i);
		}

		for (int i = enemies.size() - 1; enemies.size() > 0; i--)
		{
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
		}

		for (int i = bullets.size() - 1; bullets.size() > 0; i--)
		{
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
		}

		for (int i = sprites.size() - 1; sprites.size() > 0; i--)
		{
			delete sprites[i];
			sprites.erase(sprites.begin() + i);
		}
};

void Game::Initialise()
{

	drawState = DrawState::Normal;

	ticker.restart();
	deltaTime = 0.f;
	effectTimer = 0.f;
	shootTimer = 0.f;
	spawnTimer = 0.f;
	enemyTex.loadFromFile("Textures/box.png");
	bulletTex.loadFromFile("Textures/bullet.png");
	enemyTex.setSmooth(true);
	bulletTex.setSmooth(true);
	//sword->loadFromFile("Textures/testsword.png");
	sf::ContextSettings settings(0u, 0u, 4u, 4u, 5u);
	renderWindow = new sf::RenderWindow(sf::VideoMode(800u, 600u), "Game Window", 7u, settings);
	

	renderer = new Renderer();

	lightRender = new sf::RenderTexture();
	normalRender = new sf::RenderTexture();
	brightnessRender = new sf::RenderTexture();
	outputTex = new sf::RenderTexture();

	lightRender->create(800u, 600u);
	normalRender->create(800u, 600u);
	brightnessRender->create(800u, 600u);
	outputTex->create(800u, 600u);

	defaultEffect = new Effect("Shaders/default.vert", "Shaders/default.frag");
	
	lightEffect = new Effect("Shaders/default.vert", "Shaders/light.frag");
	brightnessEffect = new Effect("Shaders/default.vert", "Shaders/brightness.frag");
	//blurEffect = new Effect("Shaders/default.vert", "Shaders/blur.frag");
	bloomEffect = new BloomEffect("Shaders/default.vert", "Shaders/light.frag");

	for (int i = 0; i < 16; i++)
	{
		for (int y = 0; y < 13; y++)
		{
			PrimitiveShape* shape;

			int type = 3;
			if (y > 10)
				type = 0;
			if (y > 11)
				type = 1;

			shape = new PrimitiveShape(sf::Vector2f(50.0f*i + 25.0f, 0.f + (50.0f * y)), sf::Vector2f(50.f, 50.f), sf::FloatRect(0.f + (type * 50.f), 0.f, 50.f, 50.f), sf::Quads);


			shape->SetFrameInfo(sf::FloatRect(0.f, 0.f, 50.f, 50.f));
			backgroundTiles.push_back(shape);
		}
	}

	for(int i = 0; i < 1; i++)
	{
		for (int y = 0; y < 1; y++)
		{
			sf::Color color;
			
			if(y == 0 && i == 0)
				color = sf::Color::White;
			/*
			else if(y == 0 && i == 1)
				color = sf::Color::Red;
			else if (y == 1 && i == 0)
				color = sf::Color::Blue;
			else if (y == 1 && i == 1)
				color = sf::Color::Green;
				*/
			//Light* light = new Light(sf::Vector2f(200.0f + i * 300.f, 150.f + 300.f*y), color, 0, 300.0f, 400.0f, 100.0f);
			Light* light = new Light(sf::Vector2f(700.0f, 0.f), color, 0, 300.0f, 800.f, 400.0f);
			lights.push_back(light);
		}
	}

	renderer->SetVertices(backgroundTiles);
	//renderer->SetShader(defaultEffect);
	//renderer->SetTexture(texture);
};

void Game::UpdateObjects()
{
	player.Update(deltaTime, sf::Vector2f(sf::Mouse::getPosition(*renderWindow)));
	
	for (unsigned int i = 0; i < backgroundTiles.size(); i++)
	{
		//backgroundTiles[i]->Update(deltaTime);
	}
	renderer->SetVertices(backgroundTiles);

	if (enemies.size() > 0)
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i]->Update(deltaTime);
		}
	}

	if (bullets.size() > 0)
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i]->Update(deltaTime);
		}
	}
}

void Game::CheckCollisions()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		for (int y = 0; y < enemies.size(); y++)
		{
			if (bullets[i]->GetCollider()->intersects(*enemies[y]->GetCollider()))
			{
				bullets[i]->Kill();
				enemies[y]->Kill();
			}
		}
	}


	//Destroy enemies and bullets to be removed after all the other updates so vectors won't go out of bounds and break.
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->IsDead())
		{
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
		}
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->IsDead())
		{
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
		}
	}
}

void Game::Shoot(Player& player)
{
	Bullet* bullet = new Bullet(player.GetPosition(), player.GetRotation(), bulletTex);

	bullets.push_back(bullet);
}

void Game::Update()
{
	while (renderWindow->isOpen())
	{
		deltaTime = ticker.restart().asSeconds();
		effectTimer += deltaTime;
		shootTimer += deltaTime;
		spawnTimer += deltaTime;
		if (effectTimer >= 1.0f) effectTimer = 0.0f;

		sf::Event event;
		while (renderWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				renderWindow->close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			drawState = DrawState::Normal;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			drawState = DrawState::Lights;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
			drawState = DrawState::Bloom;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
			drawState = DrawState::LightsAndBloom;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && shootTimer >= 0.2f)
		{
			Shoot(player);
			shootTimer = 0.f;
		}

		if (spawnTimer >= 0.8f)
		{
			spawnTimer = 0.f;
			Enemy* enemy = new Enemy(sf::Vector2f(rand() % 701 + 100.f, 0.f), enemyTex);
			enemies.push_back(enemy);
		}

		UpdateObjects();
		CheckCollisions();
		Draw();
		//printf("Framerate : %f\n", 1.0f/deltaTime);
	}
};

void Game::ApplyLightEffects(sf::Sprite* target)
{
	for(int i = 0; i < lights.size(); i++)
	{
		lightEffect->SetVector2("lightPos", sf::Vector2f(lights[i]->GetPosition().x, 600.0f - lights[i]->GetPosition().y));
		lightEffect->SetFloat("lightRadius", lights[i]->GetRange());
		lightEffect->SetColor("lightColor", lights[i]->GetColor());
		lightEffect->ApplyEffectToTexture(*normalRender, target, sf::BlendAdd);
	}
}

void Game::NormalDraw()
{
	renderWindow->clear(sf::Color::Black);
	outputTex->clear(sf::Color::Black);
	normalRender->clear(sf::Color::Black);

	renderer->RenderToTexture(*normalRender, *defaultEffect);
	player.Draw(*normalRender);

	for(int i = 0; i < sprites.size(); i++)
	{
		normalRender->draw(*sprites[i], sf::RenderStates::Default);
	}
	for (int x = 0; x < bullets.size(); x++)
	{
		normalRender->draw(*bullets[x]->GetSprite() , sf::RenderStates::Default);
	}
	for (int x = 0; x < enemies.size(); x++)
	{
		normalRender->draw(*enemies[x]->GetSprite(), sf::RenderStates::Default);
	}
	sf::Sprite sprite(normalRender->getTexture());
	normalRender->display();

	sf::RenderStates states;
	//states.shader = &brightnessEffect->Get();

	renderWindow->draw(sprite, states);

	renderWindow->display();
}

void Game::DrawLights()
{
	renderWindow->clear(sf::Color::Black);
	outputTex->clear(sf::Color::Black);
	normalRender->clear(sf::Color::Black);

	renderer->RenderToTexture(*normalRender, *defaultEffect);
	player.Draw(*normalRender);
	for(int i = 0; i < sprites.size(); i++)
	{
		normalRender->draw(*sprites[i], sf::RenderStates::Default);
	}
	for (int x = 0; x < bullets.size(); x++)
	{
		normalRender->draw(*bullets[x]->GetSprite(), sf::RenderStates::Default);
	}
	for (int x = 0; x < enemies.size(); x++)
	{
		normalRender->draw(*enemies[x]->GetSprite(), sf::RenderStates::Default);
	}
	sf::Sprite sprite(normalRender->getTexture());
	normalRender->display();

	ApplyLightEffects(&sprite);

	normalRender->display();

	renderWindow->draw(sprite, sf::RenderStates::Default);

	renderWindow->display();
}

void Game::DrawBloom()
{
	renderWindow->clear(sf::Color::Black);
	outputTex->clear(sf::Color::Black);
	normalRender->clear(sf::Color::Black);

	renderer->RenderToTexture(*normalRender, *defaultEffect);
	player.Draw(*normalRender);
	for(int i = 0; i < sprites.size(); i++)
	{
		normalRender->draw(*sprites[i], sf::RenderStates::Default);
	}
	for (int x = 0; x < bullets.size(); x++)
	{
		normalRender->draw(*bullets[x]->GetSprite(), sf::RenderStates::Default);
	}
	for (int x = 0; x < enemies.size(); x++)
	{
		normalRender->draw(*enemies[x]->GetSprite(), sf::RenderStates::Default);
	}
	sf::Sprite sprite(outputTex->getTexture());
	normalRender->display();
	bloomEffect->ApplyBloomEffect(*normalRender, *outputTex);
	outputTex->display();
	sprite.setTexture(outputTex->getTexture());

	renderWindow->draw(sprite, sf::RenderStates::Default);

	renderWindow->display();
}

void Game::DrawLightsAndBloom()
{
	renderWindow->clear(sf::Color::Black);
	outputTex->clear(sf::Color::Black);
	normalRender->clear(sf::Color::Black);

	renderer->RenderToTexture(*normalRender, *defaultEffect);
	player.Draw(*normalRender);
	for(int i = 0; i < sprites.size(); i++)
	{
		normalRender->draw(*sprites[i], sf::RenderStates::Default);
	}
	for (int x = 0; x < bullets.size(); x++)
	{
		normalRender->draw(*bullets[x]->GetSprite(), sf::RenderStates::Default);
	}
	for (int y = 0; y < enemies.size(); y++)
	{
		normalRender->draw(*enemies[y]->GetSprite(), sf::RenderStates::Default);
	}
	sf::Sprite sprite(normalRender->getTexture());
	normalRender->display();

	ApplyLightEffects(&sprite);

	normalRender->display();
	bloomEffect->ApplyBloomEffect(*normalRender, *outputTex);
	outputTex->display();
	sprite.setTexture(outputTex->getTexture());

	renderWindow->draw(sprite, sf::RenderStates::Default);

	renderWindow->display();
}


void Game::Draw()
{
	switch (drawState)
	{
	case DrawState::Normal:
		NormalDraw();
		break;
	case DrawState::Lights:
		DrawLights();
		break;
	case DrawState::Bloom:
		DrawBloom();
		break;
	case DrawState::LightsAndBloom:
		DrawLightsAndBloom();
		break;
	}
}
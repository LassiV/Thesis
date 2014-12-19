#include <Game/Player.h>

Player::Player()
{
	turretBaseTexture.loadFromFile("Textures/turretBase.png");
	turretBaseSprite.setPosition(32.0f, 536.0f);
	turretBaseSprite.setOrigin(64.0f, 64.0f);
	turretBaseSprite.setTexture(turretBaseTexture);
	turretBaseSprite.setRotation(0.0f);
	turretBaseSprite.setScale(0.5f, 0.5f);

	turretTexture.loadFromFile("Textures/turret.png");
	turretSprite.setPosition(32.0f, 528.0f);
	turretSprite.setOrigin(132.0f, 64.0f);
	turretSprite.setTexture(turretTexture);
	turretSprite.setScale(0.5f, 0.5f);
	turretSprite.setRotation(0.0f);


	position = sf::Vector2f(32.0f, 568.0f);

};

Player::~Player()
{
};


void Player::Update(float& deltaTime, sf::Vector2f mousePos)
{
	AngleBetween(position, mousePos);

	if (rotation <= 0.1f || rotation >= 270.f)
		rotation = 0.1f;
	else if(rotation >= 180.f && rotation <= 270.f)
		rotation = 180.f;

	turretSprite.setRotation(rotation);
}

void Player::Draw(sf::RenderTexture& renderTexture)
{
	renderTexture.draw(turretBaseSprite);
	renderTexture.draw(turretSprite);
}


void Player::AngleBetween(sf::Vector2f& p1, sf::Vector2f& p2)
{
		sf::Vector2f delta = p1 - p2;

		float angle = atan2(delta.y, delta.x);
		
		if (angle < 0)
		{
			angle += 2 * 3.14151f;
		}

		rotation = angle * (180.f / 3.14151f);
}

sf::Vector2f Player::GetPosition()
{
	return position;
}

float Player::GetRotation()
{
	return rotation;
}

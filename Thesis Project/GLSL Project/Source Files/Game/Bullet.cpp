#include <Game/Bullet.h>

Bullet::Bullet()
{
		
};

Bullet::Bullet(sf::Vector2f position, float rotation, sf::Texture& texture)
{
	isDead = false;
	this->position = position;

	
	
	float ang = rotation / (180.f / 3.14151f);

	speed.x = -cos(ang)*200.0f;
	speed.y = -sin(ang)*200.0f;

	this->position.y -= 42.0f;

	this->position.y += -sin(ang)*64.f;
	this->position.x += -cos(ang)*64.f;

	collider = new sf::FloatRect();

	bulletSprite = new sf::Sprite();
	bulletSprite->setTexture(texture);
	bulletSprite->setPosition(this->position);
	bulletSprite->setOrigin(32.f, 32.f);
	bulletSprite->setScale(sf::Vector2f(.25f, .25f));
	bulletSprite->setRotation(rotation-90.f);

	collider->left = this->position.x - 8.f;
	collider->top = this->position.y;
	collider->height = 12.f;
	collider->width = 12.f;
}

Bullet::~Bullet()
{
	delete bulletSprite;
	delete collider;
};

void Bullet::Update(float& deltaTime)
{
	position += speed*deltaTime;
	bulletSprite->setPosition(position);
	collider->left = position.x - 8.f;
	collider->top = position.y;
}

sf::Sprite* Bullet::GetSprite()
{
	return bulletSprite;
}

sf::FloatRect* Bullet::GetCollider()
{
	return collider;
}

bool Bullet::IsDead()
{
	return isDead;
}

void Bullet::Kill()
{
	isDead = true;
}
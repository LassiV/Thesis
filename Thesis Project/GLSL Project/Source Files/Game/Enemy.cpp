#include <Game/Enemy.h>

Enemy::Enemy()
{
		
};

Enemy::Enemy(sf::Vector2f position, sf::Texture& texture)
{
	isDead = false;
	this->position = position;
	enemySprite = new sf::Sprite();
	collider = new sf::FloatRect();
	//enemySprite.loadFromFile("Textures/meteor.png");
	enemySprite->setPosition(this->position);
	enemySprite->setOrigin(32.0f, 32.0f);
	enemySprite->setTexture(texture);
	enemySprite->setRotation(0.0f);
	enemySprite->setScale(0.75f, 0.75f);

	collider->left = this->position.x - 32.f;
	collider->top = this->position.y;
	collider->height = 32.f;
	collider->width = 32.f;
}

Enemy::~Enemy()
{
	delete enemySprite;
	delete collider;
};

void Enemy::Update(float& deltaTime)
{
	position.y += deltaTime*50.f;
	enemySprite->setPosition(position);
	collider->left = position.x - 8.f;
	collider->top = position.y;
}

sf::Sprite* Enemy::GetSprite()
{
	return enemySprite;
}

sf::FloatRect* Enemy::GetCollider()
{
	return collider;
}

bool Enemy::IsDead()
{
	return isDead;
}

void Enemy::Kill()
{
	isDead = true;
}
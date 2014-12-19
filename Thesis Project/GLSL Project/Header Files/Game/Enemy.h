#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy
{
public:
	Enemy();
	Enemy(sf::Vector2f position, sf::Texture& texture);
	~Enemy();
	void Update(float& deltaTime);

	sf::Sprite* GetSprite();
	sf::FloatRect* GetCollider();

	void Kill();

	bool IsDead();

	
private:
	sf::Sprite* enemySprite;
	sf::Vector2f position;

	sf::FloatRect* collider;

	bool isDead;
};
#endif
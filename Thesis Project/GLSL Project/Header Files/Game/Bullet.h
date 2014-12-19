#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet
{
public:
	Bullet();
	Bullet(sf::Vector2f position, float rotation, sf::Texture& texture);
	~Bullet();
	void Update(float& deltaTime);

	sf::Sprite* GetSprite();
	sf::FloatRect* GetCollider();

	void Kill();

	bool IsDead();

private:

	sf::Vector2f position;
	sf::Sprite* bulletSprite;
	sf::FloatRect* collider;

	sf::Vector2f speed;

	bool isDead;

};
#endif
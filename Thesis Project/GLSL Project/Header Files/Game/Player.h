#ifndef PLAYER_H
#define PLAYER_H

#include <SFML\Graphics.hpp>

class Player
{
public:
	Player();
	~Player();
	void Update(float& deltaTime, sf::Vector2f mousePos);

	void Draw(sf::RenderTexture& renderTexture);

	sf::Vector2f GetPosition();

	float GetRotation();


private:
	sf::Texture turretBaseTexture;
	sf::Sprite turretBaseSprite;
	sf::Texture turretTexture;
	sf::Sprite turretSprite;
	
	float rotation;

	void AngleBetween(sf::Vector2f& p1, sf::Vector2f& p2);

	sf::Vector2f position;


};
#endif
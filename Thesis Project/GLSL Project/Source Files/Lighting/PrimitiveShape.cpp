#include "Lighting/PrimitiveShape.h"

PrimitiveShape::PrimitiveShape(void)
{
}

PrimitiveShape::~PrimitiveShape(void)
{
}


//Creating shapes only supports quads right now.
PrimitiveShape::PrimitiveShape(sf::Vector2f position, sf::Vector2f size, sf::FloatRect texCoords, sf::PrimitiveType type)
{
	toRad = 0.01745329251994f;
	this->position = position;
	this->size = size;
	animTimer = 0.0f;
	currentFrame = 0;

	animSpeed = 0.08f;
	//Randomize starting frame for testing
	frameX = 0;//rand()%6;
	frameY = 0;//rand()%4;
	spriteRows = 0;
	spriteColumns = 2;

	
	if(type == sf::Quads)
	{
		sf::FloatRect vertRect = sf::FloatRect(position.x - size.x/2.f, position.y - size.y/2.f, size.x, size.y);
		//Top left
		sf::Vertex* tempVertex1 = new sf::Vertex();
		tempVertex1->position = sf::Vector2f(vertRect.left, vertRect.top);
		tempVertex1->texCoords = sf::Vector2f(texCoords.left, texCoords.top);
		points.push_back(tempVertex1);

		//Top right
		sf::Vertex* tempVertex2 = new sf::Vertex();
		tempVertex2->position = sf::Vector2f(vertRect.left + vertRect.width, vertRect.top);
		tempVertex2->texCoords = sf::Vector2f(texCoords.left + texCoords.width, texCoords.top);
		points.push_back(tempVertex2);

		//Bottom right
		sf::Vertex* tempVertex3 = new sf::Vertex();
		tempVertex3->position = sf::Vector2f(vertRect.left + vertRect.width, vertRect.top + vertRect.height);
		tempVertex3->texCoords = sf::Vector2f(texCoords.left + texCoords.width, texCoords.top + texCoords.height);
		points.push_back(tempVertex3);

		//Bottom left
		sf::Vertex* tempVertex4 = new sf::Vertex();
		tempVertex4->position = sf::Vector2f(vertRect.left, vertRect.top + vertRect.height);
		tempVertex4->texCoords = sf::Vector2f(texCoords.left, texCoords.top + texCoords.height);
		points.push_back(tempVertex4);
	}
}


//
void PrimitiveShape::SetFrameInfo(sf::FloatRect frameInfo)
{
	this->frameInfo = frameInfo;
}

void PrimitiveShape::SetAngle(float angle)
{
	this->angle = angle;
	//Currently only for Quads.
	//for(int i = 0; i < points.size(); i++)
	//{
		sf::FloatRect vertRect = sf::FloatRect(position.x - size.x/2.f, position.y - size.y/2.f, size.x, size.y);

		points[0]->position.x = position.x + (cos(angle * toRad) * (size.x/2.f)) - (sin(angle * toRad) * (size.y/2.f));
		points[0]->position.y = position.y + (sin(angle * toRad) * (size.y/2.f)) + (cos(angle * toRad) * (size.x/2.f));

		points[1]->position.x = position.x + (cos(angle * toRad) * (size.x/2.f)) - (sin(angle * toRad) * (size.y/2.f));
		points[1]->position.y = position.y + (sin(angle * toRad) * (size.y/2.f)) + (cos(angle * toRad) * (size.x/2.f));
		
		points[2]->position.x = position.x + (cos(angle * toRad) * (size.x/2.f)) - (sin(angle * toRad) * (size.y/2.f));
		points[2]->position.y = position.y + (sin(angle * toRad) * (size.y/2.f)) - (cos(angle * toRad) * (size.x/2.f));

		points[3]->position.x = position.x + (cos(angle * toRad) * (size.x/2.f)) - (sin(angle * toRad) * (size.y/2.f));
		points[3]->position.y = position.y + (sin(angle * toRad) * (size.y/2.f)) - (cos(angle * toRad) * (size.x/2.f));
	//}

}

void PrimitiveShape::Update(float &deltaTime)
{

	animTimer += deltaTime;

	if(animTimer >= animSpeed)
	{
		animTimer = 0.0f;
		if(frameX < spriteColumns)
		{
			frameX += 1;
			currentFrame += 1;
		}
		else if(frameX>=spriteColumns)
		{
			frameX=0u;
			if(frameY<spriteRows)
			{
				frameY+=1;
				currentFrame += 1;
			}
			else
			{
				frameX = 0;
				frameY = 0;
				currentFrame = 0;
			}
		}
		//sprite.setTextureRect(sf::IntRect(currentFrameX*sizeX, currentFrameY*sizeY, sizeX, sizeY));
		points[0]->texCoords = sf::Vector2f(frameInfo.left + frameX*frameInfo.width, frameInfo.top + frameY*frameInfo.height);
		points[1]->texCoords = sf::Vector2f((frameInfo.left + frameInfo.width) + frameX*frameInfo.width, frameInfo.top + (float)frameY*frameInfo.height);
		points[2]->texCoords = sf::Vector2f(frameX*frameInfo.width + frameInfo.width, frameY*frameInfo.height + frameInfo.height);
		points[3]->texCoords = sf::Vector2f(frameX*frameInfo.width, frameY*frameInfo.height + frameInfo.height);
	}
	//SetAngle(angle+(deltaTime*45.0f));
}

std::vector<sf::Vertex*> PrimitiveShape::GetPoints()
{
	return points;
}
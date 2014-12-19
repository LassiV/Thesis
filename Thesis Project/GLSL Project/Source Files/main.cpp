#include <SFML/Window.hpp>

#include <Game/Game.h>

int main()
{
	//http://www.geeks3d.com/20110428/shader-library-swirl-post-processing-filter-in-glsl/
	//http://www.redblobgames.com/articles/visibility/
	//http://psvilans.wrongbananas.net/dynamic-2d-lighting/
	//https://briangordon.github.io/2014/08/the-skyline-problem.html
	//https://github.com/LaurentGomila/SFML/wiki/Source%3A-Simple-Collision-Detection-for-SFML-2
	//http://www.bromeon.ch/articles/raii.html
	sf::Clock ticker;
	ticker.restart();
	float deltaTime = 0.0f;
	float effectTimer = 0.0f;

	Game game;

	game.Initialise();

	game.Update();

	//game.Draw();

	return 0;
}
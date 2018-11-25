#include <SFML/Graphics.hpp>
#include <SFML/Window/Cursor.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <cmath>
#include "Game.h"
#include "Level.h"
#include "Enemy.h"

int main()
{
	Game game;
	game.eventLoop();
	return 0;
}
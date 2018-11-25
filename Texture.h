#pragma once
#include <SFML/Graphics.hpp>
#include "Resource.h"
#include "Error.h"


namespace My
{
	class Texture : public sf::Texture
	{
	public:
		bool loadFromFile(const std::string &filename, const sf::IntRect &area = sf::IntRect());
	};
}




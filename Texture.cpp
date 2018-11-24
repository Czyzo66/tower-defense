#include "Texture.h"


bool My::Texture::loadFromFile(const std::string& filename, const sf::IntRect& area)
{
	if (!sf::Texture::loadFromFile(filename, area))
	{
		exit(Error::ERROR_LOADING_TEXTURE);
		return false;
	}
	return true;
}

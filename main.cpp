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
	game.initializeGame();
	game.eventLoop();
	return 0;
}

/*
-----------------------------------------------------------------------
---- first map prototype, made using square vertices and textures: ----
-----------------------------------------------------------------------
class TileMap :public sf::Drawable, public sf::Transformable
{
private:
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
	const int* m_level;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = &m_tileset;
		target.draw(m_vertices, states);
	}
public:
	TileMap(const int* tiles) : m_level(tiles) {}
	bool load(const std::string& tileset, sf::Vector2u tileSize, unsigned int width, unsigned int height)
	{
		if (!m_tileset.loadFromFile(tileset))
			return false;
		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize(width * height * 4);
		for (unsigned int i = 0; i < height; ++i)
			for (unsigned int j = 0; j < width; ++j)
			{
				//get tile type
				int tileType = m_level[i * width + j];
				//get tile texture coordinates according to its type
				int tx = tileType % (m_tileset.getSize().x / tileSize.x); //for 0, 1, 2, 3 should be 0, 1, 0, 1
				int ty = tileType / (m_tileset.getSize().x / tileSize.x); //for 0, 1, 2, 3 should be 0, 0, 1, 1
				sf::Vertex* quad = &m_vertices[(i * width + j) * 4];
				quad[0].position = sf::Vector2f(j * tileSize.x, i * tileSize.y); //upper left corner
				quad[1].position = sf::Vector2f((j + 1) * tileSize.x, i * tileSize.y); //upper right corner
				quad[2].position = sf::Vector2f((j + 1) * tileSize.x, (i + 1) * tileSize.y); //lower right corner
				quad[3].position = sf::Vector2f(j * tileSize.x, (i + 1) * tileSize.y); //lower left corner
				if (tileType != 4)
				{
					quad[0].texCoords = sf::Vector2f(tx * tileSize.x, ty * tileSize.y); //upper left corner
					quad[1].texCoords = sf::Vector2f((tx + 1) * tileSize.x, ty * tileSize.y); //upper right corner
					quad[2].texCoords = sf::Vector2f((tx + 1) * tileSize.x, (ty + 1) * tileSize.y); //lower right corner
					quad[3].texCoords = sf::Vector2f(tx * tileSize.x, (ty + 1) * tileSize.y); //lower left corner
				}
			}
		return true;
	}
};

template <typename T>
const sf::Vector2f& getCenteringCoords(const sf::RenderTarget& target, const T entity, bool originInCenter = false) //sf::Sprite&
{
	if (originInCenter == false) {
		float ex = (target.getSize().x - entity.getGlobalBounds().width) / 2;
		float ey = (target.getSize().y - entity.getGlobalBounds().height) / 2;
		return sf::Vector2f(ex, ey);
	}
	else
	{
		float ex = target.getSize().x / 2;
		float ey = target.getSize().y / 2;
		return sf::Vector2f(ex, ey);
	}
}
*/
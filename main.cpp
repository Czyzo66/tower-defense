#include <SFML/Graphics.hpp>
#include <SFML/Window/Cursor.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Audio.hpp>
#include <cstdint>
#include <string>
#include <vector>
#include <cmath>
#include "Enemy.h"

namespace Tile
{
	constexpr int size(45);
	constexpr int width(45);
	constexpr int height(45);
	enum Type
	{
		TYPE_GRASS,
		TYPE_ROAD,
		TYPE_BUSH,
		TYPE_TOWER,
	};
}

enum Player
{
	PLAYER_IN_MENU,
	PLAYER_IN_GAME,
};

enum Error
{
	ERROR_LOADING_TEXTURE,	//0
	ERROR_LOADING_SOUND,	//1
	ERROR_LOADING_TILEMAP,	//2
	ERROR_LOADING_FONT,		//3
};

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

//sf::Sprite& createSprite(const std::string& textureFile)
//{
//	sf::Texture texture;
//	if (!texture.loadFromFile(textureFile))
//		return //Error::ERROR_LOADING_TEXTURE;
//	sf::Sprite sprite;
//	sprite.setTexture(texture);
//	return sprite;
//}

class Turret
{
private:
	sf::Vector2f position;
	sf::Sprite left;
	sf::Sprite mid;
	sf::Sprite right;
	sf::Texture texture;
	std::string name;
	int damage;
public:

};



void drawButtonScaledIfActive(float scale, sf::Sprite& button, bool& buttonActive, sf::RenderTarget& target)
{
	if (buttonActive && button.getScale().x < scale && button.getScale().y < scale)
	{
		button.setScale(scale, scale);
		target.draw(button);
	}
	else if (!buttonActive)
	{
		button.setScale(1, 1);
		target.draw(button);
	}
	else
		target.draw(button);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 900), "Post-Ironic Aesthetic Experience", sf::Style::Fullscreen);
	//cursor
	sf::Image cursorImg;
	cursorImg.loadFromFile("textures\\cursor.png");
	sf::Cursor cursor;
	cursor.loadFromPixels(cursorImg.getPixelsPtr(), cursorImg.getSize(), { 0,0 });
	window.setMouseCursor(cursor);
	//_cursor

	//fonts
	sf::Font fontFullPack2025;
	if (!fontFullPack2025.loadFromFile("fonts\\full_pack_2025.ttf")) 
		return Error::ERROR_LOADING_FONT;
	sf::Font fontNeuropolitical;
	if (!fontNeuropolitical.loadFromFile("fonts\\neuropolitical_rg.ttf"))
		return Error::ERROR_LOADING_FONT;
	//_fonts

	//menu
	sf::Texture tBackground;
	if (!tBackground.loadFromFile("textures\\background.jpg"))
		return Error::ERROR_LOADING_TEXTURE;
	sf::Sprite background(tBackground);
	sf::Vector2f backgroundSize(tBackground.getSize().x, tBackground.getSize().y); //background size
	sf::Texture tTitle;
	if (!tTitle.loadFromFile("textures\\title.png"))
		return Error::ERROR_LOADING_TEXTURE;
	sf::Sprite title(tTitle);
	//_menu

	//buttons	
	sf::Texture tButtonPlay;
	if (!tButtonPlay.loadFromFile("textures\\button_play.png"))
		return Error::ERROR_LOADING_TEXTURE;
	sf::Sprite buttonPlay(tButtonPlay);
	sf::Texture tButtonOptions;
	if (!tButtonOptions.loadFromFile("textures\\button_options.png"))
		return Error::ERROR_LOADING_TEXTURE;
	sf::Sprite buttonOptions(tButtonOptions);
	sf::Texture tButtonExit;
	if (!tButtonExit.loadFromFile("textures\\button_exit.png"))
		return Error::ERROR_LOADING_TEXTURE;
	sf::Sprite buttonExit(tButtonExit);
	//_buttons

	//sounds
	sf::SoundBuffer bufferDoot;
	if (!bufferDoot.loadFromFile("sound\\SKULL-TRUMPET.wav")) 
		return Error::ERROR_LOADING_SOUND;
	sf::Sound soundDoot(bufferDoot);
	sf::SoundBuffer bufferHit;
	if (!bufferHit.loadFromFile("sound\\hitmarker.wav")) 
		return Error::ERROR_LOADING_SOUND;
	sf::Sound soundHit(bufferHit);
	//_sounds

	//enemies
	Enemy hotdog(420, 4);
	if (!hotdog.load("textures\\hotdog.png", sf::Vector2f(30, 30)))
		return Error::ERROR_LOADING_TEXTURE;
	hotdog.setPosition(sf::Vector2f(-30, 98));
	std::vector<sf::Vector2f> track {sf::Vector2f(188.0f, 98.0f),
		sf::Vector2f(188.0f, 278.0f),
		sf::Vector2f(323.0f, 278.0f),
		sf::Vector2f(323.0f, 143.0f),
		sf::Vector2f(593.0f, 143.0f),
		sf::Vector2f(593.0f, 458.0f),
		sf::Vector2f(278.0f, 458.0f),
		sf::Vector2f(278.0f, 548.0f),
		sf::Vector2f(180.0f, 420.0f)};
	hotdog.setTrack(track);
	Enemy hotdog2(420, 10);
	if (!hotdog2.load("textures\\hotdog2.png", sf::Vector2f(30, 30)))
		return Error::ERROR_LOADING_TEXTURE;
	hotdog2.setPosition(sf::Vector2f(-30, 98));
	hotdog2.setTrack(track);
	bool hotdog2active = false;
	Enemy hotdog3(420, 10);
	if (!hotdog3.load("textures\\hotdog.png", sf::Vector2f(30, 30)))
		return Error::ERROR_LOADING_TEXTURE;
	hotdog3.setPosition(sf::Vector2f(-30, 98));
	hotdog3.setTrack(track);
	/*sf::Texture tHotdogLeft;
	if (!tHotdogLeft.loadFromFile("hotdog_left.png"))
		return Error::ERROR_LOADING_TEXTURE;
	sf::Sprite hotdogLeft(tHotdogLeft);*/
	//_enemies

	//0 - grass
	//1 - bush
	//2 - road
	//3 - turret
	const int level[] =
	{
		0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 2, 0, 1, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 1, 0,
		0, 1, 0, 0, 2, 0, 0, 2, 3, 3, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 2, 0, 3, 2, 3, 0, 1, 0, 0, 2, 0, 0, 0, 1, 0, 0,
		0, 0, 0, 1, 2, 2, 2, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 0, 0, 0, 3, 0, 1, 0, 1, 2, 1, 0, 1, 0, 0, 0,
		1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0,
		0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	TileMap map(level);
	if (!map.load("textures\\testtextures.png", sf::Vector2u(45, 45), 20, 14))
		return Error::ERROR_LOADING_TILEMAP;

	int state = Player::PLAYER_IN_MENU;

	title.setPosition(getCenteringCoords(window, title).x, (window.getSize().y - title.getLocalBounds().height) * 0.14);
	buttonPlay.setOrigin((buttonPlay.getGlobalBounds().width / 2), (buttonPlay.getGlobalBounds().height / 2));
	buttonPlay.setPosition(window.getSize().x / 2, window.getSize().y*(5 / 8.0));
	sf::FloatRect buttonPlayBounds = buttonPlay.getGlobalBounds();
	bool buttonPlayActive(false);
	buttonOptions.setOrigin((buttonOptions.getGlobalBounds().width / 2), (buttonOptions.getGlobalBounds().height / 2));
	buttonOptions.setPosition(window.getSize().x / 2, window.getSize().y*(6 / 8.0));
	sf::FloatRect buttonOptionsBounds = buttonOptions.getGlobalBounds();
	bool buttonOptionsActive(false);
	buttonExit.setOrigin((buttonExit.getGlobalBounds().width / 2), (buttonExit.getGlobalBounds().height / 2));
	buttonExit.setPosition(window.getSize().x / 2, window.getSize().y*(7 / 8.0));
	sf::FloatRect buttonExitBounds = buttonExit.getGlobalBounds();
	bool buttonExitActive(false);

	sf::Clock clock;

	window.setMouseCursorGrabbed(true);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::GainedFocus:
				window.setMouseCursorGrabbed(true);
				break;
			case sf::Event::LostFocus:
				window.setMouseCursorGrabbed(false);
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape) window.close();
				break;
			case sf::Event::MouseMoved:
				if (buttonPlayBounds.contains(event.mouseMove.x, event.mouseMove.y))
					buttonPlayActive = true;
				else
					buttonPlayActive = false;
				if (buttonOptionsBounds.contains(event.mouseMove.x, event.mouseMove.y))
					buttonOptionsActive = true;
				else
					buttonOptionsActive = false;
				if (buttonExitBounds.contains(event.mouseMove.x, event.mouseMove.y))
					buttonExitActive = true;
				else
					buttonExitActive = false;
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (state == Player::PLAYER_IN_MENU)
					{
						sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
						if (buttonPlayBounds.contains(static_cast<sf::Vector2f>(mousePosition)))
						{
							state = Player::PLAYER_IN_GAME;
							hotdog.resetTimer();
							clock.restart();
						}
							state = Player::PLAYER_IN_GAME;
							hotdog.resetTimer();
						if (buttonExitBounds.contains(static_cast<sf::Vector2f>(mousePosition)))
							window.close();
					}
					else state = Player::PLAYER_IN_MENU;
				}
				break;
			default:
				break;
			}
		}

		window.clear();
		switch (state)
		{
		case Player::PLAYER_IN_MENU:
			background.setScale((window.getSize().x / backgroundSize.x), (window.getSize().y / backgroundSize.y));
			window.draw(background);
			window.draw(title);
			drawButtonScaledIfActive(1.1f, buttonPlay, buttonPlayActive, window);
			drawButtonScaledIfActive(1.1f, buttonOptions, buttonOptionsActive, window);
			drawButtonScaledIfActive(1.1f, buttonExit, buttonExitActive, window);
			break;
		case Player::PLAYER_IN_GAME:
			window.draw(map);
			hotdog.move();
			window.draw(hotdog);
			if (clock.getElapsedTime().asSeconds() > 2)
			{
				if (hotdog2active == false)
					hotdog2.resetTimer();
				hotdog2active = true;
				hotdog2.move();
				window.draw(hotdog2);
			}
			//hotdog.draw(window);
			//clock.restart();
			break;
		default:
			break;
		}		
		window.display();
	}

	return 0;
}
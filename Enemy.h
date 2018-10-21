#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <string>
#include <vector>
#include <cmath>

class Enemy :public sf::Drawable
{
private:
	sf::Clock m_clock;
	sf::Vector2f m_size;
	sf::Vector2f m_position;
	sf::Texture m_texture;
	sf::Sprite m_left;
	sf::Sprite m_mid;
	sf::Sprite m_right;
	std::vector<sf::Vector2f> m_track;
	int m_hp;
	double m_speed;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Enemy(int hp, int speed) : m_hp(hp), m_speed(speed), m_position(sf::Vector2f(0, 0)) {}
	bool load(const std::string& textureFile, sf::Vector2f enemySize);
	bool calculateTrack(std::vector<sf::Vector2f>& track, int targetX, int targetY, int textureX, int textureY);
	bool calculateTrack(std::vector<sf::Vector2f>& track, sf::Vector2u targetSize, sf::Vector2f textureSize);
	bool setTrack(std::vector<sf::Vector2f>& track);
	bool setPosition(sf::Vector2f position);
	bool move();
	void resetTimer();
};
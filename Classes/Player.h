#pragma once
#include <SFML\Graphics.hpp>
#include "Tilemap.h"

class Player : public sf::Drawable, public sf::Transformable
{
public:
	Player();
	~Player();

	void Initialise(std::string filename, int direction, sf::Vector2f position);
	void Update(sf::Time elapsedTime);
	void GetPosition(int& x, int & y) { x = m_playerSprite.getPosition().x; y = m_playerSprite.getPosition().y; }
	void GetSize(int& x, int& y) { x = m_playerSprite.getLocalBounds().left + m_playerSprite.getLocalBounds().width, y = m_playerSprite.getLocalBounds().top + m_playerSprite.getLocalBounds().height;  }
	void MoveUp(sf::Time elapsedTime);
	void MoveDown(sf::Time elapsedTime);
	void MoveLeft(sf::Time elapsedTime);
	void MoveRight(sf::Time elapsedTime);

	void SetDirection(int direction);
	int GetDirection();
	void Dead() { m_Dead = true; }
	bool getDead() { return m_Dead; }
	void ChangeDirection();

	void SetAirBorne(bool air) { m_inAir = air; }
	bool getAir() { return m_inAir; }

private:
		
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	enum direction {
		NONE,
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	bool m_Dead;
	bool m_inAir;
	bool increase;

	direction m_Direction;

	sf::Sprite m_playerSprite;
	sf::FloatRect m_TextureRect;

	sf::Texture m_playerTexture;
	sf::Vector2f m_spriteOrigin;
	//Tilemap * m_pTilemap;

};
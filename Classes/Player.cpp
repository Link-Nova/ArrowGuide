#include "Player.h"

Player::Player()
	:m_Direction(NONE)
	,m_Dead(false)
{

}

Player::~Player()
{

}

void Player::Initialise(std::string filename, int direction, sf::Vector2f position)
{
	if (direction == 1)
	{
		m_Direction = UP;
		m_playerSprite.setRotation(180.0f);
	}
	else if (direction == 2)
	{
		m_Direction = DOWN;
		m_playerSprite.setRotation(360.0f);
	}
	else if (direction == 3)
	{
		m_Direction = LEFT;
		m_playerSprite.setRotation(90.0f);
	}
	else if (direction == 4)
	{
		m_Direction = RIGHT;
		m_playerSprite.setRotation(270.0f);
	}

	m_playerTexture.loadFromFile(filename);
	m_playerSprite.setTexture(m_playerTexture);
	m_TextureRect = m_playerSprite.getLocalBounds();

	m_spriteOrigin = sf::Vector2f(m_TextureRect.height / 2, m_TextureRect.width / 2);
	m_playerSprite.setOrigin(m_spriteOrigin);

	m_playerSprite.setPosition(position.x, position.y);
}

void Player::Update(sf::Time elapsedTime)
{
	if (m_Direction == NONE)
	{
		m_playerSprite.move(0.0f, 0.0f);
	}
	else if (m_Direction == RIGHT)
	{
		this->MoveRight(elapsedTime);
		m_playerSprite.setRotation(270.0f);
	}
	else if (m_Direction == LEFT)
	{
		this->MoveLeft(elapsedTime);
		m_playerSprite.setRotation(90.0f);
	}
	else if (m_Direction == UP)
	{
		this->MoveUp(elapsedTime);
		m_playerSprite.setRotation(180.0f);
	}
	else if (m_Direction == DOWN)
	{
		this->MoveDown(elapsedTime);
		m_playerSprite.setRotation(360.0f);
	}
}

void Player::ChangeDirection()
{
	if (m_Direction == RIGHT)
	{
		m_Direction = DOWN;
		m_playerSprite.rotate(90.0f);
	}
	else if (m_Direction == LEFT)
	{
		m_Direction = UP;
		m_playerSprite.rotate(90.0f);
	}
	else if (m_Direction == UP)
	{
		m_Direction = RIGHT;
		m_playerSprite.rotate(90.0f);
	}
	else if (m_Direction == DOWN)
	{
		m_Direction = LEFT;
		m_playerSprite.rotate(90.0f);
	}
}
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// draw 
	target.draw(m_playerSprite, states);
}

void Player::MoveRight(sf::Time elapsedTime)
{
	m_playerSprite.move(225 * elapsedTime.asSeconds(), 0);
}

void Player::MoveLeft(sf::Time elapsedTime)
{
	m_playerSprite.move(-225 * elapsedTime.asSeconds(), 0);
}

void Player::MoveUp(sf::Time elapsedTime)
{
	m_playerSprite.move(0, -225 * elapsedTime.asSeconds());
}

void Player::MoveDown(sf::Time elapsedTime)
{
	m_playerSprite.move(0, 225 * elapsedTime.asSeconds());
}

void Player::SetDirection(int direction)
{
	if (direction == 0)
		m_Direction = NONE;
	else if (direction == 1)
		m_Direction = UP;
	else if (direction == 2)
		m_Direction = DOWN;
	else if (direction == 3)
		m_Direction = LEFT;
	else if (direction == 4)
		m_Direction = RIGHT;
}

int Player::GetDirection()
{
	return m_Direction;
}
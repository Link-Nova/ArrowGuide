#include "Tiles.h"

Tiles::Tiles(int ID, sf::RenderWindow& win)
	:m_isSelected(false)
	,m_numOfTiles(0)
	,m_window(win)
{
	m_tileSetID = ID;
}

Tiles::~Tiles()
{
	
}

void Tiles::Initialise(std::string filename, int numOfTiles, sf::Vector2f pos)
{

	m_numOfTiles = numOfTiles;

	m_TileTexture.loadFromFile(filename);
	m_TileSprite.setTexture(m_TileTexture);
	
	m_TileSprite.setPosition(pos.x, pos.y);

	m_numberFont.loadFromFile("Media/Fonts/8-Bit Madness.ttf");
	m_numberText.setFont(m_numberFont);

	std::string toString = std::to_string(m_numOfTiles);

	m_numberText.setString(toString);
	m_numberText.setPosition(pos.x + 100, pos.y - 30);
	//m_numberText.setFillColor(sf::Color(255, 50, 255));
	m_numberText.setCharacterSize(40);

	if (!m_isSelected && m_numOfTiles == 0)
		m_TileSprite.setColor(sf::Color(40, 40, 40));
}

void Tiles::Update(sf::Time elapsedTime)
{
	m_TextureRect = m_TileSprite.getGlobalBounds();
	
	bool m_mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

	sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

	if (m_mousePressed && !m_prevSelected && (mousePos.x > m_TextureRect.left && mousePos.x < m_TextureRect.left + m_TextureRect.width) 
		&& (mousePos.y > m_TextureRect.top && mousePos.y < m_TextureRect.top + m_TextureRect.height) && !m_isSelected && m_numOfTiles != 0)
	{
		m_TileSprite.setColor(sf::Color(0, 0, 255));
		m_isSelected = true;
	}
	else if (m_mousePressed && !m_prevSelected && (mousePos.x > m_TextureRect.left && mousePos.x < m_TextureRect.left + m_TextureRect.width)
		&& (mousePos.y > m_TextureRect.top && mousePos.y < m_TextureRect.top + m_TextureRect.height) && m_isSelected &&  m_numOfTiles != 0)
	{
		m_TileSprite.setColor(sf::Color(255, 255, 255));
		m_isSelected = false;
	}

	std::string toString = std::to_string(m_numOfTiles);
	m_numberText.setString(toString);


	if(!m_isSelected && m_numOfTiles == 0)
		m_TileSprite.setColor(sf::Color(40, 40, 40));
	else if(!m_isSelected)
		m_TileSprite.setColor(sf::Color(255, 255, 255));

	m_prevSelected = m_mousePressed;
}

void Tiles::isPlaced()
{
	//m_TileSprite.setColor(sf::Color(255, 255, 255));
	m_isSelected = false;
	RemoveTile();
}

void Tiles::Deselected()
{
	m_TileSprite.setColor(sf::Color(255, 255, 255));
	m_isSelected = false;
}

void Tiles::AddTile()
{
	m_numOfTiles++;
}

void Tiles::RemoveTile()
{
	m_numOfTiles--;
}

void Tiles::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// draw 
	target.draw(m_TileSprite, states);
	target.draw(m_numberText, states);
}
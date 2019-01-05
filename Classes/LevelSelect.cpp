#include "LevelSelect.h"

LevelSelect::LevelSelect(sf::RenderWindow& win, int levUnlocked)
	:m_window(win)
	,m_levelsUnlocked(levUnlocked)
{

}

LevelSelect::~LevelSelect()
{

}

void LevelSelect::Initialise()
{
	sf::Vector2f posLevel(350,200);
	std::string toString;

	m_Font.loadFromFile("Media/Fonts/8-Bit Madness.ttf");

	m_title.setFont(m_Font);
	m_title.setString("Level Select");
	m_title.setCharacterSize(100);

	m_title.setPosition(sf::Vector2f(400, 20));

	for (int i = 0; i < NUM_LEVELS / 5; i++)
		for (int j = 0; j < 5; j++)
		{
			//sprites
			m_levelNumberTex[j + i * 5].loadFromFile("Media/Images/levelselect.png");
			m_levelNumberSpr[j + i * 5].setTexture(m_levelNumberTex[j + i * 5]);

			m_levelNumberSpr[j + i * 5].setPosition(posLevel.x + (j * 130), posLevel.y + (i * 130));
			m_textureRect[j + i * 5] = m_levelNumberSpr[j + i * 5].getGlobalBounds();

			toString = std::to_string(j + i * 5 + 1);

			//text
			m_numberText[j + i * 5].setFont(m_Font);
			m_numberText[j + i * 5].setFillColor(sf::Color(0, 0, 0));

			m_numberText[j + i * 5].setString(toString);
			if(j + i * 5 < 9)
				m_numberText[j + i * 5].setPosition(posLevel.x + (j * 130 + 52), posLevel.y + (i * 130 + 30));
			else
				m_numberText[j + i * 5].setPosition(posLevel.x + (j * 130 + 46), posLevel.y + (i * 130 + 30));

			m_numberText[j + i * 5].setCharacterSize(40);

			if (j + i * 5 >= m_levelsUnlocked)
			{
				m_levelNumberSpr[j + i * 5].setColor(sf::Color(50, 50, 50));
				m_numberText[j + i * 5].setFillColor(sf::Color(0, 0, 140));
			}
		}
	
	m_backgroundTex.loadFromFile("Media/Images/background.png");
	m_backgroundSpr.setTexture(m_backgroundTex);

}

int LevelSelect::Update(sf::Time elapsedTime)
{

	sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

	for (int i = 0; i < NUM_LEVELS; i++)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (mousePos.x > m_textureRect[i].left && mousePos.x < m_textureRect[i].left + m_textureRect[i].width)
			&& (mousePos.y > m_textureRect[i].top && mousePos.y < m_textureRect[i].top + m_textureRect[i].height) && i < m_levelsUnlocked)
		{
			return i + 1;
		}
	}

	return -1;
}

void LevelSelect::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(m_backgroundSpr, states);
	target.draw(m_title, states);

	for (int i = 0; i < NUM_LEVELS; i++)
	{
		target.draw(m_levelNumberSpr[i], states);
		target.draw(m_numberText[i], states);
	}

}
#include "LevelGUI.h"

LevelGUI::LevelGUI(sf::RenderWindow& win)
	:m_window(win)
	,m_backClicked(false)
	,m_playClicked(false)
	,m_levelDone(false)
	,m_resetClicked(false)
{

}

LevelGUI::~LevelGUI()
{

}

void LevelGUI::Initialise()
{
	for (int i = 0; i <= 2; i++)
	{
		m_font[i].loadFromFile("Media/Fonts/8-Bit Madness.ttf");
		m_text[i].setFont(m_font[i]);
		m_text[i].setCharacterSize(50);

		if (i == 0)
		{
			m_text[i].setString("Play");
			m_text[i].setPosition(sf::Vector2f(1069, 683));
			m_sprite[i].setPosition(sf::Vector2f(1044, 690));
			m_texture[i].loadFromFile("Media/Images/ButtonReset.png");
			m_sprite[i].setTexture(m_texture[0]);
			m_sprite[i].scale(1.2f, 1.2f);
		}
		else if (i == 1)
		{
			m_text[i].setString("Back");
			m_text[i].setPosition(sf::Vector2f(1237, 683));
			m_sprite[i].setPosition(sf::Vector2f(1215, 690));
			m_texture[i].loadFromFile("Media/Images/ButtonReset2.png");
			m_sprite[i].setTexture(m_texture[0]);
			m_sprite[i].scale(1.2f, 1.2f);
		}
		else if (i == 2)
		{
			m_text[i].setString("Reset");
			m_text[i].setPosition(sf::Vector2f(1153, 18));
			m_text[i].setCharacterSize(40);

			m_texture[i].loadFromFile("Media/Images/ButtonReset.png");
			m_sprite[i].setPosition(sf::Vector2f(1140, 22));
			m_sprite[i].setTexture(m_texture[2]);
		}

		m_textureRect[i] = m_sprite[i].getGlobalBounds();
	}
}

void LevelGUI::Update(sf::Time elapsedTime)
{
	if (!m_levelDone)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

		bool m_mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

		for (int i = 0; i <= 2; i++)
		{
			if (m_mousePressed && !m_prevSelected && (mousePos.x > m_textureRect[0].left && mousePos.x < m_textureRect[0].left + m_textureRect[0].width)
				&& (mousePos.y > m_textureRect[0].top && mousePos.y < m_textureRect[0].top + m_textureRect[0].height))
			{
				m_playClicked = !m_playClicked;
				i = 2;
			}
			else if (m_mousePressed && !m_prevSelected && (mousePos.x > m_textureRect[1].left && mousePos.x < m_textureRect[1].left + m_textureRect[1].width)
				&& (mousePos.y > m_textureRect[1].top && mousePos.y < m_textureRect[1].top + m_textureRect[1].height))
			{
				m_backClicked = true;
			}
			else if (m_mousePressed && !m_prevSelected && (mousePos.x > m_textureRect[2].left && mousePos.x < m_textureRect[2].left + m_textureRect[2].width)
				&& (mousePos.y > m_textureRect[2].top && mousePos.y < m_textureRect[2].top + m_textureRect[2].height))
			{
				m_resetClicked = true;
			}
		}

		if (m_playClicked)
		{
			m_text[0].setString("Retry");
			m_text[0].setPosition(sf::Vector2f(1059, 683));
			m_sprite[0].setTexture(m_texture[1]);
		}
		else
		{
			m_text[0].setString("Play");
			m_text[0].setPosition(sf::Vector2f(1069, 683));
			m_sprite[0].setTexture(m_texture[0]);
		}

		m_prevSelected = m_mousePressed;
	}
}

void LevelGUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	states.transform *= getTransform();

	for (int i = 0; i <= 2; i++)
	{
		target.draw(m_sprite[i], states);
		target.draw(m_text[i], states);
	}
}
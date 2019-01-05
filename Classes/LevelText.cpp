#include "LevelText.h"

LevelText::LevelText()
{

}

LevelText::~LevelText()
{

}

void LevelText::Initialise(std::string text, std::string font)
{
	m_font.loadFromFile(font);
	m_text.setFont(m_font);

	m_text.setString(text);
	m_text.setCharacterSize(100);
	m_text.setFillColor(sf::Color(30,35,30));
	m_text.setPosition(300, 500);

}

void LevelText::Update(sf::Time elapsedTime)
{

}

void LevelText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	target.draw(m_text, states);
	target.draw(m_sprite, states);
}
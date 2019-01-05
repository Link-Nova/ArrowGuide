#pragma once
#include "SFML\Graphics.hpp"

class LevelSelect : public sf::Drawable, public sf::Transformable
{
public:
	LevelSelect(sf::RenderWindow& win, int levUnlocked);
	~LevelSelect();

	void Initialise();
	int Update(sf::Time elapsedTime);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


	const int NUM_LEVELS = 20;

	sf::Texture m_levelNumberTex[20];
	sf::Sprite m_levelNumberSpr[20];

	sf::RenderWindow& m_window;

	sf::Text m_numberText[20];
	sf::Text m_title;
	sf::Font m_Font;

	sf::FloatRect m_textureRect[20];

	sf::Texture m_backgroundTex;
	sf::Sprite m_backgroundSpr;

	int m_levelsUnlocked;
};

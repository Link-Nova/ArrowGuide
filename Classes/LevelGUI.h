#pragma once
#include <SFML/Graphics.hpp>

class LevelGUI : public sf::Drawable, public sf::Transformable
{
public:

	LevelGUI(sf::RenderWindow& win);
	~LevelGUI();

	void Initialise();
	void Update(sf::Time elapsedTime);

	void setPlay(bool play) { m_playClicked = play; }
	void setBack(bool back) { m_backClicked = back; }
	void setReset(bool reset) { m_resetClicked = reset; }
	void setLevelDone(bool done) { m_levelDone = done; }

	bool getPlay() { return m_playClicked; }
	bool getBack() { return m_backClicked; }
	bool getReset() { return m_resetClicked; }
	
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool m_playClicked;
	bool m_backClicked;
	bool m_levelDone;
	bool m_resetClicked;

	sf::Text m_text[4];
	sf::Font m_font[4];

	sf::Texture m_texture[4];
	sf::Sprite m_sprite[4];

	sf::FloatRect m_textureRect[4];

	sf::RenderWindow& m_window;

	bool m_prevSelected;
};
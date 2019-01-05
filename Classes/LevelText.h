#pragma once
#include <SFML\Graphics.hpp>

class LevelText : public sf::Drawable, public sf::Transformable
{
public:
	LevelText();
	~LevelText();

	void Initialise(std::string text, std::string font);
	void Update(sf::Time elaspedTime);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Text m_text;

	sf::Font m_font;

	sf::Texture m_texture;
	sf::Sprite m_sprite;

};

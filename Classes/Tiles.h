#pragma once
#include <SFML\Graphics.hpp>

class Tiles : public sf::Drawable, public sf::Transformable
{
public:

	Tiles(int ID, sf::RenderWindow& win);
	~Tiles();

	void Initialise(std::string texture, int numOfTiles, sf::Vector2f pos);
	void Update(sf::Time elapsedTime);

	void AddTile();
	void RemoveTile();

	void isSelected(bool isSelected) { m_isSelected = isSelected; }
	bool getSelected() { return m_isSelected; }

	int getID() { return m_tileSetID; }
	void isPlaced();
	void Deselected();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool m_isSelected;
	int m_numOfTiles;
	int m_tileSetID;

	sf::RenderWindow& m_window;

	sf::Texture m_TileTexture;
	sf::FloatRect m_TextureRect;

	sf::Sprite m_TileSprite;

	bool m_prevSelected;

	sf::Text m_numberText;
	sf::Font m_numberFont;
};

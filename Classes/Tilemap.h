#pragma once
#include <SFML\Graphics.hpp>

class Tilemap : public sf::Drawable, public sf::Transformable
{
public:
	Tilemap();
	~Tilemap();
	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
	int getTileAtPosition(int x, int y);
	int getTileNumber(int x, int y);
	void replaceTileNumber(int number, int x, int y);
	void UpdateMap();

	sf::Vector2u getTileSize() { return m_tileSize; }
private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int m_mapWidth;
	int m_mapHeight;
	sf::Vector2u m_tileSize;
	int* m_tileIndicies;

	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
};
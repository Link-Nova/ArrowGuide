#include "Tilemap.h"

Tilemap::Tilemap()
	:m_mapHeight(0)
	,m_mapWidth(0)
{

}

Tilemap::~Tilemap()
{
	delete[] m_tileIndicies;
}

bool Tilemap::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
{
	// load the tileset texture
	if (!m_tileset.loadFromFile(tileset))
		return false;

	m_tileIndicies = new int[width * height];
	m_tileSize = tileSize;

	// resize the vertex array to fit the level size
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(width * height * 4);

	m_mapHeight = height;
	m_mapWidth = width;

	// populate the vertex array, with one quad per tile
	for (unsigned int i = 0; i < width; ++i)
		for (unsigned int j = 0; j < height; ++j)
		{
			// get the current tile number
			int tileNumber = tiles[i + j * width];
			m_tileIndicies[i + j * width] = tileNumber;

			// find its position in the tileset texture
			int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
			int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
		}

	return true;
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &m_tileset;
	
	// draw the vertex array
	target.draw(m_vertices, states);
}

int Tilemap::getTileAtPosition(int x, int y)
{
	int numTiles = 0;

	x = x / m_tileSize.x;
	y = y / m_tileSize.y;

	for (int i = 0; i < m_mapWidth; ++i)
		for (int j = 0; j < m_mapHeight; ++j)
		{
			if (x == i && y == j)
			{
				return m_tileIndicies[i + j * m_mapWidth];
			}

			numTiles++;
		}
}

int Tilemap::getTileNumber(int x, int y)
{
	int numTiles = 0;

	x = x / m_tileSize.x;
	y = y / m_tileSize.y;

	for (int i = 0; i < m_mapHeight; ++i)
		for (int j = 0; j < m_mapWidth; ++j)
		{
			if (y == i && x == j)
			{
				return numTiles;
			}

			numTiles++;
		}
}

void Tilemap::replaceTileNumber(int number, int x, int y)
{
	int numTiles = 0;

	x = x / m_tileSize.x;
	y = y / m_tileSize.y;

	for (int i = 0; i < m_mapWidth; ++i)
		for (int j = 0; j < m_mapHeight; ++j)
		{
			if (x == i && y == j)
			{
				m_tileIndicies[i + j * m_mapWidth] = number;
				UpdateMap();
			}

			numTiles++;
		}
}

void Tilemap::UpdateMap()
{
	for (unsigned int i = 0; i < m_mapWidth; ++i)
		for (unsigned int j = 0; j < m_mapHeight; ++j)
		{
			// get the current tile number
			int tileNumber = m_tileIndicies[i + j * m_mapWidth];
			
			// find its position in the tileset texture
			int tu = tileNumber % (m_tileset.getSize().x / m_tileSize.x);
			int tv = tileNumber / (m_tileset.getSize().x / m_tileSize.y);

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &m_vertices[(i + j * m_mapWidth) * 4];

			quad[0].position = sf::Vector2f(i * m_tileSize.x, j * m_tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * m_tileSize.x, j * m_tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * m_tileSize.x, (j + 1) * m_tileSize.y);
			quad[3].position = sf::Vector2f(i * m_tileSize.x, (j + 1) * m_tileSize.y);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * m_tileSize.x, tv * m_tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * m_tileSize.x, tv * m_tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * m_tileSize.x, (tv + 1) * m_tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * m_tileSize.x, (tv + 1) * m_tileSize.y);
		}

}
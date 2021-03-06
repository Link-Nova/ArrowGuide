#pragma once
#include <SFML\Graphics.hpp>
#include "Level.h"
#include "Tiles.h"
#include "LevelText.h"

class Level6 : public Level
{
public:
	Level6(sf::RenderWindow& win);
	~Level6();

	virtual void Initialise();
	virtual void InitialiseTiles();
	virtual void Update(sf::Time elapsedTime, LevelGUI*& LevelGUI);
	virtual void DeleteResources();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool running;

	Tilemap* m_pTilemap;
	Player* m_pPlayer;

	Tiles* m_pTileDown;
	Tiles* m_pTileUp;
	Tiles* m_pTileLeft;
	Tiles* m_pTileRight;

	LevelText* m_pLevelText;

	sf::RenderWindow& m_window;

	sf::Time m_completeTime;

	sf::Vector2i playerPos;
	sf::Vector2i bridge1Pos;
	sf::Vector2i bridge2Pos;

	sf::Texture m_paneltex;
	sf::Sprite m_panelspr;

	bool m_spacePrevPressed;
};
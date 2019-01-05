#pragma once
#include <SFML\Graphics.hpp>
#include "Level.h"
#include "Tiles.h"
#include "LevelText.h"

class Level1 : public Level
{
public:
	Level1(sf::RenderWindow& win);
	~Level1();

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

	sf::Vector2i playerPos;

	sf::Time m_completeTime;

	sf::Texture m_paneltex;
	sf::Sprite m_panelspr;

	bool m_spacePrevPressed;
};
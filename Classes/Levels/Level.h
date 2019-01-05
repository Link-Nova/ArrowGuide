#pragma once
#include <SFML\Graphics.hpp>
#include "Player.h"
#include "Tilemap.h"
#include "Tiles.h"
#include "LevelGUI.h"

class Level : public sf::Drawable, public sf::Transformable
{
public:
	Level();
	virtual ~Level();

	virtual void Initialise() = 0;
	virtual void InitialiseTiles() = 0;

	virtual void Update(sf::Time elapsedTime, LevelGUI*& LevelGUI) = 0;
	virtual void DeleteResources() = 0;

	void setDirection(Player*& player, Tilemap*& tilemap);
	void updateTile(Tiles*& tiles,Tilemap*& tilemap, sf::Vector2i pos);
	void setCompleted(bool completed) { m_completed = completed; }
	bool getCompleted() { return m_completed; }

	void hitButton(Player*& player, Tilemap*& tilemap, int thisButton, sf::Vector2i bridgePos);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool m_completed;

	bool m_leavingButton;
	bool m_OnDouble;
	sf::Time m_doublewait;

protected:
	enum pdirection {
		pNONE,
		pUP,
		pDOWN,
		pLEFT,
		pRIGHT
	};

	enum ldirection {
		lNONE,
		lDOWN,
		lLEFT,
		lRIGHT,
		lUP
	};

	bool onButton;
	bool m_onStar;

};
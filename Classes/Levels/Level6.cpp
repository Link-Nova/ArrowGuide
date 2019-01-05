#include "Level6.h"

Level6::Level6(sf::RenderWindow& win)
	:m_pPlayer(NULL)
	, m_pTilemap(NULL)
	, m_pTileLeft(NULL)
	, m_pTileRight(NULL)
	, m_pTileUp(NULL)
	, m_pTileDown(NULL)
	, playerPos(0, 0)
	, m_window(win)
	, m_completeTime(sf::seconds(0))
{

}

Level6::~Level6()
{
	DeleteResources();
}

void Level6::Initialise()
{
	//down - 1
	//left - 2
	//right - 3
	//up - 4

	running = false;
	setCompleted(false);

	m_pLevelText = NULL;

	
	bridge1Pos = sf::Vector2i(32 + (64 * 6), 32 + (64 * 5));
	bridge2Pos = sf::Vector2i(32 + (64 * 9), 32 + (64 * 3));

	m_pPlayer = new Player();
	m_pPlayer->Initialise("Media/Images/player.png", pRIGHT, sf::Vector2f(32 + (64 * 3), 32 + (64 * 4)));
	
	InitialiseTiles();

	m_paneltex.loadFromFile("Media/Images/GUIback.png");


	m_panelspr.setPosition(sf::Vector2f(1024, 0));
	m_panelspr.setTexture(m_paneltex);

}

void Level6::InitialiseTiles()
{
	/*const int level[] =
	{
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1, 0, 0, 6, 0, 0,-1,
		-1,-1,-1,-1,-1, 0, 0, 0, 0, 0,-1,
		-1, 0, 0, 0,-1,-1,-1, 9,-1,-1,-1,
		-1, 7, 0, 7,-1, 0, 0, 0, 0, 0,-1,
		-1, 0, 0, 8,11, 1, 0, 0, 5, 0,-1,
		-1, 0, 0, 0,-1, 3, 7, 7, 1, 0,-1,
		-1, 0, 5, 0,-1,-1,-1,-1, 7,-1,-1,
		-1, 0, 0, 0,-1,-1, 0, 8, 0,-1,-1,
		-1, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	};*/

	const int level[] =
	{
		18,13,13,13,13,13,13,13,13,13,13,13,13,13,13,19,
		14,21,21,21,21,21,21,21,21,21,21,21,21,21,21,15,
		14,21,21,21,21,21,21, 0, 0, 6, 0, 0,21,21,21,15,
		14,21,21, 0, 0, 7,21,21,21, 9,21,21,21,21,21,15,
		14,21,21, 7, 8, 0,21, 0, 0, 0, 0, 0,21,21,21,15,
		14,21,21, 0, 0, 7,11, 1, 0, 0, 5, 0,21,21,21,15,
		14,21,21, 0, 7, 0,21, 3, 7, 7, 1, 0,21,21,21,15,
		14,21,21, 0, 5, 0,21,21,21,21, 7,21,21,21,21,15,
		14,21,21, 0, 0, 0,21,21, 0, 8, 0,21,21,21,21,15,
		14,21,21, 0, 0, 0, 0, 0, 0, 0, 0, 0,21,21,21,15,
		14,21,21,21,21,21,21,21,21,21,21,21,21,21,21,15,
		17,16,16,16,16,16,16,16,16,16,16,16,16,16,16,20,
	};

	m_pTilemap = new Tilemap();
	m_pTilemap->load("Media/Images/tileset.png", sf::Vector2u(64, 64), level, 16, 12);


	m_pTileDown = new Tiles(lDOWN, m_window);
	m_pTileDown->Initialise("Media/Images/tileDown.png", 2, sf::Vector2f(1150, 100));
	m_pTileUp = new Tiles(lUP, m_window);
	m_pTileUp->Initialise("Media/Images/tileUp.png", 5, sf::Vector2f(1150, 250));
	m_pTileLeft = new Tiles(lLEFT, m_window);
	m_pTileLeft->Initialise("Media/Images/tileLeft.png", 3, sf::Vector2f(1150, 400));
	m_pTileRight = new Tiles(lRIGHT, m_window);
	m_pTileRight->Initialise("Media/Images/tileRight.png", 4, sf::Vector2f(1150, 550));
}

void Level6::Update(sf::Time elapsedTime, LevelGUI*& LevelGUI)
{

	bool m_spacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	if (LevelGUI->getPlay() || running)
	{
		m_pPlayer->Update(elapsedTime);
		running = true;
	}

	if (!running)
	{

		if (m_spacePressed && !m_spacePrevPressed && !running)
		{
			m_pPlayer->ChangeDirection();
		}

		//only update one at a time
		if (!m_pTileUp->getSelected() && !m_pTileLeft->getSelected() && !m_pTileRight->getSelected())
			m_pTileDown->Update(elapsedTime);
		if (!m_pTileDown->getSelected() && !m_pTileLeft->getSelected() && !m_pTileRight->getSelected())
			m_pTileUp->Update(elapsedTime);
		if (!m_pTileUp->getSelected() && !m_pTileDown->getSelected() && !m_pTileRight->getSelected())
			m_pTileLeft->Update(elapsedTime);
		if (!m_pTileUp->getSelected() && !m_pTileDown->getSelected() && !m_pTileLeft->getSelected())
			m_pTileRight->Update(elapsedTime);

		//check if tile is being placed
		sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

		updateTile(m_pTileUp, m_pTilemap, mousePos);
		updateTile(m_pTileDown, m_pTilemap, mousePos);
		updateTile(m_pTileLeft, m_pTilemap, mousePos);
		updateTile(m_pTileRight, m_pTilemap, mousePos);

		m_pPlayer->GetPosition(playerPos.x, playerPos.y);

		//reset tiles
		if (LevelGUI->getReset())
		{
			LevelGUI->setReset(false);

			delete m_pTileDown;
			delete m_pTileLeft;
			delete m_pTileRight;
			delete m_pTileUp;
			delete m_pTilemap;


			InitialiseTiles();
		}
	}

	//saving code ayyyyyyyyyy
	setDirection(m_pPlayer, m_pTilemap);

	//flip bridges
	if (onButton)
	{
		hitButton(m_pPlayer, m_pTilemap, 16 * 8 + 9, bridge1Pos);
		hitButton(m_pPlayer, m_pTilemap, 16 * 4 + 4, bridge2Pos);

		hitButton(m_pPlayer, m_pTilemap, 16 * 8 + 9, bridge2Pos);
		hitButton(m_pPlayer, m_pTilemap, 16 * 4 + 4, bridge1Pos);
	}

	//reset
	if (m_pPlayer->getDead() && m_pPlayer->GetDirection() != pNONE)
	{
		m_pLevelText = new LevelText();
		m_pLevelText->Initialise("You Died...", "Media/Fonts/8-Bit Madness.ttf");

		m_pPlayer->SetDirection(pNONE);
	}

	if (m_onStar)
	{
		m_pLevelText = new LevelText();
		m_pLevelText->Initialise("Well Done!", "Media/Fonts/8-Bit Madness.ttf");
		m_onStar = false;

		m_pPlayer->SetDirection(pNONE);
	}

	//back to level select after winning
	if (m_pLevelText && !m_pPlayer->getDead())
	{
		//dont update buttons anymore
		LevelGUI->setLevelDone(true);

		m_completeTime += elapsedTime;

		if (m_completeTime >= sf::seconds(2))
			setCompleted(true);
	}

	if ((!LevelGUI->getPlay() && running))
	{
		DeleteResources();
		Initialise();
	}	

	m_spacePrevPressed = m_spacePressed;

}

void Level6::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	target.draw(m_panelspr, states);

	// draw 
	target.draw(*m_pTilemap, states);
	target.draw(*m_pPlayer, states);
	target.draw(*m_pTileDown, states);
	target.draw(*m_pTileUp, states);
	target.draw(*m_pTileLeft, states);
	target.draw(*m_pTileRight, states);

	if(m_pLevelText)
		target.draw(*m_pLevelText, states);
}

void Level6::DeleteResources()
{
	delete m_pTilemap;
	delete m_pPlayer;
	delete m_pTileDown;
	delete m_pTileUp;
	delete m_pTileLeft;
	delete m_pTileRight;

	if(m_pLevelText)
		delete m_pLevelText;
}
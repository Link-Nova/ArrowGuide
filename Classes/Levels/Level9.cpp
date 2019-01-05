#include "Level9.h"

Level9::Level9(sf::RenderWindow& win)
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

Level9::~Level9()
{
	DeleteResources();
}

void Level9::Initialise()
{
	//down - 1
	//left - 2
	//right - 3
	//up - 4

	running = false;
	setCompleted(false);

	m_pLevelText = NULL;

	m_pPlayer = new Player();
	m_pPlayer->Initialise("Media/Images/player.png", pDOWN, sf::Vector2f(32 + (64 * 2), 32 + (64 * 2)));

	InitialiseTiles();

	m_paneltex.loadFromFile("Media/Images/GUIback.png");


	m_panelspr.setPosition(sf::Vector2f(1024, 0));
	m_panelspr.setTexture(m_paneltex);

	bridge1Pos = sf::Vector2i(32 + (64 * 5), 32 + (64 * 2));
	bridge2Pos = sf::Vector2i(32 + (64 * 7), 32 + (64 * 2));
	bridge3Pos = sf::Vector2i(32 + (64 * 1), 32 + (64 * 4));
	bridge4Pos = sf::Vector2i(32 + (64 * 3), 32 + (64 * 4));
	bridge5Pos = sf::Vector2i(32 + (64 * 4), 32 + (64 * 7));
	bridge6Pos = sf::Vector2i(32 + (64 * 4), 32 + (64 * 9));
	bridge7Pos = sf::Vector2i(32 + (64 * 9), 32 + (64 * 8));

}

void Level9::InitialiseTiles()
{

	const int level[] =
	{
		18,13,13,13,13,13,13,13,13,13,13,13,13,13,13,19,
		14, 0, 0, 0, 0,21, 7,21,21,21,21,21,21,21,21,15,
		14, 0, 7, 8, 3,11,22,11, 7, 7, 7, 7, 2, 6,21,15,
		14, 0, 0, 0, 0,21, 7,21,21,21, 5, 5, 0, 5, 5,15,
		14,10,21, 9,21,21, 0,21,21,21,21, 0, 0, 0, 0,15,
		14, 0, 0, 0,21, 0, 0, 0, 0,21, 0, 0,24, 0, 0,15,
		14, 0, 0, 0,21, 0, 7, 0, 0,21, 0, 7, 4, 7, 2,15,
		14, 5, 7,25,12, 0, 7, 8, 0,21, 8, 7, 5, 7,21,15,
		14, 0, 0, 0,21, 0, 7, 0, 0,12, 0, 0, 0, 0,21,15,
		14, 0, 0, 0,11, 0, 4, 0, 0,21, 0, 0, 0,21,21,15,
		14, 0, 0, 0,21, 0, 0, 0, 0,21,21,21,21,21,21,15,
		17,16,16,16,16,16,16,16,16,16,16,16,16,16,16,20,
	};

	m_pTilemap = new Tilemap();
	m_pTilemap->load("Media/Images/tileset.png", sf::Vector2u(64, 64), level, 16, 12);

	m_pTileDown = new Tiles(lDOWN, m_window);
	m_pTileDown->Initialise("Media/Images/tileDown.png", 4, sf::Vector2f(1150, 100));
	m_pTileUp = new Tiles(lUP, m_window);
	m_pTileUp->Initialise("Media/Images/tileUp.png", 4, sf::Vector2f(1150, 250));
	m_pTileLeft = new Tiles(lLEFT, m_window);
	m_pTileLeft->Initialise("Media/Images/tileLeft.png", 4, sf::Vector2f(1150, 400));
	m_pTileRight = new Tiles(lRIGHT, m_window);
	m_pTileRight->Initialise("Media/Images/tileRight.png", 7, sf::Vector2f(1150, 550));
}

void Level9::Update(sf::Time elapsedTime, LevelGUI*& LevelGUI)
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

	if (onButton)
	{
		hitButton(m_pPlayer, m_pTilemap, 16 * 2 + 3, bridge1Pos);
		hitButton(m_pPlayer, m_pTilemap, 16 * 2 + 3, bridge2Pos);
		hitButton(m_pPlayer, m_pTilemap, 16 * 2 + 3, bridge3Pos);
		hitButton(m_pPlayer, m_pTilemap, 16 * 2 + 3, bridge4Pos);
		hitButton(m_pPlayer, m_pTilemap, 16 * 2 + 3, bridge5Pos);
		hitButton(m_pPlayer, m_pTilemap, 16 * 2 + 3, bridge6Pos);
		hitButton(m_pPlayer, m_pTilemap, 16 * 2 + 3, bridge7Pos);

		hitButton(m_pPlayer, m_pTilemap, 16 * 7 + 7, bridge1Pos);
		hitButton(m_pPlayer, m_pTilemap, 16 * 7 + 7, bridge2Pos);
		hitButton(m_pPlayer, m_pTilemap, 16 * 7 + 7, bridge3Pos);
		hitButton(m_pPlayer, m_pTilemap, 16 * 7 + 7, bridge4Pos);
		hitButton(m_pPlayer, m_pTilemap, 16 * 7 + 7, bridge5Pos);
		hitButton(m_pPlayer, m_pTilemap, 16 * 7 + 7, bridge6Pos);
		hitButton(m_pPlayer, m_pTilemap, 16 * 7 + 7, bridge7Pos);

		hitButton(m_pPlayer, m_pTilemap, 16 * 7 + 10, bridge1Pos);
		hitButton(m_pPlayer, m_pTilemap, 16 * 7 + 10, bridge2Pos);
		hitButton(m_pPlayer, m_pTilemap, 16 * 7 + 10, bridge3Pos);
		hitButton(m_pPlayer, m_pTilemap, 16 * 7 + 10, bridge4Pos);
		hitButton(m_pPlayer, m_pTilemap, 16 * 7 + 10, bridge5Pos);
		hitButton(m_pPlayer, m_pTilemap, 16 * 7 + 10, bridge6Pos);
		hitButton(m_pPlayer, m_pTilemap, 16 * 7 + 10, bridge7Pos);
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

void Level9::draw(sf::RenderTarget& target, sf::RenderStates states) const
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

	if (m_pLevelText)
		target.draw(*m_pLevelText, states);
}

void Level9::DeleteResources()
{
	delete m_pTilemap;
	delete m_pPlayer;
	delete m_pTileDown;
	delete m_pTileUp;
	delete m_pTileLeft;
	delete m_pTileRight;

	if (m_pLevelText)
		delete m_pLevelText;
}
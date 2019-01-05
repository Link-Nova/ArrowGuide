#include "Application.h"

Application::Application(int windowWidth, int windowHeight)
	:m_window(sf::VideoMode(windowWidth, windowHeight), "Puzzle Game", sf::Style::Default)
	,m_initialised(true)
	,m_screenWidth(windowWidth)
	,m_screenHeight(windowHeight)
	,m_desiredUpdateTime(sf::seconds(1.f / 60.f))
	,currentLevel(1)
	,maxLevel(9)
	,m_appState(SELECT)
{
	m_pLevelSel = new LevelSelect(m_window, maxLevel);
	m_pLevelSel->Initialise();

}

Application::~Application()
{

}

void Application::update(sf::Time elapsedTime)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		sf::Vector2u windowSize = m_window.getSize();
		sf::Texture texture;
		texture.create(windowSize.x, windowSize.y);
		texture.update(m_window);
		sf::Image screenshot = texture.copyToImage();
		screenshot.saveToFile("screenshot.png");
	}

	bool validEventPoll = m_window.pollEvent(m_event);

	if ((m_event.type == sf::Event::Closed) && validEventPoll)
		m_window.close();

	if (m_appState == SELECT)
	{
		int selection;

		selection = m_pLevelSel->Update(elapsedTime);
		currentLevel = selection;

		if (selection > 0)
		{
			delete m_pLevelSel;

			m_pLevelGUI = new LevelGUI(m_window);
			m_pLevelGUI->Initialise();

			if (selection == 1)
			{
				m_pLevel1 = new Level1(m_window);
				m_pLevel1->Initialise();
			}
			else if (selection == 2)
			{
				m_pLevel2 = new Level2(m_window);
				m_pLevel2->Initialise();
			}
			else if (selection == 3)
			{
				m_pLevel3 = new Level3(m_window);
				m_pLevel3->Initialise();
			}
			else if (selection == 4)
			{
				m_pLevel4 = new Level4(m_window);
				m_pLevel4->Initialise();
			}
			else if (selection == 5)
			{
				m_pLevel5 = new Level5(m_window);
				m_pLevel5->Initialise();
			}
			else if (selection == 6)
			{
				m_pLevel6 = new Level6(m_window);
				m_pLevel6->Initialise();
			}
			else if (selection == 7)
			{
				m_pLevel7 = new Level7(m_window);
				m_pLevel7->Initialise();
			}
			else if (selection == 8)
			{
				m_pLevel8 = new Level8(m_window);
				m_pLevel8->Initialise();
			}
			else if (selection == 9)
			{
				m_pLevel9 = new Level9(m_window);
				m_pLevel9->Initialise();
			}

			m_appState = INGAME;
		}
	}
	else if (m_appState == INGAME)
	{

		m_pLevelGUI->Update(elapsedTime);

		if (currentLevel == 1)
		{
			m_pLevel1->Update(elapsedTime, m_pLevelGUI);
			if (m_pLevel1->getCompleted())
			{
				delete m_pLevel1;

				if(maxLevel == 1)
					maxLevel++;

				m_pLevelSel = new LevelSelect(m_window, maxLevel);
				m_pLevelSel->Initialise();
				
				m_appState = SELECT;
			}
		}
		else if (currentLevel == 2)
		{
			m_pLevel2->Update(elapsedTime, m_pLevelGUI);
			if (m_pLevel2->getCompleted())
			{
				delete m_pLevel2;
				
				if (maxLevel == 2)
					maxLevel++;

				m_pLevelSel = new LevelSelect(m_window, maxLevel);
				m_pLevelSel->Initialise();

				m_appState = SELECT;
			}
		}
		else if (currentLevel == 3)
		{
			m_pLevel3->Update(elapsedTime, m_pLevelGUI);
			if (m_pLevel3->getCompleted())
			{
				delete m_pLevel3;
				
				if (maxLevel == 3)
					maxLevel++;

				m_pLevelSel = new LevelSelect(m_window, maxLevel);
				m_pLevelSel->Initialise();

				m_appState = SELECT;
			}
		}
		else if (currentLevel == 4)
		{
			m_pLevel4->Update(elapsedTime, m_pLevelGUI);
			if (m_pLevel4->getCompleted())
			{
				delete m_pLevel4;
				
				if (maxLevel == 4)
					maxLevel++;

				m_pLevelSel = new LevelSelect(m_window, maxLevel);
				m_pLevelSel->Initialise();

				m_appState = SELECT;
			}
		}
		else if (currentLevel == 5)
		{
			m_pLevel5->Update(elapsedTime, m_pLevelGUI);
			if (m_pLevel5->getCompleted())
			{
				delete m_pLevel5;
				
				if (maxLevel == 5)
					maxLevel++;

				m_pLevelSel = new LevelSelect(m_window, maxLevel);
				m_pLevelSel->Initialise();

				m_appState = SELECT;
			}
		}
		else if (currentLevel == 6)
		{
			m_pLevel6->Update(elapsedTime, m_pLevelGUI);
			if (m_pLevel6->getCompleted())
			{
				delete m_pLevel6;
				
				if (maxLevel == 6)
					maxLevel++;

				m_pLevelSel = new LevelSelect(m_window, maxLevel);
				m_pLevelSel->Initialise();

				m_appState = SELECT;
			}
		}
		else if (currentLevel == 7)
		{
			m_pLevel7->Update(elapsedTime, m_pLevelGUI);
			if (m_pLevel7->getCompleted())
			{
				delete m_pLevel7;

				if (maxLevel == 7)
					maxLevel++;

				m_pLevelSel = new LevelSelect(m_window, maxLevel);
				m_pLevelSel->Initialise();

				m_appState = SELECT;
			}
		}
		else if (currentLevel == 8)
		{
			m_pLevel8->Update(elapsedTime, m_pLevelGUI);
			if (m_pLevel8->getCompleted())
			{
				delete m_pLevel8;

				if (maxLevel == 8)
					maxLevel++;

				m_pLevelSel = new LevelSelect(m_window, maxLevel);
				m_pLevelSel->Initialise();

				m_appState = SELECT;
			}
		}
		else if (currentLevel == 9)
		{
			m_pLevel9->Update(elapsedTime, m_pLevelGUI);
			if (m_pLevel9->getCompleted())
			{
				delete m_pLevel9;

				if (maxLevel == 9)
					maxLevel++;

				m_pLevelSel = new LevelSelect(m_window, maxLevel);
				m_pLevelSel->Initialise();

				m_appState = SELECT;
			}
		}
		//return to main menu
		if (m_pLevelGUI->getBack())
		{
			m_appState = SELECT;

			m_pLevelSel = new LevelSelect(m_window, maxLevel);
			m_pLevelSel->Initialise();

			if (currentLevel == 1)
				delete m_pLevel1;
			else if (currentLevel == 2)
				delete m_pLevel2;
			else if (currentLevel == 3)
				delete m_pLevel3;
			else if (currentLevel == 4)
				delete m_pLevel4;
			else if (currentLevel == 5)
				delete m_pLevel5;
			else if (currentLevel == 6)
				delete m_pLevel6;
			else if (currentLevel == 7)
				delete m_pLevel7;
			else if (currentLevel == 8)
				delete m_pLevel8;
			else if (currentLevel == 9)
				delete m_pLevel9;

			delete m_pLevelGUI;
		}

	}
}

void Application::render()
{
	m_window.clear();
	if (m_appState == SELECT)
	{
		m_window.draw(*m_pLevelSel);
	}
	else if (m_appState == INGAME)
	{

		if (currentLevel == 1)
			m_window.draw(*m_pLevel1);
		else if (currentLevel == 2)
			m_window.draw(*m_pLevel2);
		else if (currentLevel == 3)
			m_window.draw(*m_pLevel3);
		else if (currentLevel == 4)
			m_window.draw(*m_pLevel4);
		else if (currentLevel == 5)
			m_window.draw(*m_pLevel5);
		else if (currentLevel == 6)
			m_window.draw(*m_pLevel6);
		else if (currentLevel == 7)
			m_window.draw(*m_pLevel7);
		else if (currentLevel == 8)
			m_window.draw(*m_pLevel8);
		else if (currentLevel == 9)
			m_window.draw(*m_pLevel9);

		m_window.draw(*m_pLevelGUI);
	}

	m_window.display();

}

void Application::run()
{
	if (!m_initialised)
		return;

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (m_window.isOpen())
	{

		//Gets elapsed time since last loop
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		//will only update every 60th of a second - 60fps
		while (timeSinceLastUpdate > m_desiredUpdateTime)
		{
			//update states
			update(m_desiredUpdateTime);
			timeSinceLastUpdate -= m_desiredUpdateTime;
		}
		//render results to screen
		render();
	}
}
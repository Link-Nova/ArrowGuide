#pragma once
#include <SFML/Graphics.hpp>

#include "LevelSelect.h"
#include "LevelGUI.h"

#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"
#include "Level6.h"
#include "Level7.h"
#include "Level8.h"
#include "Level9.h"

class Application : public sf::NonCopyable
{
public:
	Application(int windowWidth, int windowHeight);
	~Application();

	void run();
private:

	enum Appstate {
		SELECT,
		INGAME,
		EXITING
	};

	Appstate m_appState;

	void update(sf::Time elapsedTime);
	void render();
	bool m_initialised;

	sf::RenderWindow m_window;

	std::size_t m_screenWidth;
	std::size_t m_screenHeight;

	sf::Event m_event;
	sf::Time m_desiredUpdateTime;

	LevelSelect* m_pLevelSel;
	LevelGUI* m_pLevelGUI;

	Level* m_pLevel1;
	Level* m_pLevel2;
	Level* m_pLevel3;
	Level* m_pLevel4;
	Level* m_pLevel5;
	Level* m_pLevel6;
	Level* m_pLevel7;
	Level* m_pLevel8;
	Level* m_pLevel9;

	int currentLevel;
	int maxLevel;
};
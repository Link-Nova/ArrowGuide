#include "Level.h"
#include <iostream>
Level::Level()
	:m_completed(false)
	,m_onStar(false)
	,onButton(false)
	,m_leavingButton(false)
	,m_OnDouble(false)
	,m_doublewait(sf::seconds(0))
{

}

Level::~Level()
{

}

void Level::setDirection(Player*& player, Tilemap*& tilemap)
{
	int num;

	sf::Vector2i playerPos;
	sf::Vector2i playerSize;

	player->GetPosition(playerPos.x, playerPos.y);
	player->GetSize(playerSize.x, playerSize.y);

	if (m_OnDouble)
	{
		m_doublewait += sf::seconds(0.0065);
		num = 0;
	}
	else if (player->GetDirection() == pDOWN || player->GetDirection() == pLEFT || player->GetDirection() == pNONE)
		num = tilemap->getTileAtPosition(playerPos.x + playerSize.x / 2, playerPos.y - playerSize.y / 2);
	else if (player->GetDirection() == pUP || player->GetDirection() == pRIGHT)
		num = tilemap->getTileAtPosition(playerPos.x - playerSize.x / 2, playerPos.y + playerSize.y / 2);

	if (m_doublewait >= sf::seconds(0.1))
	{
		m_OnDouble = false;
		m_doublewait = sf::seconds(0);
	}

	//DOWN = 2
	//UP = 1
	//LEFT = 3
	//RIGHT = 4
	if (num == 1)
	{
		player->SetDirection(pDOWN);
		tilemap->replaceTileNumber(0, playerPos.x - playerSize.x / 2, playerPos.y + playerSize.y / 2);
	}
	else if (num == 2)
	{
		player->SetDirection(pLEFT);
		tilemap->replaceTileNumber(0, playerPos.x - playerSize.x / 2, playerPos.y + playerSize.y / 2);
	}
	else if (num == 3)
	{
		player->SetDirection(pRIGHT);
		tilemap->replaceTileNumber(0, playerPos.x + playerSize.x / 2, playerPos.y - playerSize.y / 2);
	}
	else if (num == 4)
	{
		player->SetDirection(pUP);
		tilemap->replaceTileNumber(0, playerPos.x + playerSize.x / 2, playerPos.y - playerSize.y / 2);
	}
	else if (num == 6 && player->GetDirection() != pNONE)
		m_onStar = true;
	else if (num == 5 || num == -1 || num == 9 || num == 11 || num >=13 && num <= 21)
		player->Dead();
	else if (num == 8 && !m_leavingButton)
	{
		onButton = true;
	}
	else if (num == 22)
	{
		player->SetDirection(pDOWN);
		tilemap->replaceTileNumber(1, playerPos.x - playerSize.x / 2, playerPos.y + playerSize.y / 2);
		m_OnDouble = true;
	}
	else if (num == 23)
	{
		player->SetDirection(pLEFT);
		tilemap->replaceTileNumber(2, playerPos.x - playerSize.x / 2, playerPos.y + playerSize.y / 2);
		m_OnDouble = true;
	}
	else if (num == 24)
	{
		player->SetDirection(pRIGHT);
		tilemap->replaceTileNumber(3, playerPos.x + playerSize.x / 2, playerPos.y - playerSize.y / 2);
		m_OnDouble = true;
	}
	else if (num == 25)
	{
		player->SetDirection(pUP);
		tilemap->replaceTileNumber(4, playerPos.x + playerSize.x / 2, playerPos.y - playerSize.y / 2);
		m_OnDouble = true;
	}

	//only flip bridge once
	if (num != 8)
	{
		m_leavingButton = false;
	}

	std::cout << num << std::endl;
}

void Level::hitButton(Player*& player, Tilemap*& tilemap, int thisButton, sf::Vector2i bridgePos)
{
	int num;

	sf::Vector2i playerPos;
	sf::Vector2i playerSize;

	player->GetPosition(playerPos.x, playerPos.y);
	player->GetSize(playerSize.x, playerSize.y);

	if (player->GetDirection() == pDOWN || player->GetDirection() == pLEFT || player->GetDirection() == pNONE)
		num = tilemap->getTileNumber(playerPos.x + playerSize.x / 2, playerPos.y - playerSize.y / 2);

	if (player->GetDirection() == pUP || player->GetDirection() == pRIGHT)
		num = tilemap->getTileNumber(playerPos.x - playerSize.x / 2, playerPos.y + playerSize.y / 2);

	if (num == thisButton)
	{
		int tileNumber;

		if (player->GetDirection() == pDOWN || player->GetDirection() == pLEFT)
			tileNumber = tilemap->getTileAtPosition(bridgePos.x, bridgePos.y);

		if (player->GetDirection() == pUP || player->GetDirection() == pRIGHT)
			tileNumber = tilemap->getTileAtPosition(bridgePos.x, bridgePos.y);

		if(tileNumber == 9)
			tilemap->replaceTileNumber(10, bridgePos.x, bridgePos.y);
		else if(tileNumber == 10)
			tilemap->replaceTileNumber(9, bridgePos.x, bridgePos.y);
		else if(tileNumber == 11)
			tilemap->replaceTileNumber(12, bridgePos.x, bridgePos.y);
		else if(tileNumber == 12)
			tilemap->replaceTileNumber(11, bridgePos.x, bridgePos.y);

		onButton = false;
		m_leavingButton = true;
	}

}

void Level::updateTile(Tiles*& tiles, Tilemap*& tilemap, sf::Vector2i pos)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && tiles->getSelected())
	{
		int number = tilemap->getTileAtPosition(pos.x, pos.y);
		if (number == 0)
		{
			tilemap->replaceTileNumber(tiles->getID(), pos.x, pos.y);
			tiles->isPlaced();
		}
	}
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}
#pragma once
#include <OgreTrays.h>
#include "Player.h"

class GameInfoOverlay
{
public:
	GameInfoOverlay(OgreBites::TrayManager* trayM, double width);

	void updateGameInfo();

	void setPlayer(Player* p);

private: 
	OgreBites::TrayManager* mTrayMgr = nullptr;
	Player* _player = nullptr;
	OgreBites::Label* _infoLabel = nullptr;
	OgreBites::TextBox* _infoText = nullptr;

	std::string _text;
};


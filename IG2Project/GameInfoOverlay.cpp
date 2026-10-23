#include "GameInfoOverlay.h"

GameInfoOverlay::GameInfoOverlay(OgreBites::TrayManager* trayM, double width) : mTrayMgr(trayM) {
	_infoLabel = mTrayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT, "GameInfoLabel", "Stage: 1", width);
	_infoText = mTrayMgr->createTextBox(OgreBites::TL_BOTTOMRIGHT, "GameInfoTextBox", "Your info", width, width/1.5f);
}

void GameInfoOverlay::updateGameInfo() {
	std::ostringstream ss;
	ss << "HP: " << _player->getLife() << "\nPoints: " << _player->getPoints() << '\n';
	_text = ss.str();

	_infoText->setText(_text);
}

void GameInfoOverlay::setPlayer(Player* p) {
	_player = p;
}
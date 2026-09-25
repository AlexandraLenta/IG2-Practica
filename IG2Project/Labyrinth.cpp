#include "Labyrinth.h"
#include <fstream>
#include "Player.h"
#include "WallBlock.h"
#include "EmptyBlock.h"

Labyrinth::Labyrinth() : IG2Object() {
}

Labyrinth::Labyrinth(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, string fileName) : IG2Object(initPos, node, sceneMng) {	
	createLabyrinth(fileName);
}

Labyrinth::~Labyrinth() {
	for (auto a : _blocks)
		for (auto* b : a) 
			delete b;

	_blocks.clear();
}

void Labyrinth::createLabyrinth(string fileName) {
	ifstream file;
	file.open(fileName);

	if (!file) {
		throw "File not found" + fileName;
	}


	int iRow = 0, iCol = 0;
	char cell;

	file >> _numRows >> _numCols;

	_blocks = std::vector<std::vector<Block*>>(_numRows, std::vector<Block*>(_numCols));

	Vector3 absoluteStartingPos = { -(float)(_numRows*BLOCK_SIZE)/2.f, 0, -(float)(_numCols*BLOCK_SIZE)/2.f };
	Vector3 initialPos = { getPosition().x + absoluteStartingPos.x, 0, getPosition().z + absoluteStartingPos.z };
	Vector3 nextPos = initialPos;

	while (iRow < _numRows) {
		iCol = 0;
		while (iCol < _numCols) {
			file >> cell;

			Block* block = nullptr;

			if (cell == WALL_BLOCK) {
				block = createBlock(nextPos, WALL);
			}
			else if (cell == EMPTY_BLOCK) {
				block = createBlock(nextPos, EMPTY);
			}

			_blocks[iRow][iCol] = block;

			iCol++;
			nextPos.x += BLOCK_SIZE;
		}
		iRow++;
		nextPos.z += BLOCK_SIZE;
		nextPos.x = initialPos.x;
	}

	file.close();
}

Block* Labyrinth::createBlock(Vector3 pos, BlockType type) {
	SceneNode* block = createChildSceneNode();
	Block* blockObj = nullptr;

	switch (type) {
	case WALL:
		blockObj = new WallBlock(pos, block, mSM, "cube.mesh");
		break;
	case EMPTY:
		blockObj = new EmptyBlock(pos, block, mSM);
		break;
	}

	blockObj->setScale(getCubeResizeScale(blockObj));

	return blockObj;
}

Vector3 Labyrinth::getCubeResizeScale(IG2Object* cube) {
	auto x = Labyrinth::BLOCK_SIZE / (float)cube->calculateBoxSize().x;
	auto y = Labyrinth::BLOCK_SIZE / (float)cube->calculateBoxSize().y;
	auto z = Labyrinth::BLOCK_SIZE / (float)cube->calculateBoxSize().z;

	return { x, y, z };
}

void Labyrinth::movePlayer(Player* player, Real time) {
	Block* charBlock, * inFrontBlock;

	// Get the block where the character is placed, and the next one
	charBlock = this->getBlock(player->getPosition());
	inFrontBlock = this->getBlock((player->getGridOrientation() * BLOCK_SIZE) + player->getPosition());

	// Character does not change its direction -> step forward!
	if (!player->isDirectionModified())
		stepForward(player, time);

	// New direction
	else {
		// Check the block in front of the character for the new direction
		Block* newDirBlock = this->getBlock(player->getPosition() + (player->getNextDirVector() * BLOCK_SIZE));
		
		// New position of the character after moving... (for checking if the center of the block is reached)
		Vector3 charNewPos = player->getPosition() + (player->getGridOrientation() * player->getSpeed() * time);
		
		Vector3 difference = Vector3(charNewPos.x - charBlock->getPosition().x, 0, charNewPos.z - charBlock->getPosition().z);
		// Check if the character can rotate for a new VALID direction
		if (newDirBlock->canPassThrough() && blockCenterReached(difference, player->getGridOrientation()))
			player->rotateToNewDirection();
		// 180 turn?
		else if (player->is180Turn())
			player->rotateToNewDirection();
		// Rotation cannot be performed... check if character can step forward
		else
			stepForward(player, time);
	}
}

Block* Labyrinth::getBlock(Vector3 position) {
	Vector3 posInLabyrinth = getPositionRelativeToLabyrinth(position);

	int row, col;

	row = static_cast<int>(posInLabyrinth.z / BLOCK_SIZE);
	col = static_cast<int>(posInLabyrinth.x / BLOCK_SIZE);

	if (row < 0 || row >= _numRows ||
		col < 0 || col >= _numCols) {
		return nullptr;
	}

	return _blocks[row][col];
}

void Labyrinth::stepForward(Player* player, Real time) {
	player->movePlayer(time);
}

bool Labyrinth::blockCenterReached(Vector3 difference, Vector3 direction) {
	return true;
}

Vector3 Labyrinth::getPositionRelativeToLabyrinth(Vector3 pos) {
	Vector3 relative = pos - getPosition();

	relative.x += _numCols * BLOCK_SIZE / 2.f;
	relative.z += _numRows * BLOCK_SIZE / 2.f;

	return relative;
}
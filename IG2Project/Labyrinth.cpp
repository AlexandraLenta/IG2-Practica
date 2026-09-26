#include "Labyrinth.h"
#include "Player.h"
#include "WallBlock.h"
#include "EmptyBlock.h"
#include "IG2Project.h"

Labyrinth::Labyrinth() : IG2Object() {
}

Labyrinth::Labyrinth(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, std::istream& input, IG2Project* ig2) : IG2Object(initPos, node, sceneMng) {	
	createLabyrinth(input, ig2);
}

Labyrinth::~Labyrinth() {
	for (auto a : _blocks)
		for (auto* b : a) 
			delete b;

	_blocks.clear();
}

void Labyrinth::createLabyrinth(std::istream& input, IG2Project* ig2) {
	int iRow = 0, iCol = 0;
	char cell;

	input >> _numRows >> _numCols;

	_blocks = std::vector<std::vector<Block*>>(_numRows, std::vector<Block*>(_numCols));

	Vector3 absoluteStartingPos = { -(float)(_numRows*BLOCK_SIZE)/2.f, 0, -(float)(_numCols*BLOCK_SIZE)/2.f };
	_labyrinthOrigin = { getPosition().x + absoluteStartingPos.x, 0, getPosition().z + absoluteStartingPos.z };
	Vector3 nextPos = _labyrinthOrigin;

	while (iRow < _numRows) {
		iCol = 0;
		while (iCol < _numCols) {
			input >> cell;

			Block* block = nullptr;

			if (cell == WALL_BLOCK) {
				block = createBlock(nextPos, WALL);
			}
			else if (cell == EMPTY_BLOCK) {
				block = createBlock(nextPos, EMPTY);
			}
			else if (cell == HERO) {
				block = createBlock(nextPos, EMPTY); // donde esta el jugador no puede haber ningun bloque

				Vector3 playerPos = _labyrinthOrigin;
				playerPos.x += iCol * BLOCK_SIZE;
				playerPos.z += iRow * BLOCK_SIZE;

				ig2->createPlayer(playerPos);
			}

			_blocks[iRow][iCol] = block;

			iCol++;
			nextPos.x += BLOCK_SIZE;
		}
		iRow++;
		nextPos.z += BLOCK_SIZE;
		nextPos.x = _labyrinthOrigin.x;
	}
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
	// Get the block where the character is placed, and the next one
	Block* currentBlock = getBlock(player->getPosition());

	if (currentBlock == nullptr)
		return;

	Vector3 currentDir = player->getGridOrientation();

	Block* inFrontBlock = getBlock(player->getPosition() + currentDir * BLOCK_SIZE);

	// Player trying to change position
	if (player->isDirectionModified()) {
		Block* nextBlock = getBlock(player->getPosition() + player->getNextDirVector() * BLOCK_SIZE);

		Vector3 movement = currentDir * player->getSpeed() * time;

		Vector3 newPos = movement + player->getPosition();

		Vector3 difference = newPos - currentBlock->getPosition();

		// if we've reached the center, see if new direction is valid
		if (blockCenterReached(difference, currentDir)) {
			if (nextBlock != nullptr && nextBlock->canPassThrough()) {
				player->setPosition(currentBlock->getPosition());
				player->rotateToNewDirection();
				return;
			}

			if (player->is180Turn()) {
				std::cout << "180 turn\n";
				player->rotateToNewDirection();
				return;
			}
		}
		//player->movePlayer(time);
	}

	else if (inFrontBlock != nullptr && inFrontBlock->canPassThrough()) {
		player->movePlayer(time);
	}
}

Block* Labyrinth::getBlock(Vector3 position) {
	Vector3 posInLabyrinth = getPositionRelativeToLabyrinth(position);

	//std::cout << posInLabyrinth << '\n';

	int col = static_cast<int>(
		std::round(posInLabyrinth.x / BLOCK_SIZE)
		);

	int row = static_cast<int>(
		std::round(posInLabyrinth.z / BLOCK_SIZE)
		);

	if (row < 0 || row >= _numRows ||
		col < 0 || col >= _numCols) {
		return nullptr;
	}

	//std::cout << row << ' ' << col << '\n';

	return _blocks[row][col];
}

bool Labyrinth::blockCenterReached(Vector3 difference, Vector3 direction) {
	const Real tolerance = 0.1f; // floating point value tolerance

	if (direction.x > 0)
		return difference.x >= -tolerance;

	if (direction.x < 0)
		return difference.x <= tolerance;

	if (direction.z > 0)
		return difference.z >= -tolerance;

	if (direction.z < 0)
		return difference.z <= tolerance;

	return false;
}

Vector3 Labyrinth::getPositionRelativeToLabyrinth(Vector3 pos) {
	Vector3 relative = pos - _labyrinthOrigin;

	relative.x += _numCols * BLOCK_SIZE / 2.f;
	relative.z += _numRows * BLOCK_SIZE / 2.f;

	return relative;
}
#include "Labyrinth.h"
#include "WallBlock.h"
#include "EmptyBlock.h"
#include "IG2Project.h"
#include "InvisibleBlock.h"
#include "BreakableBlock.h"
#include "FakeBlock.h"
#include "SpecialVillain.h"
#include "SimpleVillain.h"

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
			else if (cell == INVISIBLE_BLOCK) {
				block = createBlock(nextPos, INVISIBLE);
			}
			else if (cell == FAKE_BLOCK) {
				block = createBlock(nextPos, FAKE);
			}
			else if (cell == BREAKABLE_BLOCK) {
				block = createBlock(nextPos, BREAKABLE);
			}
			else if (cell == HERO) {
				block = createBlock(nextPos, EMPTY); // donde esta el jugador solo puede haber un bloque vacio

				Vector3 playerPos = _labyrinthOrigin;
				playerPos.x += iCol * BLOCK_SIZE;
				playerPos.z += iRow * BLOCK_SIZE;

				_characters.push_back(ig2->createPlayer(playerPos));
			}
			else if (cell == VILLAIN_NORMAL) {
				block = createBlock(nextPos, EMPTY); // donde esta el jugador solo puede haber un bloque vacio

				Vector3 villainPos = _labyrinthOrigin;
				villainPos.x += iCol * BLOCK_SIZE;
				villainPos.z += iRow * BLOCK_SIZE;

				_characters.push_back(new SimpleVillain(villainPos, mSM->getRootSceneNode()->createChildSceneNode("villain"), mSM));
			}
			else if (cell == VILLAIN_SPECIAL) {
				block = createBlock(nextPos, EMPTY); // donde esta el jugador solo puede haber un bloque vacio

				Vector3 villainPos = _labyrinthOrigin;
				villainPos.x += iCol * BLOCK_SIZE;
				villainPos.z += iRow * BLOCK_SIZE;

				_characters.push_back(new SpecialVillain(villainPos, mSM->getRootSceneNode()->createChildSceneNode("villain"), mSM));
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
		blockObj = new WallBlock(pos, block, mSM);
		break;
	case EMPTY:
		blockObj = new EmptyBlock(pos, block, mSM);
		break;
	case INVISIBLE:
		blockObj = new InvisibleBlock(pos, block, mSM);
		break;
	case FAKE:
		blockObj = new FakeBlock(pos, block, mSM);
		break;
	case BREAKABLE:
		blockObj = new BreakableBlock(pos, block, mSM);
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

void Labyrinth::moveCharacter(Character* character, Real time) {
	// Get the block where the character is placed
	Block* currentBlock = getBlock(character->getPosition());

	if (currentBlock == nullptr)
		return;

	Vector3 currentDir = character->getGridOrientation();

	Block* inFrontBlock = getBlock(character->getPosition() + currentDir * BLOCK_SIZE);

	Vector3 newPos = currentDir * character->getSpeed() * time + character->getPosition();

	Vector3 difference = newPos - currentBlock->getPosition();

	// Player trying to change position
	if (character->isDirectionModified()) {
		Block* nextBlock = getBlock(character->getPosition() + character->getNextDirVector() * BLOCK_SIZE);

		// if we've reached the center, see if new direction is valid
		if (blockCenterReached(difference, currentDir)) {
			if (nextBlock != nullptr && nextBlock->canPassThrough()) {
				character->rotateToNewDirection();
				return;
			}

			if (character->is180Turn()) {
				character->rotateToNewDirection();
				return;
			}
		}
	}

	if (inFrontBlock != nullptr && inFrontBlock->canPassThrough()) {
		character->moveCharacter(time);
	}
	else if (inFrontBlock != nullptr) {
		if (!blockCenterReached(difference, currentDir))
			character->moveCharacter(time);
	}
}

Block* Labyrinth::getBlock(Vector3 position) {
	Vector3 relative = position - _labyrinthOrigin;

	int col = static_cast<int>(
		std::round(relative.x / BLOCK_SIZE)
		);

	int row = static_cast<int>(
		std::round(relative.z / BLOCK_SIZE)
		);

	if (row < 0 || row >= _numRows ||
		col < 0 || col >= _numCols) {
		return nullptr;
	}

	//std::cout << row << ' ' << col << '\n';

	return _blocks[row][col];
}

bool Labyrinth::blockCenterReached(Vector3 difference, Vector3 direction) {
	const Real tolerance = 0.1f;

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

void Labyrinth::updateLabyrinth(Real time) {
	for (auto rows : _blocks) {
		for (auto* block : rows) {
			block->update(time);
		}
	}

	for (auto* ch : _characters) {
		ch->update(time);
		moveCharacter(ch, time);
	}
}
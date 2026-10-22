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

Character* Labyrinth::getPlayer() const {
	return _player;
}

void Labyrinth::createLabyrinth(std::istream& input, IG2Project* ig2) {
	int iRow = 0, iCol = 0;
	char cell;

	input >> _numRows >> _numCols;

	_blocks = std::vector<std::vector<Block*>>(_numRows, std::vector<Block*>(_numCols));

	Vector3 absoluteStartingPos = { -(float)(_numRows*BLOCK_SIZE)/2.f, 0, -(float)(_numCols*BLOCK_SIZE)/2.f };
	_labyrinthOrigin = getPosition() + absoluteStartingPos;
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

				_player = ig2->createPlayer(playerPos);
				_characters.push_back(_player);
			}
			else if (cell == VILLAIN_NORMAL) {
				block = createBlock(nextPos, EMPTY); // donde esta el jugador solo puede haber un bloque vacio

				Vector3 villainPos = _labyrinthOrigin;
				villainPos.x += iCol * BLOCK_SIZE;
				villainPos.z += iRow * BLOCK_SIZE;

				_characters.push_back(new SimpleVillain(villainPos, mSM->getRootSceneNode()->createChildSceneNode(), mSM));
			}
			else if (cell == VILLAIN_SPECIAL) {
				block = createBlock(nextPos, EMPTY); // donde esta el jugador solo puede haber un bloque vacio

				Vector3 villainPos = _labyrinthOrigin;
				villainPos.x += iCol * BLOCK_SIZE;
				villainPos.z += iRow * BLOCK_SIZE;

				_characters.push_back(new SpecialVillain(villainPos, mSM->getRootSceneNode()->createChildSceneNode(), mSM));
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
	Block* currBlock = getBlock(character->getPosition());

	Vector3 currDir = character->getGridOrientation();

	Vector3 newPos = currDir * character->getSpeed() * time + character->getPosition();

	Block* inFrontBlock = getBlock(character->getPosition() + currDir * BLOCK_SIZE);

	Real step = character->getSpeed() * time;

	Real before = (character->getPosition() - currBlock->getPosition()).dotProduct(currDir);
	Real after = before + step;

	if (character->is180Turn()) {
		character->rotateToNewDirection();
	}

	// if we reach or pass the center of the current block in this frame
	if (blockCenterReached(before, after)) {
		character->setPosition({ currBlock->getPosition().x, character->getPosition().y, currBlock->getPosition().z });

		Vector3 newDir = character->chooseDirection(*this);

		Block* nextBlock = getBlock(character->getPosition() + newDir * BLOCK_SIZE);
		
		if (nextBlock != nullptr && nextBlock->canPassThrough()) {
			character->rotateToNewDirection();
			inFrontBlock = nextBlock;
		}

		if (inFrontBlock != nullptr && inFrontBlock->canPassThrough() && character->getSpeed() > 0) {
			character->moveCharacter(after / character->getSpeed());   // move leftover distance
		}
		// else: blocked, stay in block until next frame
		return;
	}

	character->moveCharacter(time); // not in center so just move
}

Block* Labyrinth::getBlock(Vector3 position) const {
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

	return _blocks[row][col];
}

Block* Labyrinth::getBlock(Vector2 position) const {
	auto p = getBlockRowColFromPos(position);

	return _blocks[p.first][p.second];
}

bool Labyrinth::blockCenterReached(Real before, Real after) {
	return before <= 0 && after >= 0;
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

std::vector<std::vector<Block*>> Labyrinth::getBlocks() const {
	return _blocks;
}

std::pair<int, int> Labyrinth::getBlockRowColFromPos(Vector2 position) const {
	Vector2 relative = position - Vector2{ _labyrinthOrigin.x, _labyrinthOrigin.z };

	int col = static_cast<int>(
		std::round(relative.x / BLOCK_SIZE)
		);

	int row = static_cast<int>(
		std::round(relative.y / BLOCK_SIZE)
		);

	if (row < 0 || row >= _numRows ||
		col < 0 || col >= _numCols) {
		return { -1, -1 };
	}

	return { row, col };
}
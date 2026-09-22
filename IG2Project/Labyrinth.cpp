#include "Labyrinth.h"
#include <fstream>

Labyrinth::Labyrinth() : IG2Object() {
}

Labyrinth::Labyrinth(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, string fileName) : IG2Object(initPos, node, sceneMng) {	
	createLabyrinth(fileName);
}

void Labyrinth::createLabyrinth(string fileName) {
	ifstream file;
	file.open(fileName);

	if (!file) {
		throw "File not found" + fileName;
	}

	int numRows, numCols, iRow = 0, iCol = 0;
	char cell;

	file >> numRows >> numCols;

	Vector3 nextPos = getPosition();

	while (iRow < numRows) {
		iCol = 0;
		while (iCol < numCols) {
			file >> cell;

			if (cell == WALL_BLOCK) {
				createWallBlock(nextPos);
			}
			else if (cell == EMPTY_BLOCK) {
				createEmptyBlock(nextPos);
			}
			iCol++;
		}
		iRow++;
	}

	file.close();
}

void Labyrinth::createWallBlock(Vector3 pos) {
	SceneNode* wall = createChildSceneNode();

	IG2Object* wallObj = new IG2Object(pos + Vector3{0, Labyrinth::BLOCK_SIZE/2., 0}, wall, mSM, "cube.mesh");
	wallObj->setScale(getCubeScale(wallObj));

	_blocks.push_back(wallObj); 
}

void Labyrinth::createEmptyBlock(Vector3 pos) {
	SceneNode* empty = createChildSceneNode();

	IG2Object* emptyObj = new IG2Object(pos, empty, mSM);
	emptyObj->setScale(getCubeScale(emptyObj));

	_blocks.push_back(emptyObj);
}

Vector3 Labyrinth::getCubeScale(IG2Object* cube) {
	auto x = Labyrinth::BLOCK_SIZE / (float)cube->calculateBoxSize().x;
	auto y = Labyrinth::BLOCK_SIZE / (float)cube->calculateBoxSize().y;
	auto z = Labyrinth::BLOCK_SIZE / (float)cube->calculateBoxSize().z;

	return { x, y, z };
}
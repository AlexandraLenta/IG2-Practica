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

	while (iRow < numRows) {
		iCol = 0;
		while (iCol < numCols) {
			file >> cell;

			if (cell == WALL_BLOCK) {
				// create wall block
			}
			else if (cell == EMPTY_BLOCK) {
				// create empty block
			}
			iCol++;
		}
		iRow++;
	}

	file.close();
}
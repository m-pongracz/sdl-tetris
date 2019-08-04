#include "game_logic.h"



GameLogic::GameLogic(int gridHeight, int gridWidth)
{
	gridHeight_ = gridHeight;
	gridWidth_ = gridWidth;
}


bool GameLogic::canCubeGoDown_(GameObject &cube) {
	int firstTruePosY = cube.getFootprintBoundaryY(tbDirection::dBottom);

	if (cube.Y() < gridHeight_ - (firstTruePosY + 1)) {
		return true;
	}
	else {
		return false;
	}
}

bool GameLogic::canCubeGoLeft_(GameObject &cube) {
	int firstTruePosX = cube.getFootprintBoundaryX(lrDirection::dLeft);

	if (cube.X() + (firstTruePosX) > 0) {
		return true;
	}
	else {
		return false;
	}
}

bool GameLogic::canCubeGoRight_(GameObject &cube) {
	int firstTruePosX = cube.getFootprintBoundaryX(lrDirection::dRight);

	if (cube.X() < gridWidth_ - (firstTruePosX + 1)) {
		return true;
	}
	else {
		return false;
	}
}

bool GameLogic::canCubeBeRotatedCW(GameObject &cube) {


	GameObject* p = &cube;
	GameObject tempCube = *p;

	tempCube.RotateCCW();

	const int currCubeXOffset = tempCube.X();
	const int currCubeYOffset = tempCube.Y();	

	for (int y = 0; y < tempCube.Footprint().size(); y++) {
		for (int x = 0; x < tempCube.Footprint()[0].size(); x++) {

			if (tempCube.Footprint()[y][x] == true) {
				if (y + currCubeYOffset < 0 || y + currCubeYOffset > Config::gridHeight-1) return false;
				if (x + currCubeXOffset < 0 || x + currCubeXOffset > Config::gridWidth - 1) return false;
			}
		}
	}

	//cube.RotateCCW();

	//int bYbottom = cube.getFootprintBoundaryY(tbDirection::dBottom);
	//int bXright = cube.getFootprintBoundaryX(lrDirection::dRight);
	//int bYtop = cube.getFootprintBoundaryY(tbDirection::dTop);
	//int bXleft = cube.getFootprintBoundaryX(lrDirection::dLeft);

	//if (cube.Rotation() % 2 == 0) {
	//	if (cube.X() + bYbottom > gridWidth_ - 1 || cube.X() + bYtop < 0) {
	//		return false;
	//	}
	//	if (cube.Y() + bXright > gridHeight_ - 1 || cube.Y() + bXleft < 0) {
	//		return false;
	//	}

	//}
	//else {
	//	if (cube.X() + bYbottom > gridWidth_ - 1 || cube.X() + bYtop < 0) {
	//		return false;
	//	}
	//	if (cube.Y() + bXright > gridHeight_ - 1 || cube.Y() + bXleft < 0) {
	//		return false;
	//	}
	//}
	return true;
}


#include "game_logic.h"



GameLogic::GameLogic(int gridHeight, int gridWidth)
{
	gridHeight_ = gridHeight;
	gridWidth_ = gridWidth;
}


bool GameLogic::canCubeGoDown_(GameObject &cube) {
	int firstTruePosY = cube.getFootprintBoundaryY(tbDirection::dBottom);

	if (cube.Y() < gridHeight_ - (firstTruePosY+1)) {
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

	if (cube.X() < gridWidth_ - (firstTruePosX+1)) {
		return true;
	}
	else {
		return false;
	}
}


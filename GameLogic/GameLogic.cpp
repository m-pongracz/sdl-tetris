#include "game_logic.h"



GameLogic::GameLogic(int gridHeight, int gridWidth)
{
	gridHeight_ = gridHeight;
	gridWidth_ = gridWidth;

}


bool GameLogic::canCubeGoDown_(GameObject &cube) {

	int firstTruePosY = cube.getFootprintBoundaryY();

	if (cube.Y() < gridHeight_ - (firstTruePosY+1)) {
		return true;
	}
	else {
		return false;
	}
}

bool GameLogic::canCubeGoLeft_(GameObject &cube) {

	if (cube.X() > 0) {
		return true;
	}
	else {
		return false;
	}
}

bool GameLogic::canCubeGoRight_(GameObject &cube) {
	int firstTruePosX = cube.getFootprintBoundaryX();

	if (cube.X() < gridWidth_ - (firstTruePosX+1)) {
		return true;
	}
	else {
		return false;
	}
}


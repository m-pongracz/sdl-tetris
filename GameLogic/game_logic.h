#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "game_object.h"
#include "config.h"

class GameLogic
{
public:
	GameLogic(int gridHeight, int gridWidth);
	bool canCubeGoDown_(GameObject &cube);
	bool canCubeGoLeft_(GameObject &cube);
	bool canCubeGoRight_(GameObject &cube);
	bool canCubeBeRotatedCW(GameObject &cube);
private:
	int gridHeight_;
	int gridWidth_;
};

#endif


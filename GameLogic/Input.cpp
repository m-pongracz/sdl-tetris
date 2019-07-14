#include "input.h"
#include "game_logic.h"
#include "game.h"
#include <SDL.h>;

void Input::pollForCubeMovement(GameObject *cube) {
	GameLogic gameLogic = *new GameLogic(Game::gridHeight, Game::gridWidth);
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
			case SDLK_LEFT:
				if (gameLogic.canCubeGoLeft_(*cube)) cube->MoveL();
				break;
			case SDLK_RIGHT:
				if (gameLogic.canCubeGoRight_(*cube)) cube->MoveR();
				break;
			case SDLK_DOWN:
				if (gameLogic.canCubeGoDown_(*cube)) cube->MoveD();
				break;
			default:
				break;
			}
		}
	}
}
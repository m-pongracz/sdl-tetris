#include "input.h"
#include "game_logic.h"
#include "game.h"
#include <SDL.h>;

void Input::pollForCubeMovement(
	Game *game, 
	void(Game::*mdPtr)(), 
	void(Game::*mlPtr)(), 
	void(Game::*mrPtr)(), 
	void(Game::*rotatePtr)(),
	void(Game::*rushDownPtr)()

) {
	GameLogic gameLogic = *new GameLogic(Game::gridHeight, Game::gridWidth);
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
			case SDLK_LEFT:
				(game->*mlPtr)();
				break;
			case SDLK_RIGHT:
				(game->*mrPtr)();
				break;
			case SDLK_DOWN:
				(game->*mdPtr)();
				break;
			case SDLK_UP:
				(game->*rotatePtr)();
				break;
			case SDLK_SPACE:
				(game->*rushDownPtr)();
				break;
			default:
				break;
			}
		}
	}
}
#include "input.h"
#include "game_logic.h"
#include "game.h"
#include <SDL.h>;

void Input::pollForRunning
(
	Game *game,
	void(Game::*mdPtr)(),
	void(Game::*mlPtr)(),
	void(Game::*mrPtr)(),
	void(Game::*rotatePtr)(),
	void(Game::*rushDownPtr)(),
	void(Game::*pausePtr)()
)
{
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
			case SDLK_p:
				(game->*pausePtr)();
				break;
			default:
				break;
			}
		}
	}
}

void Input::pollForStopped
(
	Game *game,
	void(Game::*resumePtr)()
)
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
			case SDLK_p:
				(game->*resumePtr)();
				break;
			default:
				break;
			}
		}
	}
}

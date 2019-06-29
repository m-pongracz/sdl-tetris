#ifndef GAME_H
#define GAME_H
#include "game_object.h";
#include <SDL.h>
#include "sdl_helper.h"

class Game
{
public:
	Game();
	~Game();
	bool grid[8 * 14];
	auto score() const& -> const int& { return score_; };
	auto score() & -> const int& { return score_; };
	auto currentCube() const& -> const GameObject& { return currentCube_; };
	auto currentCube() & -> const GameObject& { return currentCube_; };
	void start();
	void stop();
	void pause();
	void resume();
private:
	int score_;
	GameObject currentCube_;
	GameObject* getRandomCube_();
	void getNextCube_();
	void mainLoop_();
	void startMainLoop_();
	bool running_;
	bool quit_;
	void draw_();
	SdlHelper *sdlHelper_;
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Texture *bg;
	SDL_Texture *cube;
	SDL_Texture *gridBox;
	int windowHeight_;
	int windowWidth_;
	int getRandomNumber_(int min, int max);
	bool canCubeGoDown_();
};
#endif

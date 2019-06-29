#include "game.h"
#include <stdlib.h>
#include <iostream>  
#include <chrono>

#include "res_path.h"
#include "logging.h"

#include "SDL_image.h"

Game::Game()
{
	Logging log(&std::cout);
	sdlHelper_ = new SdlHelper(&log);

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		log.logSDLError("SDL_Init Error: ");
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		log.logSDLError("IMG_Init");
		SDL_Quit();
	}

	win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		log.logSDLError("SDL_CreateWindow Error: ");
		SDL_Quit();
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
		SDL_DestroyWindow(win);
		log.logSDLError("SDL_CreateRenderer Error: ");
		SDL_Quit();
	}

	std::string bgImagePath = getResourcePath("img") + "checkered.bmp";
	std::string clipImagePath = getResourcePath("img") + "clip.png";
	std::string cubeImagePath = getResourcePath("img") + "cube.bmp";
	std::string gridBoxImagePath = getResourcePath("img") + "gridbox.bmp";

	bg = sdlHelper_ -> loadTexture(bgImagePath, ren);
	cube = sdlHelper_ -> loadTexture(cubeImagePath, ren);
	gridBox = sdlHelper_ -> loadTexture(gridBoxImagePath, ren);


	if (bg == nullptr || cube == nullptr || gridBox == nullptr) {
		cleanup(bg, cube, gridBox, ren, win);
		SDL_Quit();
	}

	score_ = 0;
	getNextCube_();
	quit_ = false;

}

Game::~Game()
{
}

GameObject* Game::getRandomCube_()
{
	GameObject cube(static_cast<CubeType>(rand() % 6));
	return &cube;
}

void Game::getNextCube_()
{
	currentCube_ = *getRandomCube_();
}

void Game::mainLoop_()
{
	using clock = std::chrono::high_resolution_clock;
	auto startTime = clock::now();
	std::chrono::milliseconds elapsedTime;
	while (!quit_) {
		while (running_) {
			auto deltaTime = clock::now() - startTime;
			elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime);
			if (elapsedTime.count() % 1000 == 0) {
				std::cout << elapsedTime.count() << std::endl;


				SDL_RenderClear(ren);

				for (int x = 0; x < 8; ++x) {
					for (int y = 0; y < 14; ++y) {
						sdlHelper_ -> renderTexture(gridBox, ren, x * 20, y * 20, 20, 20);
						if (grid[x + (8*y)] == true) {
							sdlHelper_ -> renderTexture(cube, ren, x * 20, y * 20, 20, 20);
						}
					}
				}

				SDL_RenderPresent(ren);

			}
		}
	}
}

void Game::startMainLoop_()
{
	running_ = true;
	mainLoop_();
}

void Game::draw_()
{

}

void Game::start()
{
	startMainLoop_();
}
void Game::stop()
{

}
void Game::resume()
{

}
void Game::pause()
{

}


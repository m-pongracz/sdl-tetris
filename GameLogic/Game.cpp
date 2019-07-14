#include "game.h"
#include <stdlib.h>
#include <iostream>  
#include <chrono>
#include "random"
#include <string>
#include "input.h"

Game::Game(TetrisRendering* renderer) : gameLogic_(gridHeight, gridWidth)
{
	//gameLogic_ = *new GameLogic(gridHeight, gridWidth);

	renderer_ = renderer;

	grid.resize(gridWidth, std::vector<bool>(gridHeight, false));


	score_ = 0;
	getNextCube_();
	quit_ = false;

	//for (int x = 0; x < 20; x++) {
	//	if (gameLogic_.canCubeGoDown_(currentCube_)) currentCube_.MoveD();
	//}
	//for (int x = 0; x < 20; x++) {
	//	if (gameLogic_.canCubeGoRight_(currentCube_)) currentCube_.MoveR();
	//}
}

Game::~Game()
{
}

GameObject Game::getRandomCube_()
{
	int r = getRandomNumber_(0, 6);	
	GameObject cube(static_cast<CubeType>(r));
	return cube;
}

void Game::getNextCube_()
{
	currentCube_ = getRandomCube_();
}

void Game::mainLoop_()
{
	int lastElapsedTime = 0;

	using clock = std::chrono::high_resolution_clock;
	auto startTime = clock::now();
	std::chrono::milliseconds elapsedTime;
	while (!quit_) {
		while (running_) {

			Input::pollForCubeMovement(&currentCube_);

			for (int x = 0; x < Game::gridWidth; x++) {
				for (int y = 0; y < Game::gridHeight; y++) {
					grid[x][y] = false;
				}
			}

			auto deltaTime = clock::now() - startTime;
			elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime);			

			if (elapsedTime.count() >= lastElapsedTime + 1000) {
				lastElapsedTime = elapsedTime.count();
				currentCube_.MoveD();
			}			

			std::cout << elapsedTime.count() << std::endl;

			const int currCubeXOffset = currentCube_.X();
			const int currCubeYOffset = currentCube_.Y();

			for (int x = 0; x < GameObject::fprintCols; x++) {
				for (int y = 0; y < GameObject::fprintRows; y++) {

					bool nextGridVal = false;

					if (currentCube_.Footprint()[y][x] == true) {
						nextGridVal = true;
						grid[x + currCubeXOffset][y + currCubeYOffset] = nextGridVal;
					}
				}
			}

			if (renderer_ != nullptr) {
				renderer_->RenderFrame(grid);
			}

			if (!gameLogic_.canCubeGoDown_(currentCube_)) {
				getNextCube_();
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

int Game::getRandomNumber_(int min, int max) {
	static std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(mt);
}

int Game::test() {
	return 1;
}

void Game::MoveCubeDown() {

}
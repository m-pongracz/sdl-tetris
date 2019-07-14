#include "game.h"
#include <stdlib.h>
#include <iostream>  
#include <chrono>
#include "random"
#include <string>
#include "input.h"

Game::Game(TetrisRendering* renderer) : gameLogic_(gridHeight, gridWidth)
{
	renderer_ = renderer;

	grid.resize(gridWidth, std::vector<bool>(gridHeight, false));

	score_ = 0;
	getNextCube_();
	quit_ = false;
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
			typedef void(Game::*mdPtr)();
			mdPtr md = &Game::MoveCubeDown;

			typedef void(Game::*mlPtr)();
			mdPtr ml = &Game::MoveCubeLeft;

			typedef void(Game::*mrPtr)();
			mdPtr mr = &Game::MoveCubeRight;

			typedef void(Game::*rotatePtr)();
			rotatePtr rotate = &Game::RotateCube;

			Input::pollForCubeMovement(this, md, ml, mr, rotate);

			auto deltaTime = clock::now() - startTime;
			elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime);

			if (elapsedTime.count() >= lastElapsedTime + 1000) {
				lastElapsedTime = elapsedTime.count();

				//MoveCubeDown();
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

			for (int y = gridHeight-1; y >= 0; --y) {
				bool isRowComplete = true;
				for (int x = gridWidth-1; x >= 0; --x) {
					if (grid[x][y] == false) isRowComplete = false;
				}
				if (isRowComplete == true) {
					for (int x = gridWidth - 1; x >= 0; --x) {
						grid[x][y] = false;
					}
					for (int y1 = y; y1 >= 1; --y1) {
						bool isRowComplete = true;
						for (int x1 = gridWidth - 1; x1 >= 0; --x1) {
							grid[x1][y1-1] = grid[x1][y1];
						}
					}
					if(currentCube_.X() != 0) currentCube_.setX(currentCube_.X() - 1);
				}
			}

			if (renderer_ != nullptr) {
				renderer_->RenderFrame(grid);
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
	if (gameLogic_.canCubeGoDown_(currentCube_)) {
		const int currCubeXOffset = currentCube_.X();
		const int currCubeYOffset = currentCube_.Y() + 1;

		auto cleanedPositions = PrevCubePosCleanup();

		if (cubeInDirection(direction::down)) {
			getNextCube_();
			imprintPositionsOnGrid(cleanedPositions);
			return;
		}

		currentCube_.MoveD();
	}
	else getNextCube_();
}

void Game::MoveCubeLeft() {
	if (gameLogic_.canCubeGoLeft_(currentCube_)) {
		const int currCubeXOffset = currentCube_.X() - 1;
		const int currCubeYOffset = currentCube_.Y();

		auto cleanedPositions = PrevCubePosCleanup();

		if (cubeInDirection(direction::left)) {
			imprintPositionsOnGrid(cleanedPositions);
			return;
		}

		currentCube_.MoveL();
	}
}

void Game::MoveCubeRight() {
	if (gameLogic_.canCubeGoRight_(currentCube_)) {
		const int currCubeXOffset = currentCube_.X() + 1;
		const int currCubeYOffset = currentCube_.Y();

		auto cleanedPositions = PrevCubePosCleanup();

		if (cubeInDirection(direction::right)) {
			imprintPositionsOnGrid(cleanedPositions);
			return;
		}

		currentCube_.MoveR();
	}
}

void Game::RotateCube() {
	PrevCubePosCleanup();
	int bY = currentCube_.getFootprintBoundaryY();
	if (currentCube_.X() + bY > gridWidth - 1) {
		int newX = (gridWidth - 1) - bY;
		currentCube_.setX(newX);
	}

	currentCube_.RotateCCW();
}

std::vector<std::vector<int>> Game::PrevCubePosCleanup() {

	int trueCount = 0;
	for (int x = 0; x < GameObject::fprintCols; x++) {
		for (int y = 0; y < GameObject::fprintRows; y++) {
			if (currentCube_.Footprint()[y][x] == true) {
				++trueCount;
			}
		}
	}

	std::vector<std::vector<int>> cleanedPositions = *new std::vector<std::vector<int>>();
	cleanedPositions.resize(trueCount, std::vector<int>(2));

	const int currCubeXOffset = currentCube_.X();
	const int currCubeYOffset = currentCube_.Y();

	int cI = 0;
	for (int x = 0; x < GameObject::fprintCols; x++) {
		for (int y = 0; y < GameObject::fprintRows; y++) {
			if (currentCube_.Footprint()[y][x] == true) {
				grid[x + currCubeXOffset][y + currCubeYOffset] = false;
				cleanedPositions[cI][0] = x + currCubeXOffset;
				cleanedPositions[cI][1] = y + currCubeYOffset;
				++cI;
			}
		}
	}
	return cleanedPositions;
}

bool Game::cubeInDirection(direction dir) {

	int currCubeXOffset = currentCube_.X();
	int currCubeYOffset = currentCube_.Y();

	switch (dir) {
	case direction::left:
		--currCubeXOffset;
		break;
	case direction::right:
		++currCubeXOffset;
		break;
	case direction::down:
		++currCubeYOffset;
		break;
	}
	for (int x = 0; x < GameObject::fprintCols; x++) {
		for (int y = 0; y < GameObject::fprintRows; y++) {
			if (currentCube_.Footprint()[y][x] == true && grid[x + currCubeXOffset][y + currCubeYOffset] == true) {
				return true;
			}
		}
	}
	return false;
}

void Game::imprintPositionsOnGrid(std::vector<std::vector<int>> positions) {
	for (int z = 0; z < positions.size(); z++) {
		grid[positions[z][0]][positions[z][1]] = true;
	}
}
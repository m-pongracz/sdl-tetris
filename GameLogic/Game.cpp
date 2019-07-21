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

	grid.resize(gridHeight, std::vector<bool>(gridWidth, false));

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
	r = 6;
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

			for (int y = 0; y < currentCube_.Footprint().size(); y++) {
				for (int x = 0; x < currentCube_.Footprint()[0].size(); x++) {

					bool nextGridVal = false;
					//if footprint is true -> imprint true on grid according to footprint + its x,y offset
					if (currentCube_.Footprint()[y][x] == true) {
						nextGridVal = true;
						grid[y + currCubeYOffset][x + currCubeXOffset] = nextGridVal;
					}
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

	bool wasInDirection = false;
	bool notOutsideGrid = false;

	if (gameLogic_.canCubeGoDown_(currentCube_)) {
		notOutsideGrid = true;
		const int currCubeXOffset = currentCube_.X();
		const int currCubeYOffset = currentCube_.Y() + 1;

		auto cleanedPositions = PrevCubePosCleanup();
		if (cubeInDirection(direction::down)) {
			wasInDirection = true;


			imprintPositionsOnGrid(cleanedPositions);

		}

		currentCube_.MoveD();
	}

	if (wasInDirection || !notOutsideGrid) {
		for (int y = gridHeight - 1; y >= 0; --y) {
			bool isRowComplete = true;
			for (int x = gridWidth - 1; x >= 0; --x) {
				if (grid[y][x] == false) isRowComplete = false;
			}
			if (isRowComplete == true) {
				for (int x = gridWidth - 1; x >= 0; --x) {
					grid[y][x] = false;
				}
				//shift all rows down
				for (int y1 = y; y1 >= 1; --y1) {
					bool isRowComplete = true;
					for (int x1 = gridWidth - 1; x1 >= 0; --x1) {
						grid[y1][x1] = grid[y1 - 1][x1];
					}
				}
				//move y pos pointer one pos down again because of the row shift
				y++;
				if (currentCube_.X() != 0) currentCube_.setX(currentCube_.X() - 1);
			}
		}
		getNextCube_();
	}
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
	auto cleanedPositions = PrevCubePosCleanup();
	//TODO: bude podle toho jaká je pøedchozí rotace -> když bude 3 tak se to bude brát z leva/hora
	int bYbottom = currentCube_.getFootprintBoundaryY(tbDirection::dBottom);
	int bXright = currentCube_.getFootprintBoundaryX(lrDirection::dRight);
	int bYtop = currentCube_.getFootprintBoundaryY(tbDirection::dTop);
	int bXleft = currentCube_.getFootprintBoundaryX(lrDirection::dLeft);

	if (currentCube_.X() + bYbottom > gridWidth - 1 || currentCube_.X() - bYtop < 0) {

		int newX = (gridWidth - 1) - bYbottom;
		//currentCube_.setX(newX);

		return;
	}
	if (currentCube_.Y() + bXright > gridHeight - 1 || currentCube_.Y() - bXleft < 0) {
		return;
	}
	//if (currentCube_.Y() + bYtop > gridWidth - 1 || currentCube_.Y() + bYtop < 0) {
	//	return;
	//}
	//if (currentCube_.Y() + bXleft > gridHeight - 1 || currentCube_.Y() + bXleft < 0) {
	//	return;
	//}

	if (cubeInDirection(direction::current)) {
		imprintPositionsOnGrid(cleanedPositions);
		return;
	}

	currentCube_.RotateCW();
}

std::vector<std::vector<int>> Game::PrevCubePosCleanup() {

	int trueCount = 0;
	for (int y = 0; y < currentCube_.Footprint().size(); y++) {
		for (int x = 0; x < currentCube_.Footprint()[0].size(); x++) {
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
	for (int y = 0; y < currentCube_.Footprint().size(); y++) {
		for (int x = 0; x < currentCube_.Footprint()[0].size(); x++) {
			if (currentCube_.Footprint()[y][x] == true) {
				grid[y + currCubeYOffset][x + currCubeXOffset] = false;
				cleanedPositions[cI][0] = y + currCubeYOffset;
				cleanedPositions[cI][1] = x + currCubeXOffset;
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
	case direction::current:
		break;
	}
	for (int y = 0; y < currentCube_.Footprint().size(); y++) {
		for (int x = 0; x < currentCube_.Footprint()[0].size(); x++) {
			if (currentCube_.Footprint()[y][x] == true && grid[y + currCubeYOffset][x + currCubeXOffset] == true) {
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
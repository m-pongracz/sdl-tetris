#include "game.h"
#include <stdlib.h>
#include <iostream>  
#include <chrono>
#include "random"
#include <string>
#include "input.h"

Game::Game(TetrisRendering* renderer) : _gameLogic(gridHeight, gridWidth)
{
	_renderer = renderer;

	grid.resize(gridHeight, std::vector<bool>(gridWidth, false));

	_score = 0;
	getNextCube();
	_quit = false;

	_moveDPtr = &Game::moveCubeDown;
	_moveLPtr = &Game::moveCubeLeft;
	_moveRPtr = &Game::moveCubeRight;
	_rotatePtr = &Game::rotateCube;
	_rushDownPtr = &Game::rushCubeDown;

	_pausePtr = &Game::Pause;
	_resumePtr = &Game::Resume;

}

Game::~Game()
{
}

GameObject Game::getRandomCube()
{
	int r = getRandomNumber(0, 6);
	GameLogic gameLogic = *new GameLogic(Game::gridHeight, Game::gridWidth);
	GameObject cube(static_cast<CubeType>(r));

	cube.setX(3);

	return cube;
}

void Game::getNextCube()
{
	_score += 10;

	_currentCube = getRandomCube();

	if (cubeOnNewPosition(_currentCube)) {
		_running = false;
	}

	Game::renderScore();

	updateGrid();
}

void Game::mainLoop()
{
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	Input input = Input(this, keystates);

	int timeToMoveDown = 0;
	int timeToNextInput = 0;
	int timeTillSecond = 0;
	int loops = 0;

	using clock = std::chrono::high_resolution_clock;
	auto startTime = clock::now();
	std::chrono::milliseconds elapsedTime;
	while (!_quit)
	{
		//Input::pollForStopped
		//(
		//	this,
		//	_resumePtr
		//);

		bool wasPaused = true;

		if (_renderer != nullptr) {

			Game::renderGrid();

			Color overlayColor(0, 0, 0, 127);
			_renderer->RenderColor(_renderer->grid()->GetColumnAt(2, 0), overlayColor);
			Color pausedColor(255, 255, 255, 255);
			_renderer->RenderText
			(
				_renderer->grid()->GetColumnAt(2, 0),
				"PAUSED",
				pausedColor,
				64,
				AlignV::aCenter,
				AlignH::aMiddle
			);

			_renderer->Render();
		}

		while (_running) {

			if (wasPaused) {
				renderGrid();
			}

			wasPaused = false;

			loops++;
			input.PollDown();

			auto deltaTime = clock::now() - startTime;
			elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime);

			if (elapsedTime.count() >= timeToMoveDown + 1000 - elapsedTime.count() / 10000) {
				timeToMoveDown = elapsedTime.count();

				//moveCubeDown();
			}

			if (elapsedTime.count() >= timeToNextInput + 100) {
				timeToNextInput = elapsedTime.count();
				input.PollHold();
			}

			processVelocity();
			std::cout << _score << std::endl;

			if (_renderer != nullptr) {
				//_renderer->Clear();
				Game::renderInfo(elapsedTime.count(), loops);
				
				_renderer->Render();
			}
		}
	}
}

void Game::updateGrid() {
	const int currCubeXOffset = _currentCube.X();
	const int currCubeYOffset = _currentCube.Y();

	for (int y = 0; y < _currentCube.Footprint().size(); y++) {
		for (int x = 0; x < _currentCube.Footprint()[0].size(); x++) {

			bool nextGridVal = false;
			//if footprint is true -> imprint true on grid according to footprint + its x,y offset
			if (_currentCube.Footprint()[y][x] == true) {
				nextGridVal = true;
				grid[y + currCubeYOffset][x + currCubeXOffset] = nextGridVal;
			}
		}
	}

	renderGrid();
}

void Game::renderInfo(int miliseconds, int loops) {
	Color textColor(255, 0, 0, 255);
	Color scoreBgColor(0, 0, 0, 255);

	_renderer->RenderColor(_renderer->grid()->GetColumnAt(0, 0), scoreBgColor);
	_renderer->RenderColor(_renderer->grid()->GetColumnAt(0, 1), scoreBgColor);

	int seconds = miliseconds / 1000;
	_renderer->RenderText
	(
		_renderer->grid()->GetColumnAt(0, 0),
		std::to_string(seconds),
		textColor,
		64,
		AlignV::aCenter,
		AlignH::aMiddle
	);

	_renderer->RenderText
	(
		_renderer->grid()->GetColumnAt(0, 1),
		std::to_string(seconds > 0 ? loops / seconds : 0),
		textColor,
		64,
		AlignV::aCenter,
		AlignH::aMiddle
	);
}

void Game::renderScore() {
	Color scoreColor(255, 0, 0, 255);
	Color scoreBgColor(255, 255, 0, 255);

	_renderer->RenderColor(_renderer->grid()->GetColumnAt(1, 0), scoreBgColor);
	_renderer->RenderText
	(
		_renderer->grid()->GetColumnAt(1, 0),
		std::to_string(_score),
		scoreColor,
		64,
		AlignV::aCenter,
		AlignH::aMiddle
	);
}

void Game::renderGrid() {
	_renderer->RenderFrame(_renderer->grid()->GetColumnAt(2, 0), grid);
}

void Game::startMainLoop()
{
	_running = true;
	mainLoop();
}

void Game::draw()
{

}

void Game::Start()
{
	startMainLoop();
}
void Game::Stop()
{

}
void Game::Resume()
{
	_running = true;
}
void Game::Pause()
{
	_running = false;
}

int Game::getRandomNumber(int min, int max) {
	static std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(mt);
}

int Game::Test() {
	return 1;
}

void Game::moveCubeDown() {

	bool cubeInDirection = false;
	bool borderInDirection;

	if (_gameLogic.canCubeGoDown_(_currentCube)) {
		borderInDirection = false;

		auto cleanedPositions = prevCubePosCleanup();

		GameObject* p = &_currentCube;
		GameObject cube = *p;
		cube.MoveD();

		if (cubeOnNewPosition(cube)) {
			cubeInDirection = true;

			imprintPositionsOnGrid(cleanedPositions);
		}
		else {
			cubeInDirection = false;
			_currentCube.MoveD();
		}
	}
	else {
		borderInDirection = true;
	}

	if (cubeInDirection || borderInDirection) {
		deleteCompleteRows();
		getNextCube();
	}

	updateGrid();
}

void Game::moveCubeLeft() {
	if (_gameLogic.canCubeGoLeft_(_currentCube)) {
		const int currCubeXOffset = _currentCube.X() - 1;
		const int currCubeYOffset = _currentCube.Y();

		auto cleanedPositions = prevCubePosCleanup();

		GameObject* p = &_currentCube;
		GameObject cube = *p;

		cube.MoveL();

		if (cubeOnNewPosition(cube)) {
			imprintPositionsOnGrid(cleanedPositions);
			return;
		}

		_currentCube.MoveL();
	}

	updateGrid();
}

void Game::moveCubeRight() {
	if (_gameLogic.canCubeGoRight_(_currentCube)) {
		const int currCubeXOffset = _currentCube.X() + 1;
		const int currCubeYOffset = _currentCube.Y();

		auto cleanedPositions = prevCubePosCleanup();

		GameObject* p = &_currentCube;
		GameObject cube = *p;

		cube.MoveR();

		if (cubeOnNewPosition(cube)) {
			imprintPositionsOnGrid(cleanedPositions);
			return;
		}

		_currentCube.MoveR();
	}

	updateGrid();
}

void Game::rotateCube() {
	auto cleanedPositions = prevCubePosCleanup();

	if (!_gameLogic.canCubeBeRotatedCW(_currentCube)) {
		return;
	}

	GameObject* p = &_currentCube;
	GameObject cube = *p;

	cube.RotateCCW();

	if (cubeOnNewPosition(cube)) {
		imprintPositionsOnGrid(cleanedPositions);
		return;
	}

	_currentCube.RotateCCW();

	updateGrid();
}

void Game::rushCubeDown() {

	bool floorHit = false;

	while (!floorHit) {
		if (_gameLogic.canCubeGoDown_(_currentCube)) {


			auto cleanedPositions = prevCubePosCleanup();

			GameObject* p = &_currentCube;
			GameObject cube = *p;
			cube.MoveD();

			if (cubeOnNewPosition(cube)) {
				floorHit = true;

				imprintPositionsOnGrid(cleanedPositions);
			}
			else {
				_currentCube.MoveD();
			}
		}
		else {
			floorHit = true;
		}
	}
	//cheating my way through the current cube positions not being imprinted on the grid since 
	//this is raised by kboard event and normal imprinting is in the main loop
	auto positions = prevCubePosCleanup();
	imprintPositionsOnGrid(positions);

	moveCubeDown();
}

std::vector<std::vector<int>> Game::prevCubePosCleanup() {

	int trueCount = 0;
	for (int y = 0; y < _currentCube.Footprint().size(); y++) {
		for (int x = 0; x < _currentCube.Footprint()[0].size(); x++) {
			if (_currentCube.Footprint()[y][x] == true) {
				++trueCount;
			}
		}
	}

	std::vector<std::vector<int>> cleanedPositions = *new std::vector<std::vector<int>>();
	cleanedPositions.resize(trueCount, std::vector<int>(2));

	const int currCubeXOffset = _currentCube.X();
	const int currCubeYOffset = _currentCube.Y();

	int cI = 0;
	for (int y = 0; y < _currentCube.Footprint().size(); y++) {
		for (int x = 0; x < _currentCube.Footprint()[0].size(); x++) {
			if (_currentCube.Footprint()[y][x] == true) {
				grid[y + currCubeYOffset][x + currCubeXOffset] = false;
				cleanedPositions[cI][0] = y + currCubeYOffset;
				cleanedPositions[cI][1] = x + currCubeXOffset;
				++cI;
			}
		}
	}
	return cleanedPositions;
}

bool Game::cubeOnNewPosition(GameObject cube) {

	int currCubeXOffset = cube.X();
	int currCubeYOffset = cube.Y();

	for (int y = 0; y < cube.Footprint().size(); y++) {
		for (int x = 0; x < cube.Footprint()[0].size(); x++) {
			if (cube.Footprint()[y][x] == true && grid[y + currCubeYOffset][x + currCubeXOffset] == true) {
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

void Game::deleteCompleteRows() {
	for (int y = gridHeight - 1; y >= 0; --y) {
		bool isRowComplete = true;
		for (int x = gridWidth - 1; x >= 0; --x) {
			if (grid[y][x] == false) isRowComplete = false;
		}
		if (isRowComplete == true) {

			_score += 100;

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
			if (_currentCube.X() != 0) _currentCube.setX(_currentCube.X() - 1);

			Game::renderScore();
		}
	}
}

void Game::ChangeVelocity(VelocityDirection direction, int value) {
	switch (direction) {
	case VelocityDirection::vLeft:
		_currentCube.velocity.left = value;
		break;
	case VelocityDirection::vRight:
		_currentCube.velocity.right = value;
		break;
	case VelocityDirection::vDown:
		_currentCube.velocity.down = value;
		break;
	case VelocityDirection::vRotation:
		_currentCube.velocity.rotation = value;
		break;
	}
}

void Game::processVelocity() {
	while (_currentCube.velocity.left > 0) {
		moveCubeLeft();
		--_currentCube.velocity.left;
	}
	while (_currentCube.velocity.right > 0) {
		moveCubeRight();
		--_currentCube.velocity.right;
	}
	while (_currentCube.velocity.down > 0) {
		moveCubeDown();
		--_currentCube.velocity.down;
	}
	while (_currentCube.velocity.rotation > 0) {
		rotateCube();
		--_currentCube.velocity.rotation;
	}

}
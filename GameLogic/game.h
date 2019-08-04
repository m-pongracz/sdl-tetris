#ifndef GAME_H
#define GAME_H
#include "game_object.h"
#include <vector>
#include <SDL.h>
#include "../TetrisRendering/tetris_rendering.h"
#include "game_logic.h"
#include "config.h"

class Game
{
public:
	static const int gridWidth = Config::gridWidth;
	static const int gridHeight = Config::gridHeight;
	Game(TetrisRendering* renderer);
	~Game();
	std::vector<std::vector<bool>> grid;
	auto score() const& -> const int& { return _score; };
	auto score() & -> const int& { return _score; };
	auto currentCube() const& -> const GameObject& { return _currentCube; };
	auto currentCube() & -> const GameObject& { return _currentCube; };
	void Start();
	void Stop();
	void Pause();
	void Resume();
	auto Running() const& -> const bool& { return _running; };
	auto Running() & -> const bool& { return _running; };
	auto Quit() const& -> const bool& { return _quit; };
	auto Quit() & -> const bool& { return _quit; };
	int Test();
private:
	int _score;
	GameObject _currentCube;
	GameObject getRandomCube();
	void getNextCube();
	void mainLoop();
	void startMainLoop();
	bool _running;
	bool _quit;
	void draw();
	int _windowHeight;
	int _windowWidth;
	int getRandomNumber(int min, int max);
	GameLogic _gameLogic;
	TetrisRendering *_renderer;
	void moveCubeDown();
	void moveCubeLeft();
	void moveCubeRight();
	void rotateCube();
	void rushCubeDown();
	std::vector<std::vector<int>> prevCubePosCleanup();
	bool cubeOnNewPosition(GameObject cube);
	void imprintPositionsOnGrid(std::vector<std::vector<int>> positions);
	void deleteCompleteRows();

};
#endif

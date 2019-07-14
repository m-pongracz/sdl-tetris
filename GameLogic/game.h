#ifndef GAME_H
#define GAME_H
#include "game_object.h"
#include <vector>
#include <SDL.h>
#include "../TetrisRendering/tetris_rendering.h"
#include "game_logic.h"

enum direction { left, right, down };

class Game
{
public:
	static const int gridWidth = 8;
	static const int gridHeight = 14;
	Game(TetrisRendering* renderer);
	~Game();
	std::vector<std::vector<bool>> grid;
	auto score() const& -> const int& { return score_; };
	auto score() & -> const int& { return score_; };
	auto currentCube() const& -> const GameObject& { return currentCube_; };
	auto currentCube() & -> const GameObject& { return currentCube_; };
	void start();
	void stop();
	void pause();
	void resume();
	auto running() const& -> const bool& { return running_; };
	auto running() & -> const bool& { return running_; };
	auto quit() const& -> const bool& { return quit_; };
	auto quit() & -> const bool& { return quit_; };
	int test();
private:
	int score_;
	GameObject currentCube_;
	GameObject getRandomCube_();
	void getNextCube_();
	void mainLoop_();
	void startMainLoop_();
	bool running_;
	bool quit_;
	void draw_();
	int windowHeight_;
	int windowWidth_;
	int getRandomNumber_(int min, int max);
	GameLogic gameLogic_;
	TetrisRendering *renderer_;
	void MoveCubeDown();
	void MoveCubeLeft();
	void MoveCubeRight();
	void RotateCube();
	std::vector<std::vector<int>> PrevCubePosCleanup();
	bool cubeInDirection(direction dir);
	void imprintPositionsOnGrid(std::vector<std::vector<int>> positions);
};
#endif

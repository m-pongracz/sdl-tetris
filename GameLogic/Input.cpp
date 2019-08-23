#include "input.h"
#include "game_logic.h"
#include "game.h"
#include <SDL.h>;

Input::Input(Game* game, const Uint8* keyStates) {
	_game = game;
	_keyStates = keyStates;
}

void Input::PollDown()
{
	updateStates();

	bool(Input::*keyPressTypePtr)(int);
	keyPressTypePtr = &Input::keyPressed;

	pollByPressType(keyPressTypePtr);
	if ((this->*keyPressTypePtr)(SDL_SCANCODE_SPACE))
	{
		_game->rushCubeDown();
	}
}

void Input::PollHold()
{
	//updateStates();

	bool(Input::*keyPressTypePtr)(int);
	keyPressTypePtr = &Input::keyHeld;

	pollByPressType(keyPressTypePtr);
}

void Input::Poll() {
	//updateStates();

	//if (key(SDL_SCANCODE_LEFT))
	//{
	//	_game->ChangeVelocity(VelocityDirection::vLeft, 1);
	//}
	//if (key(SDL_SCANCODE_RIGHT))
	//{
	//	_game->ChangeVelocity(VelocityDirection::vRight, 1);
	//}
	//if (key(SDL_SCANCODE_UP)) _game->rotateCube();
	//if (key(SDL_SCANCODE_DOWN)) _game->moveCubeDown();
	//if (key(SDL_SCANCODE_SPACE)) _game->rushCubeDown();
}

void Input::updateStates() {
	updateState(_previousState);
	SDL_PumpEvents();
	updateState(_currentState);
}

void Input::updateState(bool* stateArr) {
	int keyArr[5] =
	{
		SDL_SCANCODE_LEFT,
		SDL_SCANCODE_RIGHT,
		SDL_SCANCODE_UP,
		SDL_SCANCODE_DOWN,
		SDL_SCANCODE_SPACE
	};

	for (int key : keyArr) {
		stateArr[key] = !!_keyStates[key];
	}
}

bool Input::keyPressed(int key) {
	return !_previousState[key] && _currentState[key];
	//return _currentState[key];
}

bool Input::keyHeld(int key) {
	return _previousState[key] && _currentState[key];

}

bool Input::key(int key) {
	return _currentState[key];

}

void Input::pollByPressType(bool(Input::*keyPressTypePtr)(int)) {
	if ((this->*keyPressTypePtr)(SDL_SCANCODE_LEFT))
	{
		_game->ChangeVelocity(VelocityDirection::vLeft, 1);
	}
	if ((this->*keyPressTypePtr)(SDL_SCANCODE_RIGHT))
	{
		_game->ChangeVelocity(VelocityDirection::vRight, 1);
	}
	if ((this->*keyPressTypePtr)(SDL_SCANCODE_UP))
	{
		_game->ChangeVelocity(VelocityDirection::vRotation, 1);
	}
	if ((this->*keyPressTypePtr)(SDL_SCANCODE_DOWN))
	{
		_game->ChangeVelocity(VelocityDirection::vDown, 1);
	}
}
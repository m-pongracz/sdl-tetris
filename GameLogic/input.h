#ifndef INPUT_H
#define INPUT_H

#include "game_object.h"
#include "game.h"

class Input
{
public:
	Input(Game* game, const Uint8* keyStates);
	void PollDown();
	void PollHold();
	void Poll();


private:
	Game* _game;
	const Uint8* _keyStates;
	bool _previousState[512];
	bool _currentState[512];

	void updateState(bool* stateArr);
	void updateStates();
	bool keyPressed(int key);
	bool keyHeld(int key);
	bool key(int key);
	void pollByPressType(bool(Input::*keyPressTypePtr)(int));
};

#endif

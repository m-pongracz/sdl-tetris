#ifndef INPUT_H
#define INPUT_H

#include "game_object.h"
#include "game.h"

class Input
{
public:
	static void pollForRunning
	(
		Game *game,
		void(Game::*mdPtr)(),
		void(Game::*mlPtr)(),
		void(Game::*mrPtr)(),
		void(Game::*rotatePtr)(),
		void(Game::*rushDownPtr)(),
		void(Game::*pausePtr)()
	);
	static void pollForStopped
	(
		Game *game,

		void(Game::*resumePtr)()
	);

};

#endif

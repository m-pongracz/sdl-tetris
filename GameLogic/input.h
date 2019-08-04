#ifndef INPUT_H
#define INPUT_H

#include "game_object.h"
#include "game.h"

class Input
{
public:
	static void pollForCubeMovement(
		Game *game, 
		void(Game::*mdPtr)(), 
		void(Game::*mlPtr)(), 
		void(Game::*mrPtr)(), 
		void(Game::*rotatePtr)(),
		void(Game::*rushDownPtr)()
	);
	
};

#endif

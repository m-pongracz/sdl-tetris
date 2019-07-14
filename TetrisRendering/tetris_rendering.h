#ifndef TETRISRENDERING_H
#define TETRISRENDERING_H



#include "sdl_helper.h"
#include <vector>

class TetrisRendering
{
public:
	TetrisRendering();
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Texture *bg;
	SDL_Texture *cube;
	SDL_Texture *gridBox;
	SdlHelper *sdlHelper_;
	void RenderFrame(std::vector<std::vector<bool>> grid);
};

#endif
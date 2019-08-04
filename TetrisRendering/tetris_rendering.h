#ifndef TETRISRENDERING_H
#define TETRISRENDERING_H

#include "sdl_helper.h"
#include <vector>
#include "res_path.h"
#include "color.h"

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
	void RenderText(const std::string &message, Color color, int fontSize);
private:
	std::string _displayText;
	Color _textColor;
	int _fontSize;
};

#endif
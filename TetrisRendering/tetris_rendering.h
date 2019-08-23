#ifndef TETRISRENDERING_H
#define TETRISRENDERING_H

#include "sdl_helper.h"
#include <vector>
#include "res_path.h"
#include "color.h"
#include "../UserInterface/grid.h"
#include "../UserInterface/dimensions.h"
#include "../UserInterface/column.h"

class TetrisRendering
{
public:
	TetrisRendering(Grid* grid);
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Texture *bg;
	SDL_Texture *cube;
	SDL_Texture *gridBox;
	SdlHelper *sdlHelper_;
	void RenderFrame(const Column* column, std::vector<std::vector<bool>> grid);
	void RenderText
	(
		const Column* column,
		const std::string &message,
		Color color,
		int fontSize,
		AlignV vertical = AlignV::aTop,
		AlignH horizontal = AlignH::aLeft
	);
	void RenderColor(const Column* column, Color color);

	void Clear();
	void Render();
	auto grid() & -> Grid* { return _grid; };
private:
	Grid* _grid;
};

#endif
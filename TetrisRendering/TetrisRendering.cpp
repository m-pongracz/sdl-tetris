#include "tetris_rendering.h"

#include "SDL_image.h"
#include "logging.h"
#include "res_path.h"
#include "../GameLogic/game.h"

TetrisRendering::TetrisRendering()
{

	Logging log(&std::cout);
	sdlHelper_ = new SdlHelper(&log);

	//if (SDL_Init(SDL_INIT_VIDEO) != 0) {
	//	log.logSDLError("SDL_Init Error: ");
	//}

	//if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
	//	log.logSDLError("IMG_Init");
	//	SDL_Quit();
	//}

	win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		log.logSDLError("SDL_CreateWindow Error: ");
		SDL_Quit();
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
		SDL_DestroyWindow(win);
		log.logSDLError("SDL_CreateRenderer Error: ");
		SDL_Quit();
	}

	std::string bgImagePath = getResourcePath("img") + "checkered.bmp";
	std::string clipImagePath = getResourcePath("img") + "clip.png";
	std::string cubeImagePath = getResourcePath("img") + "cube.bmp";
	std::string gridBoxImagePath = getResourcePath("img") + "gridbox.bmp";

	bg = sdlHelper_->loadTexture(bgImagePath, ren);
	cube = sdlHelper_->loadTexture(cubeImagePath, ren);
	gridBox = sdlHelper_->loadTexture(gridBoxImagePath, ren);


	if (bg == nullptr || cube == nullptr || gridBox == nullptr) {
		cleanup(bg, cube, gridBox, ren, win);
		SDL_Quit();
	}
}

void TetrisRendering::RenderFrame(std::vector<std::vector<bool>> grid) {

	SDL_RenderClear(ren);

	for (int x = 0; x < Game::gridWidth; ++x) {
		for (int y = 0; y < Game::gridHeight; ++y) {
			sdlHelper_->renderTexture(gridBox, ren, x * 20, y * 20, 20, 20);
			if (grid[x][y] == true) {
				sdlHelper_->renderTexture(cube, ren, x * 20, y * 20, 20, 20);
			}
		}
	}

	SDL_RenderPresent(ren);

}
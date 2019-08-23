#include "tetris_rendering.h"

#include "SDL_image.h"
#include "SDL_ttf.h"
#include "logging.h"

#include "../GameLogic/game.h"

TetrisRendering::TetrisRendering(Grid* grid)
{
	_grid = grid;



	//auto scoreCol = _grid->GetColumnAt(0, 0);
	//_scorePos = _grid->GetColumnPosition(0, 0);
	//_scoreDimensions = Dimensions(scoreCol->width(), scoreCol->height());

	//_scorePos = _grid->GetColumnPosition(0, 0);
	//_scoreDimensions = Dimensions(scoreColumn.width(), scoreColumn.height());

	//_gamePos = _grid->GetColumnPosition(1, 0);
	//_gameDimensions = Dimensions(gameColumn.width(), gameColumn.height());

	Logging log(&std::cout);
	sdlHelper_ = new SdlHelper(&log);

	//if (SDL_Init(SDL_INIT_VIDEO) != 0) {
	//	log.logSDLError("SDL_Init Error: ");
	//}

	//if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
	//	log.logSDLError("IMG_Init");
	//	SDL_Quit();
	//}

	win = SDL_CreateWindow("Tetris", 100, 100, _grid->width(), _grid->height(), SDL_WINDOW_SHOWN);
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

	int bm = SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
	if (bm != 0) {
		log.logSDLError("SDL_SetRenderDrawBlendMode Error: ");
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

void TetrisRendering::RenderFrame(const Column* column, std::vector<std::vector<bool>> grid) {

	auto gamePos = column->coordinates();
	auto gameDimensions = column->dimensions();

	int cubeW = gameDimensions.w() / Game::gridWidth;
	int cubeH = gameDimensions.h() / Game::gridHeight;

	for (int x = 0; x < Game::gridWidth; ++x) {
		for (int y = 0; y < Game::gridHeight; ++y) {
			Point cubeCoords = Point(gamePos.x + x * cubeW, gamePos.y + y * cubeH);
			Dimensions cubeDimensions = Dimensions(cubeW, cubeH);

			sdlHelper_->renderTexture(gridBox, ren, &cubeCoords, &cubeDimensions);
			if (grid[y][x] == true) {
				sdlHelper_->renderTexture(cube, ren, &cubeCoords, &cubeDimensions);
			}
		}
	}

}

void TetrisRendering::RenderText
(
	const Column* column,
	const std::string &message,
	Color color,
	int fontSize,
	AlignV vertical,
	AlignH horizontal
)
{
	Point textPos = column->coordinates();
	Dimensions textDimensions = column->dimensions();

	sdlHelper_->renderText(ren, &textPos, &textDimensions, message, color, fontSize, vertical, horizontal);

	//delete textPos;
	//delete textDimensions;
}

void TetrisRendering::RenderColor(const Column* column, Color color)
{
	Point gamePos = column->coordinates();
	Dimensions gameDimensions = column->dimensions();

	sdlHelper_->renderColor(ren, &gamePos, &gameDimensions, color);

	//delete gamePos;
	//delete gameDimensions;
}

void TetrisRendering::Clear() {
	SDL_RenderClear(ren);
}

void TetrisRendering::Render() {
	SDL_RenderPresent(ren);
}


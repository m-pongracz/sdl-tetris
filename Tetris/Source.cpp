
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "../TetrisRendering/tetris_rendering.h"
#include "../GameLogic/game.h"
//#include "../TetrisRendering/logging.h"

using namespace std;


int main(int argc, char * argv[])
{
	//Logging log(&std::cout);

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		//log.logSDLError("SDL_Init Error: ");
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		//log.logSDLError("IMG_Init");
		SDL_Quit();
	}
	if (TTF_Init() != 0) {
		//logSDLError(std::cout, "TTF_Init");
		SDL_Quit();
	}

	Grid uiGrid = Grid(480, 660);

	Row textRow = Row(0, 100);
	Row gameRow = Row(0, 560);

	Column scoreColumn = Column();
	Column gameColumn = Column(160, 0);
	gameColumn.align = Align::center;
	Column gameColumn2 = Column(180, 0);
	gameColumn2.align = Align::center;


	uiGrid.AddRow(&textRow);
	uiGrid.AddRow(&gameRow);

	textRow.AddColumn(&scoreColumn);

	gameRow.AddColumn(&gameColumn);
	gameRow.AddColumn(&gameColumn2);


	uiGrid.RecalculateGrid();

	TetrisRendering *ren = new TetrisRendering(&uiGrid);

	Game *game = new Game(ren);
	game->Start();
	return 0;
}

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "../TetrisRendering/tetris_rendering.h"
#include "../GameLogic/game.h"
//#include "../TetrisRendering/logging.h"
#include "../UserInterface/grid.h"
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

	Grid uiGrid = Grid(480, 710);

	Row infoRow = Row(0, 50);
	Row textRow = Row(0, 100);
	Row gameRow = Row();


	Column fpsColumn = Column(100,0);
	Column timeColumn = Column();

	Column scoreColumn = Column();

	Column gameColumn = Column();

	
	infoRow.SetMargin(10);
	gameRow.SetMargin(10);
	textRow.SetMargin(10);

	uiGrid.AddRow(&infoRow);
	uiGrid.AddRow(&textRow);
	uiGrid.AddRow(&gameRow);

	infoRow.AddColumn(&timeColumn);
	infoRow.AddColumn(&fpsColumn);

	textRow.AddColumn(&scoreColumn);

	gameRow.AddColumn(&gameColumn);

	uiGrid.RecalculateGrid();

	TetrisRendering *ren = new TetrisRendering(&uiGrid);

	Game *game = new Game(ren);
	game->Start();
	return 0;
}
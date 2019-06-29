//#include <iostream>
//#include <SDL.h>
//#include "res_path.h"
//#include "logging.h"
//#include "sdl_helper.h"
//#include "SDL_image.h"
//#include "game_object.h"
#include "game.h"

using namespace std;

int main(int argc, char * argv[])
{
	//Logging log(&cout);
	//SdlHelper sdlHelper(&log);

	//if (SDL_Init(SDL_INIT_VIDEO) != 0) {
	//	log.logSDLError("SDL_Init Error: ");
	//	return 1;
	//}

	//if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
	//	log.logSDLError("IMG_Init");
	//	SDL_Quit();
	//	return 1;
	//}

	//SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	//if (win == nullptr) {
	//	log.logSDLError("SDL_CreateWindow Error: ");
	//	SDL_Quit();
	//	return 1;
	//}

	//SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//if (ren == nullptr) {
	//	SDL_DestroyWindow(win);
	//	log.logSDLError("SDL_CreateRenderer Error: ");
	//	SDL_Quit();
	//	return 1;
	//}

	//string fgImagePath = getResourcePath("img") + "img.png";
	//string bgImagePath = getResourcePath("img") + "checkered.bmp";
	//string clipImagePath = getResourcePath("img") + "clip.png";
	//string cubeImagePath = getResourcePath("img") + "cube.bmp";
	//string gridBoxImagePath = getResourcePath("img") + "gridbox.bmp";


	//SDL_Texture *bg = sdlHelper.loadTexture(bgImagePath, ren);
	//SDL_Texture *img = sdlHelper.loadTexture(fgImagePath, ren);
	//SDL_Texture *clip = sdlHelper.loadTexture(clipImagePath, ren);
	//SDL_Texture *cube = sdlHelper.loadTexture(cubeImagePath, ren);
	//SDL_Texture *gridBox = sdlHelper.loadTexture(gridBoxImagePath, ren);


	//if (bg == nullptr || img == nullptr || clip == nullptr) {
	//	cleanup(bg, img, clip, ren, win);
	//	SDL_Quit();
	//	return 1;
	//}

	//int w = 640;
	//int h = 480;

	//for (int i = 0; i < 3; ++i) {
	//	SDL_RenderClear(ren);

	//	/*for (int x = 0; x < 640; ++x) {
	//		for (int y = 0; y < 480; ++y) {
	//			sdlHelper.renderTexture(bg, ren, x*20, y*20);
	//		}
	//	}
	//	*/

	//	sdlHelper.renderTexture(bg, ren, 0, 0, w, h, true);

	//	int iW, iH;
	//	SDL_QueryTexture(img, NULL, NULL, &iW, &iH);

	//	sdlHelper.renderTexture(img, ren, (w / 2) - iW / 2, (h / 2) - iH / 2);


	//	SDL_RenderPresent(ren);
	//	SDL_Delay(1000);
	//}

	SDL_Event e;
	bool quit = false;
	int clipNum = 0;

	Game game;
	game.start();

	//while (!quit && false) {
	//	SDL_RenderClear(ren);

	//	sdlHelper.renderTexture(bg, ren, 0, 0, w, h, nullptr, true);

	//	int iW, iH;
	//	SDL_QueryTexture(img, NULL, NULL, &iW, &iH);

	//	sdlHelper.renderTexture(img, ren, (w / 2) - iW / 2, (h / 2) - iH / 2);

	//	SDL_QueryTexture(clip, NULL, NULL, &iW, &iH);
	//	iW = iW / 2;
	//	iH = iH / 2;
	//	SDL_Rect clips[4];
	//	for (int i = 0; i < 4; ++i) {

	//		clips[i].x = i / 2 * iW;
	//		clips[i].y = i % 2 * iH;
	//		clips[i].w = iW;
	//		clips[i].h = iH;
	//	}

	//	while (SDL_PollEvent(&e)) {
	//		if (e.type == SDL_QUIT) {
	//			quit = true;
	//		}
	//		if (e.type == SDL_KEYDOWN) {
	//			switch (e.key.keysym.sym) {
	//			case SDLK_1:
	//				clipNum = 0;
	//				break;
	//			case SDLK_2:
	//				clipNum = 1;
	//				break;
	//			case SDLK_3:
	//				clipNum = 2;
	//				break;
	//			case SDLK_4:
	//				clipNum = 3;
	//				break;
	//			case SDLK_ESCAPE:
	//				quit = true;
	//				break;
	//			default:
	//				break;
	//			}
	//			if (e.type == SDL_MOUSEBUTTONDOWN) {
	//				quit = true;
	//			}
	//		}
	//	}

	//	sdlHelper.renderTexture(clip, ren, 0, 0, iW, iH, &clips[clipNum]);

	//	bool grid[8][14];

	//	GameObject cubeO(CubeType::L);
	//	cubeO.MoveD();
	//	cubeO.MoveD();
	//	cubeO.MoveD();
	//	
	//	int y = 0;
	//	int x = 0;
	//	string line = "";
	//	for (int i = 0; i < sizeof cubeO.footprint_; ++i) {

	//		grid[x + cubeO.X()][y + cubeO.Y()] = cubeO.footprint_[GameObject::index(x, y)];
	//		line += cubeO.footprint_[GameObject::index(x, y)] ? "[X]" : "[ ]";

	//		++x;
	//		if (i != 0 && (i + 1) % GameObject::fprintRows == 0) {
	//			++y;
	//			x = 0;
	//			line += "\n";
	//		};


	//	}
	//	//cout << "------------\n";
	//	//cout << line;

	//	for (int x = 0; x < sizeof grid / sizeof grid[0]; ++x) {
	//		for (int y = 0; y < sizeof grid[0]; ++y) {
	//			sdlHelper.renderTexture(gridBox, ren, x * 20, y * 20, 20, 20);
	//			if (grid[x][y] == true) {
	//				sdlHelper.renderTexture(cube, ren, x * 20, y * 20, 20, 20);
	//			}
	//		}
	//	}

	//	SDL_RenderPresent(ren);
	//}

	/*SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
	if (bmp == nullptr) {
		cleanup(win, ren);
		log.logSDLError("SDL_LoadBMP Error: ");
		SDL_Quit();
		return 1;
	}*/

	//SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
	//SDL_FreeSurface(bmp);
	//if (tex == nullptr) {
	//	cleanup(win, ren, tex);
	//	log.logSDLError("SDL_CreateTextureFromSurface Error: ");
	//	SDL_Quit();
	//	return 1;
	//}

	//for (int i = 0; i < 3; ++i) {
	//	SDL_RenderClear(ren);
	//	SDL_RenderCopy(ren, tex, NULL, NULL);
	//	SDL_RenderPresent(ren);
	//	SDL_Delay(1000);
	//}

	//cleanup(win, ren, tex);


	//cleanup(win, ren, bg, img);
	//SDL_Quit();
	//IMG_Quit();
	return 0;
}
#include "sdl_helper.h"
#include "logging.h"
#include <utility>
#include <string>
#include "SDL_image.h"
Logging *logger;


SdlHelper::SdlHelper()
{
}


SdlHelper::SdlHelper(Logging *_logger)
{
	logger = _logger;
}

SDL_Texture* SdlHelper::loadTexture(const std::string &file, SDL_Renderer *ren) {
	/*SDL_Texture *texture = nullptr;
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	if (loadedImage != nullptr) {
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		if (texture == nullptr) {
			(*logger).logSDLError("CreateTextureFromSurface");
		}
	}
	else {
		(*logger).logSDLError("LoadBMP");
	}
	return texture;*/

	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr) {
		(*logger).logSDLError("LoadTexture");
	}
	return texture;
}

void SdlHelper::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h, SDL_Rect *clip, bool tile) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;

	//if (clip != nullptr) {
	//	dst.w = clip->w;
	//	dst.h = clip->h;
	//}

	if (tile) {
		int iW, iH;
		SDL_QueryTexture(tex, NULL, NULL, &iW, &iH);

		dst.w = iW;
		dst.h = iH;

		int dstXOffset = dst.x;
		int dstYOffset = dst.y;

		for (int x = 0; x < h; ++x) {
			for (int y = 0; y < w; ++y) {
				dst.x = (x * iW) + dstXOffset;
				dst.y = (y * iH) + dstYOffset;
				SDL_RenderCopy(ren, tex, clip, &dst);
			}
		}
	}
	else {
		SDL_RenderCopy(ren, tex, clip, &dst);
	}
}

void SdlHelper::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip, bool tile) {
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	renderTexture(tex, ren, x, y, w, h, clip, tile);
}
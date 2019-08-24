#include "sdl_helper.h"
#include "logging.h"
#include <utility>
#include <string>
#include <SDL_image.h>

Logging* logger;


SdlHelper::SdlHelper(Logging* _logger)
{
	const std::string fontPath = getResourcePath("fonts") + "arial.ttf";

	font = TTF_OpenFont(fontPath.c_str(), 48);

	logger = _logger;
}

SDL_Texture* SdlHelper::loadTexture(const std::string& file, SDL_Renderer* ren) {

	SDL_Texture* texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr) {
		(*logger).logSDLError("LoadTexture");
	}
	return texture;
}

void SdlHelper::renderTexture(SDL_Texture* tex, SDL_Renderer* ren, Point* coords, Dimensions* dimensions, SDL_Rect* clip, bool tile) {
	SDL_Rect dst;
	dst.x = coords->x;
	dst.y = coords->y;
	dst.w = dimensions->w();
	dst.h = dimensions->h();


	if (tile) {
		int iW, iH;
		SDL_QueryTexture(tex, NULL, NULL, &iW, &iH);

		dst.w = iW;
		dst.h = iH;

		int dstXOffset = dst.x;
		int dstYOffset = dst.y;

		for (int x = 0; x < dst.h; ++x) {
			for (int y = 0; y < dst.w; ++y) {
				dst.x = (x * iW) + dstXOffset;
				dst.y = (y * iH) + dstYOffset;
				SDL_RenderCopy(ren, tex, clip, &dst);
			}
		}
	}
	else {
		SDL_RenderCopy(ren, tex, clip, &dst);
	}

	//SDL_DestroyTexture(tex);
}

void SdlHelper::renderTexture(SDL_Texture* tex, SDL_Renderer* ren, Point* coords, SDL_Rect* clip, bool tile) {
	Dimensions d = Dimensions(0, 0);
	int w = d.w();
	int h = d.h();

	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	renderTexture(tex, ren, coords, &d, clip, tile);
}

void SdlHelper::renderText(SDL_Renderer* ren, Point* coords, Dimensions* dimensions, const std::string& message,
	Color color, int fontSize, AlignV vertical, AlignH horizontal)
{
	SDL_Color sdlColor = { color.R, color.G, color.B, color.A };
	if (font == nullptr) {

		return;
	}

	SDL_Surface* surf = TTF_RenderText_Blended(font, message.c_str(), sdlColor);
	if (surf == nullptr) {
		TTF_CloseFont(font);

		return;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surf);
	if (texture == nullptr) {
		return;
	}

	//Querying texture for its true size and overriding dimensions so they match the texture
	int w, h;
	//w and h serve as variables for out in c#
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	Point alignedCoords = Point(coords->x, coords->y);

	switch (vertical) {
	case AlignV::aCenter: {
		alignedCoords.y = coords->y + (dimensions->h() / 2) - (h / 2);
		break;
	}
	case AlignV::aBottom: {
		alignedCoords.y = coords->y + dimensions->h() - h;
		break;
	}
	}

	switch (horizontal) {
	case AlignH::aMiddle: {
		alignedCoords.x = coords->x + (dimensions->w() / 2) - (w / 2);
		break;
	}
	case AlignH::aRight: {
		alignedCoords.x = coords->x + dimensions->w() - w;
		break;
	}
	}

	Dimensions queriedDimensions = Dimensions(w, h);

	renderTexture(texture, ren, &alignedCoords, &queriedDimensions);

	SDL_FreeSurface(surf);
	SDL_DestroyTexture(texture);


}

void SdlHelper::renderColor(SDL_Renderer* ren, Point* coords, Dimensions* dimensions, Color color)
{
	SDL_Color sdlColor = { color.R, color.G, color.B, color.A };

	SDL_Surface* surf = SDL_CreateRGBSurface(0, dimensions->w(), dimensions->h(), 32, 0, 0, 0, 0);
	SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, sdlColor.r, sdlColor.g, sdlColor.b));

	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surf);

	if (color.A != 255) {
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(texture, sdlColor.a);
	}
	if (texture == nullptr) {
		return;
	}

	//Querying texture for its true size and overriding dimensions so they match the texture
	int w, h;
	//w and h serve as variables for out in c#
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	Dimensions queriedDimensions = Dimensions(w, h);

	renderTexture(texture, ren, coords, &queriedDimensions);

	SDL_FreeSurface(surf);
	SDL_DestroyTexture(texture);
}
#ifndef SDL_HELPER
#define SDL_HELPER

#include <string>
#include <SDL.h>
#include "logging.h"
#include "SDL_ttf.h"
#include "res_path.h"
#include "point.h"
#include "dimensions.h"


class SdlHelper
{
public:
	SdlHelper(Logging *_logger);
	SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, Point* coords, SDL_Rect *clip = nullptr, bool tile = false);
	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, Point* coords, Dimensions* dimensions, SDL_Rect *clip = nullptr, bool tile = false);
	void renderText(SDL_Renderer *ren, Point* coords, Dimensions* dimensions, const std::string &message, SDL_Color color, int fontSize);
	TTF_Font *font;
};

template<typename T, typename... Args>
void cleanup(T *t, Args&&... args) {
	cleanup(t);
	cleanup(std::forward<Args>(args)...);
}
template<>
inline void cleanup<SDL_Window>(SDL_Window *win) {
	if (!win) {
		return;
	}
	SDL_DestroyWindow(win);
}
template<>
inline void cleanup<SDL_Renderer>(SDL_Renderer *ren) {
	if (!ren) {
		return;
	}
	SDL_DestroyRenderer(ren);
}
template<>
inline void cleanup<SDL_Texture>(SDL_Texture *tex) {
	if (!tex) {
		return;
	}
	SDL_DestroyTexture(tex);
}
template<>
inline void cleanup<SDL_Surface>(SDL_Surface *surf) {
	if (!surf) {
		return;
	}
	SDL_FreeSurface(surf);
}
#endif 


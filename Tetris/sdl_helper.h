#ifndef SDL_HELPER
#define SDL_HELPER

#include <string>
#include <SDL.h>
#include "logging.h"

class SdlHelper
{
public:
	SdlHelper();
	SdlHelper(Logging *_logger);
	SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip = nullptr, bool tile = false);
	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h, SDL_Rect *clip = nullptr, bool tile = false);
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


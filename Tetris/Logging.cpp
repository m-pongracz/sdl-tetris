#include "logging.h"
#include <SDL.h>
//#include <utility>
#include <string>
#include <ostream>

std::ostream *os;

Logging::Logging(std::ostream *_os)
{
	os = _os;
}

void Logging::logSDLError(const std::string &msg) {
	*os << msg << " error: " << SDL_GetError() << std::endl;
}

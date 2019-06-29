#include <SDL.h>
#include <utility>
#include <string>

class Logging2
{
private:
	std::ostream *os;

public:
	Logging2(std::ostream *_os) {
		os = _os;
	}

	void logSDLError(std::ostream &os, const std::string &msg) {
		os << msg << " error: " << SDL_GetError() << std::endl;
	}
};
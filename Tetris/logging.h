#ifndef LOGGING_H
#define LOGGING_H

#include <SDL.h>
#include <string>
#include <iostream>

class Logging
{

public:
	Logging(std::ostream *_os);
	void logSDLError(const std::string &msg);	
};

#endif
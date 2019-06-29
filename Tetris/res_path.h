#ifndef RES_PATH_H
#define RES_PATH_H

#include <iostream>
#include <string>
#include <SDL.h>

std::string getResourcePath(const std::string &subDir = "") {
#if defined _WIN64
	std::string BIN_FOLDER = "x64";
	const char SEP = '\\';
#elif defined _WIN32
	std::string BIN_FOLDER = "x86";
	const char SEP = '\\';
#else 
	const char SEP = '/';
#endif

	static std::string baseRes;
	if (baseRes.empty()) {
		char *basePath = SDL_GetBasePath();
		if (basePath) {
			baseRes = basePath;
			SDL_free(basePath);
		}
		else {
			std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
			return "";
		}

		size_t pos = baseRes.rfind(BIN_FOLDER);
		baseRes = baseRes.substr(0, pos) + "res" + SEP;
	}

	return subDir.empty() ? baseRes : baseRes + subDir + SEP;
}

#endif
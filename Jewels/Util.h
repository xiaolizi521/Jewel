#ifndef _UTIL_H_
#define _UTIL_H_

#include "defines.h"
#include "Vertex.h"
#include "Rect.h"
#include <iostream>
#include "SDL.h"

std::ostream& operator<<(std::ostream& os, const Rect& obj);

std::ostream& operator<<(std::ostream& os, const Vertex& obj);

std::ostream& operator<<(std::ostream& os, const JewelType& obj);

SDL_Surface * makeRGBSurface(int iW, int iH);

#endif
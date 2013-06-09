#include "Util.h"

std::ostream& operator<<(std::ostream& os, const JewelType& obj)
{
  switch(obj)
  {
    case JEWELTYPE_RED:
    {
      os << "RED";
    }
    break;
    case JEWELTYPE_BLUE:
    {
      os << "BLUE";
    }
    break;
    case JEWELTYPE_AMBER:
    {
      os << "AMBER";
    }
    break;
    case JEWELTYPE_EMERALD:
    {
      os << "EMERALD";
    }
    break;
    case JEWELTYPE_PURPLE:
    {
      os << "PURPLE";
    }
    break;
    case JEWELTYPE_NONE:
    {
      os << "NONE";
    }
    break;
  }
  return os;
}

SDL_Surface * makeRGBSurface(int iW, int iH)
{
  // Create RGB Surface 
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  int rmask = 0xff000000;
  int gmask = 0x00ff0000;
  int bmask = 0x0000ff00;
  int amask = 0x000000ff;
#else
  int rmask = 0x000000ff;
  int gmask = 0x0000ff00;
  int bmask = 0x00ff0000;
  int amask = 0xff000000;
#endif
  SDL_Surface * surface = SDL_CreateRGBSurface(SDL_SWSURFACE, iW, iH, 
                                    32, rmask, gmask, bmask, amask);
  return surface;
}
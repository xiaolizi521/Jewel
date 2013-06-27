#include "Util.h"

std::ostream& operator<<(std::ostream& os, const Rect& obj)
{
  os << "{" << obj.x << "," << obj.y << " w: " << obj.w << " h: " << obj.h << " }";
  return os;
}

std::ostream& operator<<(std::ostream& os, const Vertex& obj)
{
  os << "[" << obj.x << "," << obj.y << "]";
  return os;
}

std::ostream& operator<<(std::ostream& os, const JewelType& obj)
{
  switch(obj)
  {
    case JEWELTYPE_RED:
    {
      os << "[R]";
    }
    break;
    case JEWELTYPE_BLUE:
    {
      os << "[B]";
    }
    break;
    case JEWELTYPE_AMBER:
    {
      os << "[Y]";
    }
    break;
    case JEWELTYPE_EMERALD:
    {
      os << "[G]";
    }
    break;
    case JEWELTYPE_PURPLE:
    {
      os << "[P]";
    }
    break;
    case JEWELTYPE_NONE:
    {
      os << "[0]";
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
#ifndef _TEXTURE_MGR_H_
#define _TEXTURE_MGR_H_

#include <map>
#include "SDL.h"

typedef SDL_Surface* HTEXTURE;

class TextureMgr
{

public:
  bool LoadTexture(const char *pFileName, int ID);
  HTEXTURE GetTexture(int ID);

  // Singleton pattern
  static TextureMgr* Instance()
  {
    return &m_TextureMgr;
  }
private:
  static TextureMgr m_TextureMgr;
  std::map<int, HTEXTURE> textures;
};


#endif
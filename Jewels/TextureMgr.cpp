#include "TextureMgr.h"
#include "SDL_image.h"
#include <iostream>
#include "defines.h"

TextureMgr TextureMgr::m_TextureMgr;

/************************************************/
bool TextureMgr::LoadTexture(const char * pFileName, int id)
{
  HTEXTURE tex;
  if((tex = IMG_Load(pFileName)) == NULL)
	{
	  std::cout << "IMG ERROR:" << IMG_GetError() << std::endl;
	  return false;
	}
  else
  {
    textures.insert(std::pair<int,HTEXTURE>(id,tex));
  }
  return true;
}

/************************************************/
HTEXTURE TextureMgr::GetTexture(int ID)
{
  std::map<int, HTEXTURE>::const_iterator results = textures.find(ID);
  if(results == textures.end() )
  {
    return NULL;
  }
  else
  {
    return results->second;
  }
}
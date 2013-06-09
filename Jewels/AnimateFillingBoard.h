#ifndef _ANIMATE_FILLING_BOARD_H_
#define _ANIMATE_FILLING_BOARD_H_

#include "SDL.h"
#include "State.h"
#include "Game.h"
#include "Sprite.h"
#include "DroppingJewels.h"
#include "TextureMgr.h"
#include <vector>
#include "defines.h"

class AnimateFillingBoard: public State<Game>
{
public:
  void Enter(Game*);
	void Exit(Game*) ;	
	void HandleEvents(Game * game);
	void Update(Game * game);
	void Draw(Game* game);

  void Pause(){}
  void Resume(){}

  // Singleton pattern
  static AnimateFillingBoard* Instance()
  {
    return &m_AnimateFillingBoard;
  }

protected:
  static AnimateFillingBoard m_AnimateFillingBoard;
	AnimateFillingBoard();

  void CreateSprites(Game *pGame);
  
private:
  
  int TimeLeft(void);

  std::vector<DroppingJewels* > sprites;
  Sprite* pWiper;
  SDL_Surface * pGameScreen;
  int iStart;
  int iNextTime;
  int iCompleted;
};

#endif
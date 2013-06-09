#ifndef _NEWGAMEANIM_H_
#define _NEWGAMEANIM_H_

#include "SDL.h"
#include "State.h"
#include "Sprite.h"
#include "Game.h"

class StartAnim : public State<Game>
{
public:
  void Enter(Game*);
	void Exit(Game*);
	
	void HandleEvents(Game * game);
	void Update(Game * game);
	void Draw(Game* game);

  // Not used
  void Pause(){}
  void Resume(){}

  // Singleton pattern
  static StartAnim* Instance()
  {
    return &m_StartAnim;
  }

protected:
  static StartAnim m_StartAnim;
	StartAnim() {}

  // Store a pointer to the game
  Game * pGame;

  // Some internal variables
  int iCurColumn;
  int iCurRow;

  int iAnimSpeed; // a jewel is displayed every iAnimSpeed milliseconds.
  int iOldTime;
  int iCurrentTime;
  
  bool bAnimDone;
};

#endif
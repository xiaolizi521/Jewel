#ifndef _DISAPPEAR_AND_DROP_TEST_H_
#define _DISAPPEAR_AND_DROP_TEST_H_

#include "SDL.h"
#include "State.h"
#include "Sprite.h"
#include "Game.h"

class DisappearAndDropTest : public State<Game>
{
public:
  void Enter(Game*);
	void Exit(Game*) ;
	
	void HandleEvents(Game * game);
	void Update(Game * game);
	void Draw(Game* game);

  // Not used
  void Pause(){}
  void Resume(){}

  // Singleton pattern
  static DisappearAndDropTest* Instance()
  {
    return &m_DisappearAndDropTest;
  }

protected:
  static DisappearAndDropTest m_DisappearAndDropTest;
  DisappearAndDropTest(){}
private:
  bool bNewChoice;
  bool bCalculateDrop;

  int iChoice;
  Sprite * first;
  Sprite * second;

  std::vector<std::pair<int,int>> chosen;
  std::vector<std::pair<int,int>>::reverse_iterator it;
};

#endif
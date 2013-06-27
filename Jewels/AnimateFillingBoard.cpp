#include "AnimateFillingBoard.h"
#include "Game.h"
#include "GameObject.h"
#include <iostream>
#include "Util.h"
#include "DisappearAndDropTests.h"

/*************************************************************************/
AnimateFillingBoard::AnimateFillingBoard():
  sprites(NUM_COLUMNS),
  iStart(0),
  iNextTime(0),
  iCompleted(0)
{

}

/*************************************************************************/

void AnimateFillingBoard::Enter(Game* pGame)
{
  pGame->CreateColumnsForDropping();
  
  pWiper = pGame->GetGridWiper();
}

/*************************************************************************/

void AnimateFillingBoard::Exit(Game* pGame)
{

}

/*************************************************************************/

void AnimateFillingBoard::HandleEvents(Game * pGame)
{
  SDL_Event event;
  
  if(SDL_PollEvent(&event))
  {
    
  }
}

/*************************************************************************/

int AnimateFillingBoard::TimeLeft(void)
{
  int iNow = SDL_GetTicks();
  if ( iNextTime <= iNow ) {
      iNextTime = iNow+TIME_BETWEEN_DROPS;
      return(0);
  }
  return(iNextTime-iNow);
}

/*************************************************************************/

void AnimateFillingBoard::Update(Game * pGame)
{
 
  int iElapsed = pGame->GetElapsedTime();


  // update each of the dropping jewels.
  pGame->UpdateAllDropColumns(iElapsed);

}

/*************************************************************************/

void AnimateFillingBoard::Draw(Game* pGame)
{

  if(pGame->AllColumnsDropped())
  {
    pGame->PrintBoard();

    // force the board to redraw
    pGame->SetBoardRedraw(true);

    pGame->ChangeState(DisappearAndDropTest::Instance());
  }
  else
  {
    pWiper->Blit(pGame->GetGameScreen(), GRID_START_X, GRID_START_Y);

    pGame->DrawAllDropColumns();
  }
}

/*************************************************************************/
AnimateFillingBoard AnimateFillingBoard::m_AnimateFillingBoard;
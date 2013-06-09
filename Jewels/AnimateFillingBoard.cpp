#include "AnimateFillingBoard.h"
#include "Game.h"
#include "GameObject.h"
#include <iostream>
#include "Util.h"
#include "Choosing.h"

/*************************************************************************/
AnimateFillingBoard::AnimateFillingBoard():
  sprites(NUM_COLUMNS),
  iStart(0),
  iNextTime(0),
  iCompleted(0)
{

}

/*************************************************************************/

void AnimateFillingBoard::CreateSprites(Game* pGame)
{
  pGame->CreateColumnsForDropping();
  
  for(int i = 0; i < NUM_COLUMNS; i++)
  {   
    std::vector<JewelType> vj = pGame->GetDroppingColumn(i);
    std::vector<Sprite *> vs = pGame->MakeSpritesForDropping(vj);
    std::vector<Vertex> vv = pGame->GetDropCoords(i);
    std::vector<Vertex> vt = pGame->GetDropTargetCoords(i);
    
    sprites[i] = new DroppingJewels(pGame->GetGameScreen(), vs, vv, vt, GRID_START_Y);

    sprites[i]->SetVelocity(0.0, DROP_SPEED);
  }

  pWiper = pGame->GetGridWiper();
}

/*************************************************************************/

void AnimateFillingBoard::Enter(Game* pGame)
{
  
  CreateSprites(pGame);
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

  if(iStart < 1 && !TimeLeft())
  {
    sprites[iStart]->Start();
    iStart++;
  }

  for(int i = 0; i < 2; i++)
  {
    if(sprites[i]->Completed())
    {
      //pGame->InsertDroppedJewels(i);
      //iCompleted++;
    }
    else
    {
      sprites[i]->Update(iElapsed);
    }
  }

  if(NUM_COLUMNS == iCompleted)
  {
    pGame->SetBoardRedraw(true);
    std::cout << "DONE!";
  }
}

/*************************************************************************/

void AnimateFillingBoard::Draw(Game* pGame)
{
  
  pWiper->Blit(pGame->GetGameScreen(), GRID_START_X, GRID_START_Y);

//  if(NUM_COLUMNS == iCompleted)
//  {
//    pGame->ChangeState(Choosing::Instance());
 // }
//  else
  {
    for(int i = 0; i < 2; i++)
    {
      sprites[i]->Draw();
    }
  }

  
}

/*************************************************************************/
AnimateFillingBoard AnimateFillingBoard::m_AnimateFillingBoard;
#include "StartAnim.h"
#include <iostream>
#include "defines.h"
#include "Choosing.h"

void StartAnim::Enter(Game* pGame)
{
  // Initialise our vars
  // to perform a simple animation to show the jewels one by one
  iCurColumn = 0;
  iCurRow = 0;
  iAnimSpeed = 30;
  iOldTime = 0;
}

void StartAnim::Exit(Game* pGame)
{
  std::cout << "StartAnim Exit Successful\n";
}

// Just pressing the mouse button will start the game 
void StartAnim::HandleEvents(Game * pGame)
{

}

void StartAnim::Update(Game* pGame)
{
  if(!bAnimDone)
  {
    // Get time elapsed since last update.
    iCurrentTime = SDL_GetTicks();
    //std::cout << "ticks " << iCurrentTime << "\n";

    if((iCurrentTime - iOldTime) > iAnimSpeed)
    {
      // round iOldtime down to last frame time.
      iOldTime = iCurrentTime/iAnimSpeed * iAnimSpeed;
      std::cout << "iOldTime " << iOldTime << "\n";
      if(iCurRow == NUM_ROWS)
      {
        bAnimDone = true;
        pGame->ChangeState(Choosing::Instance());
      }
      else
      {
        std::cout << "Showing slot! " << iCurColumn << ", " << iCurRow << "\n";
        pGame->ShowSlot(iCurColumn, iCurRow);
        iCurColumn++;
        if(iCurColumn == NUM_COLUMNS)
        {
          iCurRow++;
          iCurColumn = 0;
        }
      }
    }
  }
  else
  {
    
  }
}

// Blit any sprites for this state
void StartAnim::Draw(Game *pGame)
{
  
}

StartAnim StartAnim::m_StartAnim;
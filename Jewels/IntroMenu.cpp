#include "IntroMenu.h"
#include <iostream>
#include "defines.h"
#include "StartAnim.h"

void IntroMenu::Enter(Game* pGame)
{
  // Create sprites
  HTEXTURE menu = TextureMgr::Instance()->GetTexture(STARTMENU);
  intro = new Sprite(menu, 0, 0, menu->w, menu->h);

  std::cout << "IntroMenu Init successful\n";
}

void IntroMenu::Exit(Game* pGame)
{
  // Blit the background to get rid of the menu
  pGame->DrawBackground();
}

// Just pressing the mouse button will start the game 
void IntroMenu::HandleEvents(Game * pGame)
{
  SDL_Event event;
  
  if(SDL_PollEvent(&event))
  {
    std::cout << "IntroMenu handle event\n";
    switch(event.type)
	  {
      case SDL_MOUSEBUTTONDOWN:
        std::cout << "Mouse button pressed at (" << event.button.x << "," << event.button.y << ")\n";
        pGame->ChangeState(StartAnim::Instance());
        break;
      default:
        break;
	  }
  }
}

void IntroMenu::Update(Game * engine)
{
  //std::cout << "IntroMenu::Update\n";  
}

// Blit any sprites for this state
void IntroMenu::Draw(Game *pGame)
{
  intro->Blit(pGame->GetScreen(), INTRO_MENU_X, INTRO_MENU_Y);
}

IntroMenu IntroMenu::m_IntroMenu;
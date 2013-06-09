#include "SDL.h"
#include "Engine.h"
#include "State.h"
#include <iostream>
#include "Sprite.h"
#include "SDL_image.h"

Engine::Engine()
{

}

void Engine::Start(const char* title, int width, int height, bool fullscreen)
{ 
	int flags = 0;

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_WM_SetCaption(title, title);

	//    load support for the JPG and PNG image formats
    flags=IMG_INIT_JPG|IMG_INIT_PNG;
    int initted=IMG_Init(flags);
    if((initted&flags) != flags) {
     std::cout << "IMG_Init: Failed to init required jpg and png support!\n";
     std::cout << "IMG_Init:" << IMG_GetError();
    // handle error
    }

	if( fullscreen )
	{
	  flags = SDL_FULLSCREEN;
	}
	
	m_pCanvas = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);

	m_bFullscreen = fullscreen;

	m_bRunning = true;

  m_pGame = new Game(m_pCanvas);

	std::cout << "Engine Initialised" << std::endl;

	while(Running())
	{
	  EngineLoop();
	}

	// cleanup the Engine
	CleanUp();
}


void Engine::EngineLoop()
{
  HandleEvents();
  Update();
  Draw();
}

void Engine::HandleEvents()
{
  m_pGame->HandleEvents(this);
}


void Engine::Update()
{
  //std::cout << "Engine::Update()" << std::endl;
  m_pGame->Update(this);
}

void Engine::Draw()
{
  m_pGame->Draw();
  SDL_Flip(m_pCanvas);
}

void Engine::CleanUp()
{
  // shutdown SDL
  SDL_Quit();
}
 
bool Engine::Running()
{
  return m_bRunning;
}

void Engine::Quit()
{
  m_bRunning = false;
}



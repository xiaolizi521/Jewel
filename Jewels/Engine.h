#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "State.h"
#include "SDL.h"
#include "Sprite.h"
#include "Game.h"
#include <deque>



class Engine
{
public:
	
	Engine();
	void Start(const char* title, int width, int height, bool fullscreen);
	void Update();
	
	void EngineLoop();
	void Draw();
	void CleanUp();
	bool Running();
	void HandleEvents();
	void Quit();
	
	SDL_Surface * GetScreen() {		return m_pCanvas; }
	
private:

	Game * m_pGame;
	SDL_Surface* m_pCanvas;
	bool m_bRunning;
	bool m_bFullscreen;
	
};

#endif
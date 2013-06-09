#ifndef _GAME_H_
#define _GAME_H_

///////////////////////////////////////////////////////////////////////////////
//
// author: bithika mookherjee
// email:  thumbelina@gmail.com
// date:   2013-06-09
// 
///////////////////////////////////////////////////////////////////////////////

#include "SDL.h"
#include "Sprite.h"
#include "defines.h"
#include "Rect.h"
#include "State.h"
#include "RNG.h"
#include "Vertex.h"
#include <vector>

class Engine;

class Game
{
public:
  Game(SDL_Surface * pSurface);

  void HandleEvents(Engine* pEngine);
	void Update(Engine* pEngine);
	void Draw();

  void ChangeState(State<Game>* state); // new function
	void PushState(State<Game>* state); // new function
	void PopState();


  // Jewel Game specific functions
  void InitialiseBoardCoordinates();
  void InitialiseBoardSquares();
  void InitialiseBoard();
  
  bool MouseInGrid(int iScreenX, int iScreenY, int * col, int * row);

  void PutJewel(int i, int j, JewelType t);
  void InsertDroppedJewels(int iWhichColumn);
  
  void CreateColumnsForDropping();
  std::vector<JewelType> GetDroppingColumn(int iWhichColumn);
  std::vector<Sprite *>  MakeSpritesForDropping(std::vector<JewelType>& drop);
  std::vector<Vertex> GetDropCoords(int iWhich);
  std::vector<Vertex> GetDropTargetCoords(int iWhich);

  // Swapping
  bool PrepareToSwap(std::pair<int,int>&, std::pair<int,int>&);

  int GetCoordX(int col, int row){ return coords[col][row].x; }
  int GetCoordY(int col, int row){ return coords[col][row].y; }

  std::vector<Sprite*> GetJewelSprites();
  void CreateJewelSprites();
  void CreateBackgroundSprites();
  Sprite * GetGridWiper();

  // Drawing functions
  void SetBoardRedraw(bool);
  void DrawBoard();
  void DrawBackground();

  int  GetElapsedTime();

  SDL_Surface * GetGameScreen() { return pGameScreen; }

private:
  std::vector<State<Game>*> states;
  SDL_Surface * pGameScreen;
  RandomNumberGenerator * rng;

  // Timing
  int iCurrentTime;
  int iFrameTime;

  // Rectangle defining grid area
  Rect gridarea;

  // Each square in the grid can be defined using a rect.
  // Used to translate mouse presses.
  std::vector<std::vector<Rect>> squares;

  // The grid coordinates are stored in a vector of vector<Vertex>
  // coords are given as the centre of each slot.
  std::vector<std::vector<Vertex>> coords;

  // The board is a grid of JewelTypes.
  std::vector<std::vector<JewelType>> board; 

  // Columns of jewels type and sprites - used for animating drops
  std::vector<std::vector<JewelType>> dropColumns;

  // Sprites 
  std::vector<Sprite *> jewelSprites;
  Sprite * pBkg;
  Sprite * pScoreSprite;
  Sprite * pTimeLeftSprite;
  Sprite * pMarker;
  Sprite * pEmpty;
  Sprite * pGridWiper;

  // Drawing 
  SDL_Surface * pBoardImage;
  bool bBackgroundNeedsRedraw;
  bool bBoardNeedsRedraw;
};

#endif
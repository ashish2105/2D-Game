#ifndef HUD__H
#define HUD__H
#include <SDL.h>
#include<string>
#include<stdint.h>
#include "drawable.h"
#include "clock.h"
#include "ioMod.h"



class Hud {
public:
  static Hud& getInstance();  
  ~Hud();
  void displayHud() const;
  void startHud() const;
  void endHud() const;
  void lostHud() const;
  Hud(const Hud&)= delete;
  Hud& operator=(const Hud&)=delete;
private:

  const int width;
  const int height;
  const int width1;
  const int height1;
  int x;
  int y;
  int x1;
  int y1;
  SDL_Renderer* r;
  SDL_Rect Rectangle;
  SDL_Rect Rectangle1;
  Hud();
  };
#endif



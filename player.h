#ifndef PLAYER__H
#define PLAYER__H
#include <string>
#include <list>
#include <cmath>
#include "twowayPlayer.h"
class SmartSprite;

class Player : public TwoWayPlayer {
public:
  Player(const std::string& , const std::string&);
  Player(const Player&);  
  Player& operator=(const Player&);
  void collided() { collision = true; }
  void missed() { collision = false; }
  void right();
  void left();
  void up();
  void down();
  void stop();
  void update(Uint32 ticks);
  void attach( SmartSprite* o ) { observers.push_back(o); } 
  void detach( SmartSprite* o );


protected:
  std::list<SmartSprite*> observers;
private:
  bool collision;
  Vector2f initialVelocity;
};
#endif

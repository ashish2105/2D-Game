#ifndef SMARTSPRITE__H
#define SMARTSPRITE__H
#include <string>
#include "twowaySprite.h"

class ExplodingSprite;
class SmartSprite : public TwoWaySprite {
public:
  SmartSprite(const std::string&, const std::string&, const Vector2f& pos, int w, int h);
  SmartSprite(const SmartSprite&);
  SmartSprite& operator=(const SmartSprite&);
  ~SmartSprite();
  void draw() const;

  virtual void update(Uint32 ticks);
  void setPlayerPos(const Vector2f& p) { playerPos = p; }

  virtual void explode();

private:
  enum MODE {NORMAL, EVADE};
  Vector2f playerPos;
  int playerWidth;
  int playerHeight;
  MODE currentMode;
  float safeDistance;
  ExplodingSprite* explosion;

  void goLeft();
  void goRight();
  void goUp();
  void goDown();
};
#endif

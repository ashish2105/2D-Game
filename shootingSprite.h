#ifndef SHOOTINGSPRITE_H
#define SHOOTINGSPRITE_H

#include <string>
#include <iostream>
#include <list>
#include "player.h"
#include "bullet.h"
#include "bullets.h"

class ExplodingSprite;

class ShootingSprite : public Player {
public:
  ShootingSprite(const std::string& n, const std::string& t);
  ShootingSprite(const ShootingSprite& s);
  ~ShootingSprite();
  virtual void update(Uint32 ticks);
  virtual void draw() const;
  bool collide(const Drawable* obj) const;
  void shootRight();
  void shootLeft();
  unsigned int bulletCount() const { return bullets.bulletCount(); }
  unsigned int freeCount()  const { return bullets.freeCount(); }
  virtual void explode();
protected:
  
  ShootingSprite& operator=(const ShootingSprite& s);
private:
  std::string bulletName;
  Bullets bullets;
  float minSpeed;
  float bulletInterval;
  float timeSinceLastFrame;
  ExplodingSprite* explosion;
};
#endif

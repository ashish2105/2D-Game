#ifndef BULLETS_H
#define BULLETS_H

#include <list>
#include "bullet.h"

class CollisionStrategy; 

class Bullets {
public:
  Bullets(const std::string&);
  Bullets(const Bullets&);
  ~Bullets();
  void draw() const;
  void update(Uint32 ticks);
  void shoot(const Vector2f& pos, const Vector2f& vel);
  unsigned int bulletCount() const { return bulletList.size(); }
  unsigned int freeCount()  const { return freeList.size(); }
  bool shooting() const { return !bulletList.empty(); }
  bool collided(const Drawable*) const;
  Bullets& operator=(const Bullets&); 
private:
  std::string name;
  Vector2f myVelocity;
  mutable std::list<Bullet> bulletList; 
  mutable std::list<Bullet> freeList;   
  CollisionStrategy* strategy;   
};
#endif

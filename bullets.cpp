#include <iostream>
#include <sstream>
#include <cmath>
#include "ioMod.h"
#include "gamedata.h"
#include "bullets.h"
#include "collisionStrategy.h"




Bullets::~Bullets() {
delete strategy;
}

Bullets::Bullets(const std::string& n) :
  name(n), 
  myVelocity(Gamedata::getInstance().getXmlInt(n+"/speedX"),
              Gamedata::getInstance().getXmlInt(n+"/speedY")
              ),
  bulletList(),
  freeList(),
  strategy(NULL)
{
  std::string sName = Gamedata::getInstance().getXmlStr(name+"/strategy");
  if ( sName == "midpoint" ) strategy = new MidPointCollisionStrategy;
  else if ( sName == "rectangular" ) strategy = new RectangularCollisionStrategy;
  else if ( sName == "perpixel" ) strategy = new PerPixelCollisionStrategy;
}


Bullets::Bullets(const Bullets& b) :
  name(b.name),
  myVelocity(b.myVelocity),
  bulletList(b.bulletList), 
  freeList(b.freeList),
  strategy(b.strategy)
{ }


 Bullets& Bullets::operator=(const Bullets& s)
  {
    name=s.name;
    myVelocity=s.myVelocity;
    bulletList=s.bulletList; 
    freeList=s.freeList;
    strategy=s.strategy;
    return *this;
  }

    void Bullets::shoot(const Vector2f& position, const Vector2f& velocity) {
    if ( freeList.empty() ) {
      Bullet b(name);
      b.setPosition( position );
      b.setVelocity( velocity );
      bulletList.push_back( b );
    }
    else {
      Bullet b = freeList.front();
      freeList.pop_front();
      b.reset();
      b.setVelocity(velocity);
      b.setPosition(position);
      bulletList.push_back( b );
    }
}

bool Bullets::collided(const Drawable* obj) const {
  for (const auto& bullet : bulletList) {
    if ( strategy->execute(bullet, *obj) ) {
      return true;
    }
  }
  return false;
}



void Bullets::draw() const { 
  for (const auto& bullet : bulletList ) {
    bullet.draw();
  }
}

void Bullets::update(Uint32 ticks) { 
  std::list<Bullet>::iterator ptr = bulletList.begin();
  while (ptr != bulletList.end()) {
    ptr->update(ticks);
    if (ptr->goneTooFar()) {  // Check to see if we should free a Bullet
      freeList.push_back(*ptr);
      ptr = bulletList.erase(ptr);
    }   
    else ++ptr;
  }
}





#include <cmath>
#include <random>
#include <functional>
#include "smartSprite.h"
#include "gamedata.h"
#include "renderContext.h"
#include "explodingSprite.h"

float distance(float x1, float y1, float x2, float y2) {
  float x = x1-x2;
  float y = y1-y2;
  return hypot(x, y);
}


SmartSprite::~SmartSprite( ) { if (explosion) delete explosion; }

void SmartSprite::goLeft()  { setVelocityX( -fabs(getVelocityX()) ); 
    setName(leftmoment);
    flipImage( RenderContext::getInstance()->getImages(leftmoment) );  }
void SmartSprite::goRight() { setVelocityX( fabs(getVelocityX()) );
    setName(rightmoment);
    flipImage( RenderContext::getInstance()->getImages(rightmoment) );  }
void SmartSprite::goUp()    { setVelocityY( -fabs(getVelocityY()) ); }
void SmartSprite::goDown()  { setVelocityY( fabs(getVelocityY()) );  }


SmartSprite::SmartSprite(const std::string& name, const std::string& name1,const Vector2f& pos, 
  int w, int h) :
  TwoWaySprite(name,name1),
  playerPos(pos),
  playerWidth(w),
  playerHeight(h),
  currentMode(NORMAL),
  safeDistance(Gamedata::getInstance().getXmlFloat(name+"/safeDistance")),
  explosion(nullptr)
{}


SmartSprite::SmartSprite(const SmartSprite& s) : 
  TwoWaySprite(s),
  playerPos(s.playerPos),
  playerWidth(s.playerWidth),
  playerHeight(s.playerHeight),
  currentMode(s.currentMode),
  safeDistance(s.safeDistance),
  explosion(s.explosion)
{}

SmartSprite& SmartSprite::operator=(const SmartSprite& s)
  {
	TwoWaySprite::operator=(s);
  	playerPos=(s.playerPos);
  	playerWidth=(s.playerWidth);
  	playerHeight=(s.playerHeight);
  	currentMode=(s.currentMode);
  	safeDistance=(s.safeDistance);
  	explosion=(s.explosion);
        return *this;
  }


void SmartSprite::explode() {
  if ( !explosion )
  {
    Sprite 
    sprite(getName(), getPosition(), getVelocity(), images[currentFrame]);
    explosion = new ExplodingSprite(sprite);
  }
}

void SmartSprite::draw() const { 
  if ( explosion ) explosion->draw();
  else images[currentFrame]->draw(getX(), getY(), getScale());
}



void SmartSprite::update(Uint32 ticks) { 
  if ( explosion ) {
    explosion->update(ticks);
    if ( explosion->chunkCount() == 0 ) {
      delete explosion;
      explosion = NULL;
    }
    return;
  }

  TwoWaySprite::update(ticks);
    if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-getScaledHeight()) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
    setName(rightmoment);
    flipImage( RenderContext::getInstance()->getImages(rightmoment) );
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -fabs( getVelocityX() ) );
    setName(leftmoment);
    flipImage( RenderContext::getInstance()->getImages(leftmoment) );
  }
  float x= getX()+getImage()->getWidth()/2;
  float y= getY()+getImage()->getHeight()/2;
  float ex= playerPos[0]+playerWidth/2;
  float ey= playerPos[1]+playerHeight/2;
  float distanceToEnemy = ::distance( x, y, ex, ey );

  if  ( currentMode == NORMAL ) {
    if(distanceToEnemy < safeDistance) currentMode = EVADE;
  }
  else if  ( currentMode == EVADE ) {
    if(distanceToEnemy > safeDistance) currentMode=NORMAL;
    else {
      if ( x < ex ) goLeft();
      if ( x > ex ) goRight();
      if ( y < ey ) goUp();
      if ( y > ey ) goDown();
    }
  }
}

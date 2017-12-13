#include "player.h"
#include "smartSprite.h"
#include "gamedata.h"
#include "renderContext.h"

Player::Player( const std::string& name1, const std::string& name2) :
  TwoWayPlayer(name1, name2),
  observers(),
  collision(false),
  initialVelocity(getVelocity())
{ }

Player::Player(const Player& s) :
  TwoWayPlayer(s), 
  observers( s.observers ),
  collision(s.collision),
  initialVelocity(s.getVelocity())
  { }

Player& Player::operator=(const Player& s) {
  TwoWayPlayer::operator=(s);
  observers=s.observers;
  collision = s.collision;
  initialVelocity = s.initialVelocity;
  return *this;
}

void Player::detach( SmartSprite* o ) {
  std::list<SmartSprite*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    if ( *ptr == o ) {
      ptr = observers.erase(ptr);
      return;
    }
    ++ptr;
  }
}

void Player::stop() { 
  setVelocity(Vector2f(0,0));
}

void Player::right() { 
  if ( getX() < worldWidth-getScaledWidth()) {
    setVelocityX(initialVelocity[0]);
    setName(rightmoment);
    flipImage( RenderContext::getInstance()->getImages(rightmoment) );
  }
} 
void Player::left()  { 
  if ( getX() > 0) {
    setVelocityX(-initialVelocity[0]);
    setName(leftmoment);
    flipImage( RenderContext::getInstance()->getImages(leftmoment) );
  }
} 
void Player::up()    { 
  if ( getY() > 0) {
    setVelocityY( -initialVelocity[1] );
  }
} 
void Player::down()  { 
  if ( getY() < worldHeight-getScaledHeight()) {
    setVelocityY( initialVelocity[1] );
  }
}

void Player::update(Uint32 ticks) {
  std::list<SmartSprite*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    (*ptr)->setPlayerPos( getPosition() );
    ++ptr;
    }
  if ( !collision ) advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  stop();
}


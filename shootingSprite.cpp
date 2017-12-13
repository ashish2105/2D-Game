#include "shootingSprite.h"
#include "gamedata.h"
#include "renderContext.h"
#include "explodingSprite.h"

ShootingSprite::ShootingSprite(const std::string& name, const std::string& name1) :
  Player(name, name1),
  bulletName( Gamedata::getInstance().getXmlStr(name+"/bullet") ),
  bullets(bulletName),
  //check(false),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") ),
  bulletInterval(Gamedata::getInstance().getXmlInt(bulletName+"/interval")),
  timeSinceLastFrame(0),
  explosion(nullptr)
{ }

ShootingSprite::ShootingSprite(const ShootingSprite& s) :
  Player(s),
  bulletName(s.bulletName),
  bullets(s.bullets),
 // check(s.check),
  minSpeed(s.minSpeed),
  bulletInterval(s.bulletInterval),
  timeSinceLastFrame(s.timeSinceLastFrame),
  explosion(s.explosion)
{ }

ShootingSprite& ShootingSprite::operator=(const ShootingSprite& s) {
  Player::operator=(s);
  bulletName=s.bulletName;
  bullets=s.bullets;
 // check(s.check),
  minSpeed=s.minSpeed;
  bulletInterval=s.bulletInterval;
  timeSinceLastFrame=s.timeSinceLastFrame;
  explosion=s.explosion;
  return *this;
}
ShootingSprite::~ShootingSprite( ) { if (explosion) delete explosion; }

void ShootingSprite::shootLeft() { 

  if ( timeSinceLastFrame < bulletInterval ) return;
  //float deltaX = getScaledWidth();
  float deltaY = getScaledHeight()/2;
  // I need to add some minSpeed to velocity:
  Bullet bullet(bulletName);
  //bullet.setPosition( getPosition() +Vector2f(deltaX, deltaY) );
 // bullet.setVelocity( getVelocity() + Vector2f(minSpeed, 0) );

  bullets.shoot( getPosition() +Vector2f(0, deltaY), -(getVelocity() + Vector2f(minSpeed, 0)) );

  //bullets.shoot( getPosition() +Vector2f(0, deltaY), -(getVelocity() + Vector2f(minSpeed, 0)) );
  timeSinceLastFrame = 0;
}

void ShootingSprite::shootRight() { 

  if ( timeSinceLastFrame < bulletInterval ) return;
  float deltaX = getScaledWidth();
  float deltaY = getScaledHeight()/2;
  // I need to add some minSpeed to velocity:
  Bullet bullet(bulletName);
  //bullet.setPosition( getPosition() +Vector2f(deltaX, deltaY) );
 // bullet.setVelocity( getVelocity() + Vector2f(minSpeed, 0) );
  bullets.shoot( getPosition() +Vector2f(deltaX, deltaY), (getVelocity() + Vector2f(minSpeed, 0)) );
  
  //bullets.shoot( getPosition() +Vector2f(0, deltaY), -(getVelocity() + Vector2f(minSpeed, 0)) );
  timeSinceLastFrame = 0;
}


void ShootingSprite::explode() {
  if ( !explosion )
  {
    Sprite 
    sprite(getName(), getPosition(), getVelocity(), images[currentFrame]);
    explosion = new ExplodingSprite(sprite);
  }
}

bool ShootingSprite::collide(const Drawable* obj) const {
return bullets.collided(obj);
}
void ShootingSprite::draw() const{ 
  //Player::draw();
    bullets.draw();
  if ( explosion ) {explosion->draw();}
  else {images[currentFrame]->draw(getX(), getY(), getScale()); }
}

void ShootingSprite::update(Uint32 ticks) { 
	timeSinceLastFrame += ticks;
  Player::update(ticks);
    bullets.update(ticks);
  if ( explosion ) {
    explosion->update(ticks);
    if ( explosion->chunkCount() == 0 ) {
      delete explosion;
      explosion = NULL;
    }
    return;
  }
}


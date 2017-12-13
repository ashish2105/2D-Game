#include "twowayPlayer.h"
#include "gamedata.h"
#include "renderContext.h"

void TwoWayPlayer::advanceFrame(Uint32 ticks) {
  timeSinceLastFrame += ticks;
  if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
    timeSinceLastFrame = 0;
  }
}

TwoWayPlayer::TwoWayPlayer(const std::string& right, const std::string& left) :
  Drawable(right, 
           Vector2f(Gamedata::getInstance().getXmlInt(right+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(right+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(right+"/speedX"),
                    Gamedata::getInstance().getXmlInt(right+"/speedY"))
           ),
  images( RenderContext::getInstance()->getImages(right) ),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(right+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(right+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  rightmoment(right),
  leftmoment(left)
{ }

TwoWayPlayer::TwoWayPlayer(const TwoWayPlayer& s) :
  Drawable(s), 
  images(s.images),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  rightmoment(s.rightmoment),
  leftmoment(s.leftmoment)
  { }

TwoWayPlayer& TwoWayPlayer::operator=(const TwoWayPlayer& s) {
  Drawable::operator=(s);
  images = (s.images);
  currentFrame = (s.currentFrame);
  numberOfFrames = ( s.numberOfFrames );
  frameInterval = ( s.frameInterval );
  timeSinceLastFrame = ( s.timeSinceLastFrame );
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
  rightmoment = (s.rightmoment);
  leftmoment = (s.leftmoment);
  return *this;
}

void TwoWayPlayer::draw() const { 
  images[currentFrame]->draw(getX(), getY(), getScale());
}

void TwoWayPlayer::update(Uint32 ticks) { 
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

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

}

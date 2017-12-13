#ifndef TWOWAYPLAYER__H
#define TWOWAYPLAYER__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"

class ExplodingSprite;

class TwoWayPlayer : public Drawable {
public:
  TwoWayPlayer(const std::string&, const std::string&);
  TwoWayPlayer(const TwoWayPlayer&);
  virtual void draw() const;
  virtual void update(Uint32 ticks);

  virtual const Image* getImage() const { 
    return images[currentFrame]; 
  }
  int getScaledWidth()  const { 
    return getScale()*images[currentFrame]->getWidth(); 
  } 
  int getScaledHeight()  const { 
    return getScale()*images[currentFrame]->getHeight(); 
  } 
  virtual const SDL_Surface* getSurface() const { 
    return images[currentFrame]->getSurface();
  }

  void flipImage(std::vector<Image *> Images) {
    images = Images;
  }

protected:
  std::vector<Image *> images;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int worldWidth;
  int worldHeight;

  std::string rightmoment;
  std::string leftmoment;

  void advanceFrame(Uint32 ticks);
  TwoWayPlayer& operator=(const TwoWayPlayer&);
};
#endif

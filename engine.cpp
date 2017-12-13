#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include <vector>
#include "shootingSprite.h"
#include "sprite.h"
#include "multisprite.h"
#include "player.h"
#include "twowaySprite.h"
#include "gamedata.h"
#include "engine.h"
#include "smartSprite.h"
#include "frameGenerator.h"
#include "collisionStrategy.h"
#include "explodingSprite.h"

class SpriteLess {
public:
  bool operator()(const Drawable* lhs, const Drawable* rhs) const {
    return lhs->getScale() < rhs->getScale();
  }
};


Engine::~Engine() { 
  delete player;
  for(auto x: sprite)
  delete x;
  for(auto z: sprites)
  delete z;
  for(auto y: strategies)
  delete y;
  for(auto a: wall)
  delete a;
  for(auto a: fwall)
  delete a;
  for(auto b: bust)
  delete b;
  for(auto b: cake)
  delete b;
  for(auto b: paint)
  delete b;
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  hud( Hud::getInstance() ),
  rc( RenderContext::getInstance() ),
  io( IOmod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  world("land", Gamedata::getInstance().getXmlInt("land/factor") ),
  w("tree", Gamedata::getInstance().getXmlInt("tree/factor") ),
  x("building", Gamedata::getInstance().getXmlInt("building/factor") ),
  a("shadow1", Gamedata::getInstance().getXmlInt("shadow1/factor") ),
  b("shadow2", Gamedata::getInstance().getXmlInt("shadow2/factor") ),
  c("shadow3", Gamedata::getInstance().getXmlInt("shadow3/factor") ),
  d("sun", Gamedata::getInstance().getXmlInt("sun/factor") ),
  e("sky", Gamedata::getInstance().getXmlInt("sky/factor") ),
  viewport( Viewport::getInstance() ),
  player(new ShootingSprite("Horseright","Horseleft")),
  cake(),
  sprite(),
  wall(),
  bust(),
  paint(),
  fwall(),
  sprites(),
  strategies(),
  currentStrategy(),
  collision(),
  shootright(true),
  god(true),
  count(0),
  last(0),
  life(3),
  time(0),
  currentSprite(0),
  gameHud(0),
  pool(*player),
  sound(),
  makeVideo( false )
{

  //sprites.push_back( new ShootingSprite("bluesquare") );
  int n = Gamedata::getInstance().getXmlInt("numberOfStars");
  int v = Gamedata::getInstance().getXmlInt("numberOfCoins");
  for ( int i = 0; i < v; ++i ) {
    Drawable* s = new TwoWaySprite("coin","coin");
    float scale = Gamedata::getInstance().getRandFloat(0.1,0.8);
    s->setScale(scale);
    paint.push_back(s);
    //delete s;
  }
  std::vector<Drawable*>::iterator ptr = paint.begin();
  ++ptr;
  sort(ptr, paint.end(), SpriteLess());
  sprites.reserve(n);
    Vector2f pos = player->getPosition();
  int w = player->getScaledWidth();
  int h = player->getScaledHeight();
  for (int i = 0; i < n; ++i) {
    sprites.push_back( new SmartSprite("coin","coin", pos, w, h) );
    player->attach( sprites[i] );
  } 
  
  wall.push_back(new MultiSprite("Mwall"));
  wall.push_back(new MultiSprite("Mwall1"));
  wall.push_back(new MultiSprite("Mwall2"));
  wall.push_back(new MultiSprite("Mwall3"));
  wall.push_back(new MultiSprite("Mwall4"));
  wall.push_back(new MultiSprite("Mwall5"));
  wall.push_back(new MultiSprite("Mwall6"));
  wall.push_back(new MultiSprite("Mwall7"));
  wall.push_back(new MultiSprite("Mwall8"));
  wall.push_back(new MultiSprite("Mwall9"));
  wall.push_back(new Sprite("Wall"));
  wall.push_back(new Sprite("Wall2"));
  wall.push_back(new Sprite("Wall3"));
  wall.push_back(new Sprite("Wall4"));
  wall.push_back(new Sprite("Wall5"));
  wall.push_back(new Sprite("Wall6"));
  wall.push_back(new Sprite("Wall7"));
  wall.push_back(new Sprite("Wall8"));
  wall.push_back(new Sprite("Wall9"));
  //wall.push_back(new Sprite("Wall10"));
  bust.push_back(new Sprite("EWall3"));
  bust.push_back(new Sprite("EWall4"));
  bust.push_back(new Sprite("EWall5"));
  bust.push_back(new Sprite("EWall6"));
  bust.push_back(new Sprite("EWall7"));
  bust.push_back(new Sprite("EWall8"));
  bust.push_back(new Sprite("EWall9"));
  fwall.push_back(new Sprite("EWall10"));
  cake.push_back(new Sprite("Cake"));
  sprite.push_back(new MultiSprite("Tree"));  
  sprite.push_back(new MultiSprite("Tree1"));  
  sprite.push_back(new MultiSprite("Tree2"));  
  sprite.push_back(new MultiSprite("Tree3"));  
  sprite.push_back(new MultiSprite("Tree4"));  
  sprite.push_back(new MultiSprite("Tree5"));  
  sprite.push_back(new MultiSprite("Tree6"));  
  sprite.push_back(new MultiSprite("Tree7")); 
  //strategies.push_back( new RectangularCollisionStrategy );
  strategies.push_back( new PerPixelCollisionStrategy );
  //strategies.push_back( new MidPointCollisionStrategy );
  Viewport::getInstance().setObjectToTrack(player);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  e.draw();
  d.draw();
  for(unsigned int i=0; i<(paint.size()/3);i++) paint[i]->draw();
  c.draw();
  b.draw();
  for(unsigned int i=(paint.size()/3); i<(2*paint.size()/3);i++) paint[i]->draw();
  a.draw();
  x.draw();
  for(unsigned int i=(2*paint.size()/3); i<(paint.size());i++) paint[i]->draw();
  w.draw();
  world.draw();
  pool.draw();

  SDL_Color c={0,0,0,255};
 // IOmod::getInstance().writeText("Press m to change strategy", 500, 60);
   for ( const Drawable* sprite : sprites ) {
    sprite->draw();
  }
 // int x=sprites.size();
  for ( const Drawable* sprites : sprite ) {
    sprites->draw();
  }
  for ( const Drawable* walls : wall ) {
    walls->draw();
  }
  for ( const Drawable* busts : bust ) {
    busts->draw();
  }
  for ( const Drawable* busts : fwall ) {
    busts->draw();
  }
  for ( const Drawable* cakes : cake ) {
    cakes->draw();
  }
  strategies[currentStrategy]->draw();
  if ( collision ) {
    //IOmod::getInstance().writeText("Oops: Collision", 500, 90);
  }
  player->draw();
  std::stringstream strme;
  strme << sprites.size() << " Coins left";
  IOmod::getInstance().writeText(strme.str(), c, 30, 90);
  
  std::stringstream strm;
  strm << life << " Lifes left";
  IOmod::getInstance().writeText(strm.str(), c, 30, 60);
  io.writeText("Ashish's Game",c,30,400);
  //unsigned int time= Gamedata::getInstance().getXmlInt("hud1/Time");
    if(gameHud==0){
	hud.startHud();
        clock.pause(); }
    if(gameHud%2==0&&gameHud!=0)
        hud.displayHud();
    if(last==1)
        hud.endHud();
    if(life==0){
        hud.lostHud();
        clock.pause();
        }
  viewport.draw();
  SDL_RenderPresent(renderer);
 
}

void Engine::checkForCollisions() {
  collision = false;
  /*for ( const auto d : sprite ) {
    if ( strategies[currentStrategy]->execute(*player, *d) ) {
      collision = true;
     d->explode();
    }
  }*/
 for ( const auto d : cake ) {
    if ( strategies[currentStrategy]->execute(*player, *d) ) {     
    last=1;
    (d)->setPosition(Vector2f((d)->getPosition()[0] + 2500 , (d)->getPosition()[1]));
    }
  }
  for ( const auto d : wall ) {
    if ( strategies[currentStrategy]->execute(*player, *d) ) {
      collision = true;
    }
  }

  for ( const auto d : fwall ) {
   if(count==Gamedata::getInstance().getXmlInt("numberOfStars"))
    {
   if ( player->collide(d) ) {   
     static_cast<Sprite*>(d)->explode(); 
    (d)->setPosition(Vector2f((d)->getPosition()[0] + 2500 , (d)->getPosition()[1]));	
     sound[5];
    // d->explode();
    }
   }
  }
   for ( const auto d : fwall ) {
    if ( strategies[currentStrategy]->execute(*player, *d) ) {
      collision = true;
    }
  }  
  for ( const auto d : bust ) {
    if ( strategies[currentStrategy]->execute(*player, *d) ) {
      collision = true;
    }
  }
  for ( const auto d : bust ) {
    if ( player->collide(d) ) {     
     static_cast<Sprite*>(d)->explode(); 
    (d)->setPosition(Vector2f((d)->getPosition()[0] + 5000 , (d)->getPosition()[1]));	
     sound[5];
    // d->explode();
    }
  }
  if ( collision ) {
    player->collided();
    player->explode();
    sound[6];
     if(life==3)
     {
    --life;
     time=clock.getSeconds();
     time=time+3;
     }
     else if(time<clock.getSeconds())
     {
     --life;
     time=clock.getSeconds();
     time=time+3;
     }
      
    (player)->setPosition(Vector2f((player)->getPosition()[0] -150 , (player)->getPosition()[1]));	
    //draw();
    
   // IOmod::getInstance().writeText("Oops: Collision", 500, 90);
  }
  else {
    player->missed();
    collision = false;
  }
  auto it = sprites.begin();
  while ( it != sprites.end() ) {
    if ( strategies[currentStrategy]->execute(*player, **it) ) {
      sound[9];
      ++count;
      SmartSprite* doa = *it;
      player->detach(doa);
      delete doa;
      it = sprites.erase(it);
    }
    else ++it;
  }

  auto it1 = bust.begin();
  while ( it1 != bust.end() ) {
    if (static_cast<Sprite*> (*it1)->getDeleteFlag() ) {
      //static_cast<Sprite*>(*it1)->explode();
      Drawable* boa=*it1;
      delete boa;
      it1 = bust.erase(it1);
    }
    else ++it1;
  }

  auto it2 = fwall.begin();
  while ( it2 != fwall.end() ) {
    if (static_cast<Sprite*> (*it2)->getDeleteFlag() ) {
      //static_cast<Sprite*>(*it1)->explode();
      Drawable* foa=*it2;
      delete foa;
      it2 = fwall.erase(it2);
    }
    else ++it2;
  }

}

void Engine::update(Uint32 ticks) {
  if(!god)
  checkForCollisions();
  for(auto* s : paint) s->update(ticks);
    for ( Drawable* sprite : sprites ) {
    sprite->update( ticks );
  }
  for(auto x: sprite)
  x->update(ticks);
  for ( Drawable* walls : wall ) {
    walls->update(ticks);
  }
  for ( Drawable* busts : bust ) {
    busts->update(ticks);
  }
   for ( Drawable* fwalls : fwall ) {
    fwalls->update(ticks);
  }
  for ( Drawable* cakes : cake ) {
    cakes->update(ticks);
  }
  //spinningStar->update(ticks);
  world.update();
  w.update();
  x.update();
  a.update();
  b.update();
  c.update();
  d.update();
  e.update();
  player->update(ticks);
  viewport.update(); // always update viewport last
}



bool Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if ( keystate[SDL_SCANCODE_SPACE] ) {
          if(shootright==true)
          static_cast<ShootingSprite*>(player)->shootRight();
          else
          static_cast<ShootingSprite*>(player)->shootLeft();
	  sound[3];
        }
        if ( keystate[SDL_SCANCODE_G] ) {
          if(!god) god=true;
           else god=false;
        }
        if ( keystate[SDL_SCANCODE_F1] ) {
          ++gameHud;
           if(gameHud==1)
           god=false;
        }
        if ( keystate[SDL_SCANCODE_T] ) {
           if(gameHud==0){
           god=false;
           ++gameHud;
           clock.unpause();
           }
        }
        if ( keystate[SDL_SCANCODE_R] ) {
          clock.unpause();
          return true;
        }
	if ( keystate[SDL_SCANCODE_M] ) {
          currentStrategy = (1 + currentStrategy) % strategies.size();
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
      }
    }

    // In this section of the event loop we allow key bounce:

    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      if (keystate[SDL_SCANCODE_A]) {
        player->left();
        shootright=false;
      }
      if (keystate[SDL_SCANCODE_D]) {
        player->right();
        shootright=true;
      } 
      if (keystate[SDL_SCANCODE_W]) {
        player->up();
      }
      if (keystate[SDL_SCANCODE_S]) {
        player->down();
      }
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
  return false;
}

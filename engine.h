#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "hud.h"
#include "poolHud.h"
#include "sound.h"

class ShootingSprite;
class CollisionStrategy;
class SmartSprite;
class MultiSprite;
class Engine {
public:
  Engine ();
  ~Engine ();
  bool play();
  Engine(const Engine&)=delete;
  Engine& operator=(const Engine&)=delete;
private:
  Hud& hud;
  const RenderContext* rc;
  const IOmod& io;
  Clock& clock;

  SDL_Renderer * const renderer;
  World world;
  World w;
  World x;
  World a;
  World b;
  World c;
  World d;
  World e;
  Viewport& viewport;
  ShootingSprite* player;
  std::vector<Drawable*> cake;
  std::vector<Drawable*> sprite;
  std::vector<Drawable*> wall;
  std::vector<Drawable*> bust;
  std::vector<Drawable*> paint;
  std::vector<Drawable*> fwall;
  std::vector<SmartSprite*> sprites;
  std::vector<CollisionStrategy*> strategies;
  int currentStrategy;
  bool collision;
  bool shootright;
  bool god;
  int count;
  int last;
  int life;
  unsigned int time;
  //Drawable* star;
  //Drawable* spinningStar;
  int currentSprite, gameHud;
  PoolHud pool;
  SDLSound sound;
  bool makeVideo;
  void draw() const;
  void update(Uint32);

  
  void printScales() const;
  void checkForCollisions();
};

#include "poolHud.h"
#include "gamedata.h"
#include "renderContext.h"
#include <sstream>


PoolHud::PoolHud(const ShootingSprite& p):
    player(p),
    r( RenderContext::getInstance()->getRenderer() ),
    Rectangle( {Gamedata::getInstance().getXmlInt("poolhud/start/x"),
               Gamedata::getInstance().getXmlInt("poolhud/start/y"),
               Gamedata::getInstance().getXmlInt("poolhud/width"),
               Gamedata::getInstance().getXmlInt("poolhud/height")
              }
            ),
    showPoolHud(true),
    io(IOmod::getInstance())
   {}

void PoolHud::update(){}
void PoolHud::draw() const {
if (!showPoolHud) return;
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( r, 255, 255, 255, 255/2 );
    SDL_RenderFillRect( r, &Rectangle );
    std::stringstream strm;
    strm<<"Bullet List :"<< player.bulletCount();
    io.writeText(strm.str(),Rectangle.x+10, 22);
    strm.clear();
    strm.str("");
    strm<<"Free List :"<< player.freeCount();
    io.writeText(strm.str(),Rectangle.x+10, 50);
    SDL_SetRenderDrawColor( r, 255, 255, 255, 255/2 );
    SDL_RenderFillRect( r, &Rectangle );
}





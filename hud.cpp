#include "hud.h"
#include "ioMod.h"
#include "clock.h"
#include <iostream>
#include <string>
#include <iomanip>
#include "gamedata.h"
#include "renderContext.h"
#include <sstream>
Hud& Hud::getInstance(){
    static Hud instance;
    return instance;
}

Hud::Hud(): width(Gamedata::getInstance().getXmlInt("hud/width")),
    height(Gamedata::getInstance().getXmlInt("hud/height")),
    width1(Gamedata::getInstance().getXmlInt("hud1/width")),
    height1(Gamedata::getInstance().getXmlInt("hud1/height")),
    x(Gamedata::getInstance().getXmlInt("hud/start/x")),
    y(Gamedata::getInstance().getXmlInt("hud/start/y")),
    x1(Gamedata::getInstance().getXmlInt("hud1/start/x")),
    y1(Gamedata::getInstance().getXmlInt("hud1/start/y")),
    r( RenderContext::getInstance()->getRenderer() ),
    Rectangle({x,y,width,height}),
    Rectangle1({x1,y1,width1,height1})
   {}

Hud::~Hud()
{}



void Hud::displayHud() const{
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( r, 255, 255, 255, 255/2 );
    SDL_RenderFillRect( r, &Rectangle );
    SDL_SetRenderDrawColor( r, 255, 0, 0, 255 );
    SDL_RenderDrawRect( r, &Rectangle );
    SDL_Color Textcolor = {0,0,0,255};  
    IOmod::getInstance().writeText("Controls ",Textcolor, x+15, y+25);
    IOmod::getInstance().writeText("a: Left ",Textcolor, x+15, y+50);
    IOmod::getInstance().writeText("d: Right",Textcolor, x+15, y+75);
    IOmod::getInstance().writeText("w: Up",Textcolor, x+15, y+100);
    IOmod::getInstance().writeText("s: Down ",Textcolor, x+15, y+125);
    IOmod::getInstance().writeText("P: Pause ",Textcolor, x+15, y+150);
    IOmod::getInstance().writeText("G: God Mode ",Textcolor, x+15, y+175);
    IOmod::getInstance().writeText("space Bar: Shooting ",Textcolor, x+15, y+200);
    IOmod::getInstance().writeText("ESC: To exit ",Textcolor, x+15, y+250);
    std::stringstream strm;
    strm<<"Fps : "<<Clock::getInstance().getFps();
 // io.writeText(,30,55);
    IOmod::getInstance().writeText(strm.str(),Textcolor, x+15, y+225);
  
    
}

void Hud::startHud() const{
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( r, 255, 255, 255, 255/2 );
    SDL_RenderFillRect( r, &Rectangle1 );
    SDL_SetRenderDrawColor( r, 255, 0, 0, 255 );
    SDL_RenderDrawRect( r, &Rectangle1 );
    SDL_Color Textcolor = {0,0,0,255};  
    IOmod::getInstance().writeText("WELCOME TO FLAPPY UNICORN GAME ",Textcolor, x+150, y+15);
    IOmod::getInstance().writeText("You can control the unicorns moment using ASWD, SpaceBar is assigned for",Textcolor, x1, y+50);
    IOmod::getInstance().writeText("shooting. The objective of the game is to complete the obstacle course to reach",Textcolor, x1, y+75);
    IOmod::getInstance().writeText("the end of the game and treat the unicorn with a delicious cupcake.If unicorn",Textcolor, x1, y+100);
    IOmod::getInstance().writeText("collides with any of the Blue walls it will die. The red walls can be destroyed by  ",Textcolor, x1, y+125);
    IOmod::getInstance().writeText("shooting them. There are coins flying around which needs to be collected. At ",Textcolor, x1, y+150);
    IOmod::getInstance().writeText("the end of the game there will be big red wall and the last wall can be exploded by, ",Textcolor, x1, y+175);
    IOmod::getInstance().writeText("shooting it But you need to collect all the coins in order to explode the walls.  ",Textcolor, x1, y+200);
    IOmod::getInstance().writeText("If you don't collect all the coins, your bullets will have no effect on the wall.",Textcolor, x1, y+225);
    IOmod::getInstance().writeText("You have 3 lives to complete the game. All the best",Textcolor, x1, y+250);
    IOmod::getInstance().writeText("I hope you will enjoy the game ",Textcolor, x1+150, y+350);
    IOmod::getInstance().writeText("press T to start ",Textcolor, x+15, y+275);
    IOmod::getInstance().writeText("For any help throughout the game press F1 ",Textcolor, x+15, y+300);
  
    
}

void Hud::endHud() const{
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( r, 255, 255, 255, 255/2 );
    SDL_RenderFillRect( r, &Rectangle1 );
    SDL_SetRenderDrawColor( r, 255, 0, 0, 255 );
    SDL_RenderDrawRect( r, &Rectangle1 );
    SDL_Color Textcolor = {0,0,0,255};  
    IOmod::getInstance().writeText("THANKS FOR PLAYING FLAPPY UNICORN GAME ",Textcolor, x+150, y+15);
    IOmod::getInstance().writeText("You have sucessfully completed the game",Textcolor, x1+150, y+50);
    IOmod::getInstance().writeText("Please press R to restart",Textcolor, x1+150, y+75);
    IOmod::getInstance().writeText("Press ESC to exit",Textcolor, x1+150, y+100);
    }
void Hud::lostHud() const{
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( r, 255, 255, 255, 255/2 );
    SDL_RenderFillRect( r, &Rectangle1 );
    SDL_SetRenderDrawColor( r, 255, 0, 0, 255 );
    SDL_RenderDrawRect( r, &Rectangle1 );
    SDL_Color Textcolor = {0,0,0,255};  
    IOmod::getInstance().writeText("GAME OVER ",Textcolor, x+150, y+15);
    IOmod::getInstance().writeText("Sorry you are out of lifes",Textcolor, x1+150, y+50);
    IOmod::getInstance().writeText("Please press R to restart",Textcolor, x1+150, y+75);
    IOmod::getInstance().writeText("Press ESC to exit",Textcolor, x1+150, y+100);
    }





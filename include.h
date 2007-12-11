#ifndef INCLUDE_H
#define INCLUDE_H

//This file should be at the theoretical top of all of the headers. It contains the libraries necessary for most
//all of the classes to work properly. This method ensures that all of these files are included once and only once,
//thus speeding up linking time. I know that it isn't proper, but it gets the job done, and I think it does it well.
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <vector>
#include <list>
#include <math.h>
#include <string>

//Globals. These really need to be cut down. I think most of this can be solved by putting them all in the graphics
//class, once it has been formatted as such, and making an instance of that class global. I'm not sure.
const int SCREEN_WIDTH = 200;	//Screen width
const int SCREEN_HEIGHT = 100;	//Screen height
const int SCREEN_BPP = 32;	//Screen BPP

extern SDL_Event SDLEvent;	//The main event that we poll to get key presses, releases, etc.

class Dynamic_Object;	//Forward declaration of this class, so that the below doesn't get mad
class Character;	//Forward declaration of this class, so that the below doesn't get mad
extern std::vector<Dynamic_Object*> interactObjectList;
extern std::vector<Dynamic_Object*> backgroundObjectList;
extern std::list<Dynamic_Object*> collisionList;
	//The lists of all dynamic objects created in the game.

extern Character *hero;	//A pointer to the hero instance of the character class

#endif

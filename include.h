#ifndef INCLUDE_H
#define INCLUDE_H

//This file should be at the theoretical top of all of the headers. It contains the libraries necessary for most
//all of the classes to work properly. This method ensures that all of these files are included once and only once,
//thus speeding up linking time. I know that it isn't proper, but it gets the job done, and I think it does it well.
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <vector>
#include <math.h>
#include <string>

//Globals. These really need to be cut down. I think most of this can be solved by putting them all in the graphics
//class, once it has been formatted as such, and making an instance of that class global. I'm not sure.
const int SCREEN_WIDTH = 200;	//Screen width
const int SCREEN_HEIGHT = 100;	//Screen height
const int SCREEN_BPP = 32;	//Screen BPP

SDL_Event SDLEvent;	//The main event that we poll to get key presses, releases, etc.

SDL_Surface *screen = NULL;	//The main display screen for the game
SDL_Surface *dynamicLayer = NULL;
	//A very important surface. All of the dynamic objects should update to this surface, in order from
	//back to front. This surface will eventually be blitted to the screen, but only at the very last possible
	//moment.
SDL_Surface *background = NULL;	//The main background surface for the game
SDL_Surface *dynamicSprites = NULL;
	//The surface containing all of the spritesheets for dynamic objects, except for the characters
SDL_Surface *bgTiles = NULL;
	//The surface containing all of the tiles used to populate the background
SDL_Surface *characters = NULL;
	//The surface containing all of the sprites necessary to create the characters

class Dynamic_Object;	//Forward declaration of this class, so that the below doesn't get mad
std::vector<Dynamic_Object*> allDynamicObjects;
	//The list of all dynamic objects created in the game.

class Character;	//Forward declaration of this class, so that the below doesn't get mad
Character *hero = NULL;	//A pointer to the hero instance of the character class

#endif

#ifndef INCLUDE_H
#define INCLUDE_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <vector>
#include <math.h>
#include <string>
#include "ClassDeclarations.h"

//Globals
const int SCREEN_WIDTH = 200;
const int SCREEN_HEIGHT = 100;
const int SCREEN_BPP = 32;

SDL_Event SDLEvent;

SDL_Surface *screen = NULL;
SDL_Surface *background = NULL;
SDL_Surface *dynamicSprites = NULL;
SDL_Surface *bgTiles = NULL;
SDL_Surface *characters = NULL;
SDL_Surface *dynamicLayer = NULL;

std::vector<Dynamic_Object*> allDynamicObjects;

Character *hero = NULL;

#include "BG_Item.h"
#include "Graphics.h"
#include "Animation.h"
#include "Character.h"
#include "Dynamic_Object.h"
#include "Torch.h"

#endif

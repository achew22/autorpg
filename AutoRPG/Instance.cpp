/*
Copyright 2007, 2008 Andrew Allen and Brian Shourd

This file is part of AutoRPG.

AutoRPG is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

AutoRPG is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with AutoRPG (Called LICENSE.txt).  If not, see
<http://www.gnu.org/licenses/>.
*/

#include "Instance.h"
#include "Character.h"
#include "Sprite_Sheet.h"
#include "Map.h"
#include "constants.h"
#include "Point.h"
#include "Graphics.h"

#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <vector>

//The constructor, locx and locy determine where this particular Instance module will load it's stuff
Instance::Instance(int locx, int locy, SDL_Surface* theScreen)
{
    dynamicLayer = SDL_CreateRGBSurface(SDL_SWSURFACE, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, NULL, NULL, NULL, NULL);
    screen = theScreen;
}

//Loads the necessary files to be used. Returns false if there was some error, otherwise returns true
//Currently, there is no need to load any files, though there will be, I'm sure
bool Instance::LoadFiles()
{
	return true;
}

void Instance::LoadMap(std::string indexFile, std::string tileFile)
{
    map = new Map(indexFile, tileFile);
    //map->AssignSpriteSheet(50, 50, tileFile);
}

//Frees all of the surfaces that were declared, unless they were already freed, then quits SDL
void Instance::CleanUp()
{
	if (dynamicLayer != NULL)
	{
		printf("dynamicLayer to be freed\n");
		SDL_FreeSurface(dynamicLayer);
		printf("dynamicLayer freed\n");
	}
}

//Updates every item in the allDynamicObjects list, if it is within 100 pixels of the screen. It then flips the buffers to display the frame.
//Returns false if an error occurs
bool Instance::Update()
{
	SDL_Rect screenLocation;	//Defines essentially where the camera is at
	screenLocation.h = 200;
	screenLocation.w = 200;
	screenLocation.y = 0;

	//Keep the screenLocation relative to the player's position
	if (player != NULL)
	{
		Point pos = player->GetPosition();
		screenLocation.x = pos.x - (SCREEN_WIDTH - 48)/2;
		screenLocation.y = pos.y - (SCREEN_HEIGHT - 64)/2;
	}
	else
	{
		screenLocation.x = 0;
	}

	//Apply the map to the background
	if (map != NULL)
	{
        map->ApplyMap(screenLocation.x, screenLocation.y, SCREEN_HEIGHT, SCREEN_WIDTH, dynamicLayer);
	}

	//Check every dynamicObject in our main lists to see if it is close enough to the screen to warrant an update
	//and then call its update function. I am afraid that this is really inefficient to do EVERY FRAME, but I haven't
	//yet fixed this problem
    for (std::map<std::string, Character*>::iterator i = characterList.begin(); i != characterList.end(); i++)
	{
		Point pos = i->second->GetPosition();
		i->second->UpdatePosition();
		if ((pos.x > screenLocation.x - 100) && (pos.x < screenLocation.x + screenLocation.w + 100)
			&& (pos.y > screenLocation.y - 50) && (pos.y < screenLocation.y + screenLocation.h + 50))
		{
			i->second->UpdateAnimation();
		}
	}

    //Clear the screen
	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

	//Apply the dynamic layer to the screen layer, with the clip around the screenLocation
	Graphics::ApplyImage(0, 0, dynamicLayer, screen, &screenLocation);

	return true;
}

void Instance::SetUpDynamicObjects()
{
	player = new Character(20, 32, 48, 64, dynamicLayer, "player");
	characterList.insert(characterList.begin(), std::pair<std::string, Character*>("player", player));
}

Character* Instance::GetPlayer()
{
    return player;
}

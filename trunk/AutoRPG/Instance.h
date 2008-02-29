#ifndef INSTANCE_H
#define INSTANCE_H

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

#include <SDL/SDL.h>
#include <string>
#include "Point.h"
#include "Sprite_Sheet.h"
#include <vector>
#include <map>
#include "Character.h"
#include "Map.h"

class Instance
{
private:
    SDL_Surface *screen;	//The main display screen for the game
    SDL_Surface *dynamicLayer;
        //A very important surface. All of the dynamic objects should update to this surface, in order from
        //back to front. This surface will eventually be blitted to the screen, but only at the very last possible
        //moment.
    std::map<int, Character*> characterMap;    //Pointers to the lists that will need to be updated that exist in this instace of graphics
    Character* player;
    Map* map;
public:
    Instance(int locx, int locy, SDL_Surface* theScreen);
	bool LoadFiles();	//Load all of the necessary files for this game
	void LoadMap(std::string indexFile, std::string tileFile);
	bool Update();	//The main update function, which calls all of the necessary updates for the dynamic objects and ultimately makes the buffer swap
		//to show them all to the screen
	void CleanUp();	//Frees all of the allocated surfaces and quits the SDL subsystems that are running
	void SetUpDynamicObjects();
	Character* GetPlayer();  //Returns a pointer to the character for this instance
};

#endif

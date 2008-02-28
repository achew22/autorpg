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

#include "constants.h"
#include "Instance.h"
#include "Character.h"
#include "Graphics.h"
#include "Conversions.h"

#include <stdio.h>

int main(int argc, char *args[])
{
    Graphics graphics;
   	if (!graphics.Init()) {printf("Init failed\n"); return 1;} else {printf("Init Success\n");}

    Instance instance1(0, 0, graphics.GetScreen());

	if (!instance1.LoadFiles()) {printf("LoadFiles failed\n"); return 1;} else {printf("LoadFiles Success\n");}
	instance1.LoadMap("maps/map1.txt", "maps/map1.gif");
	instance1.SetUpDynamicObjects();
	if (!instance1.Update()) {printf("Update failed\n"); return 1;} else {printf("Update Success\n");}

	SDL_Event SDLEvent; //The main event for polling and what-not
    bool quit = false;
	while (quit != true)
	{
		if (SDL_PollEvent(&SDLEvent))
		{
			if (SDLEvent.type == SDL_KEYDOWN)
			{
				switch (SDLEvent.key.keysym.sym)
				{
				case SDLK_RIGHT:    //Right button pressed
					instance1.GetPlayer()->MoveRight();
					break;
				case SDLK_LEFT:     //Left button pressed
					instance1.GetPlayer()->MoveLeft();
					break;
				case SDLK_UP:		//Up button pressed
					instance1.GetPlayer()->MoveUp();
					break;
                case SDLK_DOWN:     //Down button pressed
                    instance1.GetPlayer()->MoveDown();
                    break;
				case SDLK_ESCAPE:   //Escape pressed
					quit = true;
					break;
                default:
                    break;
				}
			}
			else if (SDLEvent.type == SDL_KEYUP)
			{
				switch (SDLEvent.key.keysym.sym)
				{
				case SDLK_RIGHT:    //Right button released
					if (instance1.GetPlayer()->GetVelocity().x > 0)   //If you were moving right
					{
						instance1.GetPlayer()->StopMoveHoriz();    //Stop moving right
					}
					break;
				case SDLK_LEFT:     //Left button released
					if (instance1.GetPlayer()->GetVelocity().x < 0)   //If you were moving left
					{
						instance1.GetPlayer()->StopMoveHoriz();    //Stop moving left
					}
					break;
                case SDLK_UP:     //Up button released
					if (instance1.GetPlayer()->GetVelocity().y < 0)   //If you were moving up
					{
						instance1.GetPlayer()->StopMoveVert();    //Stop moving up
					}
					break;
                case SDLK_DOWN: //Down button released
                    if (instance1.GetPlayer()->GetVelocity().y > 0) //If you were moving down
                    {
                        instance1.GetPlayer()->StopMoveVert();  //Stop moving down
                    }
                    break;
                default:
                    break;
				}
			}
			else if (SDLEvent.type == SDL_QUIT)
			{
				quit = true;    //If the person "X"'s out of the window
			}
		}
		if (!instance1.Update()) {return 1;}    //Update
		if (!graphics.Update()) {return 1;}     //Update
	}

	instance1.CleanUp();    //Clean up all dynamically allocated memory
	graphics.CleanUp();

	return 0;
}

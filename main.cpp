#include "constants.h"
#include "Graphics.h"
#include "Character.h"
#include "Dynamic_Object.h"
#include "Torch.h"
#include <stdio.h>

Character *hero = NULL;	//A pointer to the hero instance of the character class

int main(int argc, char *args[])
{
    Graphics *graphics = new Graphics();
	if (!graphics->Init()) {printf("Init failed\n"); return 1;} else {printf("Init Success\n");}
	if (!graphics->LoadFiles()) {printf("LoadFiles failed\n"); return 1;} else {printf("LoadFiles Success\n");}
	graphics->SetUpDynamicObjects();
	graphics->CreateBackground();
	if (!graphics->Update()) {printf("Update failed\n"); return 1;} else {printf("Update Success\n");}

	SDL_Event SDLEvent; //The main event for polling and what-not
    bool quit = false;
    int time = 0;
	while (quit != true)
	{
	    time = SDL_GetTicks();  //This is the current time since initialization, in milliseconds (used for capping the frame rate)
		if (SDL_PollEvent(&SDLEvent))
		{
			if (SDLEvent.type == SDL_KEYDOWN)
			{
				switch (SDLEvent.key.keysym.sym)
				{
				case SDLK_RIGHT:    //Right button pressed
					hero->MoveRight();
					break;
				case SDLK_LEFT:     //Left button pressed
					hero->MoveLeft();
					break;
				case SDLK_UP:		//Up button pressed
					hero->Jump();
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
					if (hero->GetVelocity().x > 0)   //If you were moving right
					{
						hero->StopMove();    //Stop moving right
					}
					break;
				case SDLK_LEFT:     //Left button released
					if (hero->GetVelocity().x < 0)   //If you were moving left
					{
						hero->StopMove();    //Stop moving left
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
		if (!graphics->Update()) {return 1;}    //Update
		if (SDL_GetTicks() - time <= 1000.0/FPS)    //Capping the frame rate: if not enough time has passed
		{
		    SDL_Delay((Uint32)(1000.0/FPS - SDL_GetTicks() + time));  //Then wait until enough time has passed
		}
	}

	graphics->CleanUp();    //Clean up all dynamically allocated memory
	delete graphics;

	return 0;
}

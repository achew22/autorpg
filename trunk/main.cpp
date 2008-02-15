#include "constants.h"
#include "Instance.h"
#include "Character.h"
#include "Dynamic_Object.h"
#include "Torch.h"
#include <stdio.h>

int main(int argc, char *args[])
{
    Instance *instance2 = new Instance(0, 100);
    Instance *instance1 = new Instance(0, 0);
	if (!Instance::Init()) {printf("Init failed\n"); return 1;} else {printf("Init Success\n");}
	if (!instance1->LoadFiles("images/dynamicobjects2x.png", "images/bgTiles2x.png", "images/miniDungeonCharSprites2x.png")) {printf("LoadFiles failed\n"); return 1;} else {printf("LoadFiles Success\n");}
	instance1->SetUpDynamicObjects();
	instance1->CreateBackground();
	if (!instance1->Update()) {printf("Update failed\n"); return 1;} else {printf("Update Success\n");}

	if (!instance2->LoadFiles("images/dynamicobjects2x.png", "images/bgTiles2x.png", "images/miniDungeonCharSprites2x.png")) {printf("LoadFiles failed\n"); return 1;} else {printf("LoadFiles Success\n");}
	instance2->SetUpDynamicObjects();
	instance2->CreateBackground();
	if (!instance2->Update()) {printf("Update failed\n"); return 1;} else {printf("Update Success\n");}

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
					instance1->GetPlayer()->MoveRight();
					break;
				case SDLK_LEFT:     //Left button pressed
					instance1->GetPlayer()->MoveLeft();
					break;
				case SDLK_UP:		//Up button pressed
					instance1->GetPlayer()->Jump();
					break;
                case SDLK_d:    //d button pressed
                    instance2->GetPlayer()->MoveRight();
                    break;
                case SDLK_a:    //a button pressed
                    instance2->GetPlayer()->MoveLeft();
                    break;
                case SDLK_w:    //w button pressed
                    instance2->GetPlayer()->Jump();
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
					if (instance1->GetPlayer()->GetVelocity().x > 0)   //If you were moving right
					{
						instance1->GetPlayer()->StopMove();    //Stop moving right
					}
					break;
				case SDLK_LEFT:     //Left button released
					if (instance1->GetPlayer()->GetVelocity().x < 0)   //If you were moving left
					{
						instance1->GetPlayer()->StopMove();    //Stop moving left
					}
					break;
                case SDLK_d:    //d button released
                    if (instance2->GetPlayer()->GetVelocity().x > 0) //If you were moving right
                    {
                        instance2->GetPlayer()->StopMove();   //Stop moving left
                    }
                    break;
                case SDLK_a:    //a button released
                    if (instance2->GetPlayer()->GetVelocity().x < 0) //If you were moving left
                    {
                        instance2->GetPlayer()->StopMove();  //Stop moving left
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
		if (!instance1->Update()) {return 1;}    //Update
		if (!instance2->Update()) {return 1;}    //Update
		if (SDL_GetTicks() - time <= 1000.0/FPS)    //Capping the frame rate: if not enough time has passed
		{
		    SDL_Delay((Uint32)(1000.0/FPS - SDL_GetTicks() + time));  //Then wait until enough time has passed
		}
	}

	instance1->CleanUp();    //Clean up all dynamically allocated memory
	instance2->CleanUp();
	delete instance1;
	delete instance2;

	return 0;
}

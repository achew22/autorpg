#include "constants.h"
#include "Graphics.h"
#include "Character.h"
#include "Dynamic_Object.h"
#include "Torch.h"
#include <stdio.h>

Character *player1 = NULL;	//A pointer to the player1 instance of the character class
Character *player2 = NULL;    //

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
					player1->MoveRight();
					break;
				case SDLK_LEFT:     //Left button pressed
					player1->MoveLeft();
					break;
				case SDLK_UP:		//Up button pressed
					player1->Jump();
					break;
                case SDLK_d:    //d button pressed
                    player2->MoveRight();
                    break;
                case SDLK_a:    //a button pressed
                    player2->MoveLeft();
                    break;
                case SDLK_w:    //w button pressed
                    player2->Jump();
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
					if (player1->GetVelocity().x > 0)   //If you were moving right
					{
						player1->StopMove();    //Stop moving right
					}
					break;
				case SDLK_LEFT:     //Left button released
					if (player1->GetVelocity().x < 0)   //If you were moving left
					{
						player1->StopMove();    //Stop moving left
					}
					break;
                case SDLK_d:    //d button released
                    if (player2->GetVelocity().x > 0) //If you were moving right
                    {
                        player2->StopMove();   //Stop moving left
                    }
                    break;
                case SDLK_a:    //a button released
                    if (player2->GetVelocity().x < 0) //If you were moving left
                    {
                        player2->StopMove();  //Stop moving left
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

#include "include.h"
#include "Graphics.h"
#include "Character.h"
#include "Dynamic_Object.h"
#include "Torch.h"
#include <stdio.h>

SDL_Event SDLEvent;	//The main event that we poll to get key presses, releases, etc.

class Dynamic_Object;	//Forward declaration of this class, so that the below doesn't get mad
class Character;	//Forward declaration of this class, so that the below doesn't get mad
std::vector<Dynamic_Object*> interactObjectList;
std::vector<Dynamic_Object*> backgroundObjectList;
std::list<Dynamic_Object*> collisionList;
	//The lists of all dynamic objects created in the game.

Character *hero = NULL;	//A pointer to the hero instance of the character class

int main(int argc, char *args[])
{
    Graphics *graphics = new Graphics();
	if (!graphics->Init()) {printf("Init failed\n"); return 1;} else {printf("Init Success\n");}
	if (!graphics->LoadFiles()) {printf("LoadFiles failed\n"); return 1;} else {printf("LoadFiles Success\n");}
	graphics->SetUpDynamicObjects();
	graphics->CreateBackground();
	if (!graphics->Update()) {printf("Update failed\n"); return 1;} else {printf("Update Success\n");}

    bool quit = false;
	while (quit != true)
	{
		if (SDL_PollEvent(&SDLEvent))
		{
			if (SDLEvent.type == SDL_KEYDOWN)
			{
				switch (SDLEvent.key.keysym.sym)
				{
				case SDLK_RIGHT:
					hero->SetVelocity(1, 0);
					if (!graphics->Update()) {return 1;}
					break;
				case SDLK_LEFT:
					hero->SetVelocity(-1, 0);
					if (!graphics->Update()) {return 1;}
					break;
				case SDLK_ESCAPE:
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
				case SDLK_RIGHT:
					if (hero->GetVelocityX() > 0)
					{
						hero->SetVelocity(0, 0);
					}
					if (!graphics->Update()) {return 1;}
					break;
				case SDLK_LEFT:
					if (hero->GetVelocityX() < 0)
					{
						hero->SetVelocity(0, 0);
					}
					if (!graphics->Update()) {return 1;}
					break;
                default:
                    break;
				}
			}
			else if (SDLEvent.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		if (!graphics->Update()) {return 1;}
	}

	graphics->CleanUp();
	delete graphics;

	return 0;
}

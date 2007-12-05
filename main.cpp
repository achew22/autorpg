#include "include.h"
#include "Graphics.h"
#include "Character.h"
#include "Dynamic_Object.h"
#include "Torch.h"
#include <stdio.h>

int main(int argc, char *args[])
{
    Graphics *graphics = new Graphics();
	if (!graphics->Init()) {printf("Init failed\n"); return 1;}
	if (!graphics->LoadFiles()) {printf("LoadFiles failed\n"); return 1;}
	graphics->SetUpDynamicObjects();
	graphics->CreateBackground();
	if (!graphics->Update()) {printf("Update failed\n"); return 1;}

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

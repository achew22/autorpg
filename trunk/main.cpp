#include "include.h"
#include <stdio.h>

void SetUpDynamicObjects()
{
	Character *newHero = new Character(20, 32, 48, 64, characters);
	std::vector<SDL_Rect> heroAnimRight;
	heroAnimRight.resize(4);
	heroAnimRight[0].x = 0;
	heroAnimRight[0].y = 64;
	heroAnimRight[0].w = 48;
	heroAnimRight[0].h = 64;

	heroAnimRight[1].x = 48;
	heroAnimRight[1].y = 64;
	heroAnimRight[1].w = 48;
	heroAnimRight[1].h = 64;

	heroAnimRight[2].x = 96;
	heroAnimRight[2].y = 64;
	heroAnimRight[2].w = 48;
	heroAnimRight[2].h = 64;

	heroAnimRight[3] = heroAnimRight[1];

	std::vector<SDL_Rect> heroAnimLeft;
	heroAnimLeft.resize(4);
	heroAnimLeft[0].x = 48;
	heroAnimLeft[0].y = 192;
	heroAnimLeft[0].w = 48;
	heroAnimLeft[0].h = 64;

	heroAnimLeft[1].x = 0;
	heroAnimLeft[1].y = 192;
	heroAnimLeft[1].w = 48;
	heroAnimLeft[1].h = 64;

	heroAnimLeft[2] = heroAnimLeft[0];

	heroAnimLeft[3].x = 96;
	heroAnimLeft[3].y = 192;
	heroAnimLeft[3].w = 48;
	heroAnimLeft[3].h = 64;

	newHero->AddAnimation(heroAnimLeft);
	newHero->AddAnimation(heroAnimRight);

	hero = newHero;
	allDynamicObjects.push_back( (Dynamic_Object*)newHero);

	for (int i=0; i<10; i++)
	{
		Character *newEnemy = new Character(400*i, 32, 48, 64, characters);
		std::vector<SDL_Rect> enemyAnimRight;
		enemyAnimRight.resize(4);
		enemyAnimRight[0].x = 0;
		enemyAnimRight[0].y = 64;
		enemyAnimRight[0].w = 48;
		enemyAnimRight[0].h = 64;

		enemyAnimRight[1].x = 48;
		enemyAnimRight[1].y = 64;
		enemyAnimRight[1].w = 48;
		enemyAnimRight[1].h = 64;

		enemyAnimRight[2].x = 96;
		enemyAnimRight[2].y = 64;
		enemyAnimRight[2].w = 48;
		enemyAnimRight[2].h = 64;

		enemyAnimRight[3] = enemyAnimRight[1];

		std::vector<SDL_Rect> enemyAnimLeft;
		enemyAnimLeft.resize(4);
		enemyAnimLeft[0].x = 48;
		enemyAnimLeft[0].y = 192;
		enemyAnimLeft[0].w = 48;
		enemyAnimLeft[0].h = 64;

		enemyAnimLeft[1].x = 0;
		enemyAnimLeft[1].y = 192;
		enemyAnimLeft[1].w = 48;
		enemyAnimLeft[1].h = 64;

		enemyAnimLeft[2] = enemyAnimLeft[0];

		enemyAnimLeft[3].x = 96;
		enemyAnimLeft[3].y = 192;
		enemyAnimLeft[3].w = 48;
		enemyAnimLeft[3].h = 64;

		newEnemy->AddAnimation(enemyAnimLeft);
		newEnemy->AddAnimation(enemyAnimRight);
		newEnemy->SetVelocity(-1, 0);

		allDynamicObjects.push_back( (Dynamic_Object*)newEnemy);
	}

	for (int i=0; i<40; i++)
	{
		Dynamic_Object *newTorch = new Torch(100*i + 48, dynamicSprites);
		allDynamicObjects.push_back(newTorch);
	}
}

bool HandleEvents()
{
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
					if (!Graphics::Update()) {return false;}
					break;
				case SDLK_LEFT:
					hero->SetVelocity(-1, 0);
					if (!Graphics::Update()) {return false;}
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
					if (!Graphics::Update()) {return false;}
					break;
				case SDLK_LEFT:
					if (hero->GetVelocityX() < 0)
					{
						hero->SetVelocity(0, 0);
					}
					if (!Graphics::Update()) {return false;}
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
		if (!Graphics::Update()) {return false;}
	}
	return quit;
}

int main(int argc, char *args[])
{
	if (!Graphics::Init()) {printf("Init failed\n"); return 1;}
	if (!Graphics::LoadFiles()) {printf("LoadFiles failed\n"); return 1;}
	SetUpDynamicObjects();
	Graphics::CreateBackground();
	if (!Graphics::Update()) {printf("Update failed\n"); return 1;}

	if (!HandleEvents()) {printf("HandleEvents failed\n");  return 1;}

	Graphics::CleanUp();

	return 0;
}

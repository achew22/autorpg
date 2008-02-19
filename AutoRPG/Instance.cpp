#include "Instance.h"
#include "Background_Object.h"
#include "Interact_Object.h"
#include "Character.h"
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include "constants.h"
#include "Point.h"
#include "Dynamic_Object.h"
#include <vector>
#include "Torch.h"
#include "Graphics.h"

//The constructor, locx and locy determine where this particular Instance module will load it's stuff
Instance::Instance(int locx, int locy, SDL_Surface* theScreen)
{
    dynamicLayer = NULL;
    background = NULL;
    dynamicSprites = NULL;
    bgTiles = NULL;
    screen = theScreen;
    characters = NULL;
    location.x = locx;
    location.y = locy;
}

//Loads the necessary files to be used. Returns false if there was some error, otherwise returns true
bool Instance::LoadFiles(std::string dynamicSpritesFile, std::string bgTilesFile, std::string charactersFile)
{
	background = SDL_CreateRGBSurface(SDL_SWSURFACE, 4000, 200, SCREEN_BPP, NULL, NULL, NULL, NULL);
	dynamicLayer = SDL_CreateRGBSurface(SDL_SWSURFACE, 4000, 200, SCREEN_BPP, NULL, NULL, NULL, NULL);
	dynamicSprites = Graphics::LoadImage(dynamicSpritesFile.c_str(), 0, 0xFF, 0xFF);
	bgTiles = Graphics::LoadImage(bgTilesFile.c_str(), 0, 0, 0xFF);
	characters = Graphics::LoadImage(charactersFile.c_str(), 0xFF, 0, 0);

	tempSpriteSheet = new Sprite_Sheet(48, 64, 48*6, 64*4, characters);

	if ((dynamicSprites == NULL) || (bgTiles == NULL) || (characters == NULL)) {return false;}
	return true;
}

//Frees all of the surfaces that were declared, unless they were already freed, then quits SDL
void Instance::CleanUp()
{
	if (background != NULL)
	{
		printf("background to be freed\n");
		SDL_FreeSurface(background);
		printf("background freed\n");
	}
	if (dynamicSprites != NULL)
	{
		printf("dynamicSprites to be freed\n");
		SDL_FreeSurface(dynamicSprites);
        printf("dynamicSprites freed\n");
	}
	if (bgTiles != NULL)
	{
		printf("bgTiles to be freed\n");
		SDL_FreeSurface(bgTiles);
		printf("bgTiles freed\n");
	}
	if (characters != NULL)
	{
		printf("characters to be freed\n");
		SDL_FreeSurface(characters);
		printf("characters freed\n");
	}
	if (dynamicLayer != NULL)
	{
		printf("dynamicLayer to be freed\n");
		SDL_FreeSurface(dynamicLayer);
		printf("dynamicLayer freed\n");
	}
}

//Creates the background layer, currently just a white rectangle
void Instance::CreateBackground()
{
	SDL_FillRect(background, &background->clip_rect, SDL_MapRGB(background->format, 0xFF, 0xFF, 0xFF));
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
		screenLocation.x = (pos.x - 20);
	}
	else
	{
		screenLocation.x = 0;
	}

	//Keep the screenLocation within the level itself
	if (screenLocation.x < 0)
	{
		screenLocation.x = 0;
	}
	else if (screenLocation.x > 3800)
	{
		screenLocation.x = 3800;
	}

	//Apply the background to the dynamicLayer
	Graphics::ApplyImage(0, 0, background, dynamicLayer);

	//Check every dynamicObject in our main lists to see if it is close enough to the screen to warrant an update
	//and then call its update function. I am afraid that this is really inefficient to do EVERY FRAME, but I haven't
	//yet fixed this problem
	for (std::vector<Dynamic_Object*>::iterator i = backgroundObjectList.begin(); i != backgroundObjectList.end(); ++i)
	{
		Point pos = (*i)->GetPosition();
		if ((pos.x > screenLocation.x - 100) && (pos.x < screenLocation.x + screenLocation.w + 100)
			&& (pos.y > screenLocation.y - 50) && (pos.y < screenLocation.y + screenLocation.h + 50))
		{
			(*i)->Update();
		}
	}
	for (std::vector<Dynamic_Object*>::iterator i = interactObjectList.begin(); i != interactObjectList.end(); ++i)
	{
		Point pos = (*i)->GetPosition();
		if ((pos.x > screenLocation.x - 100) && (pos.x < screenLocation.x + screenLocation.w + 100)
			&& (pos.y > screenLocation.y - 50) && (pos.y < screenLocation.y + screenLocation.h + 50))
		{
			(*i)->Update();
		}
	}
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

	tempSpriteSheet->ApplySprite(0, 0, 5, dynamicLayer); //Testing out the Sprite_Sheet Class

	//Apply the dynamic layer to the screen layer, with the clip around the screenLocation
	Graphics::ApplyImage(location.x, location.y, dynamicLayer, screen, &screenLocation);

	return true;
}

void Instance::SetUpDynamicObjects()
{
	player = new Character(20, 32, 48, 64, characters, dynamicLayer, "player");
	characterList.insert(characterList.begin(), std::pair<std::string, Character*>("player", player));

	for (int i=0; i<40; i++)
	{
		Dynamic_Object *newTorch = new Torch(100*i + 48, dynamicSprites, dynamicLayer);
		backgroundObjectList.push_back(newTorch);
	}
}

Character* Instance::GetPlayer()
{
    return player;
}

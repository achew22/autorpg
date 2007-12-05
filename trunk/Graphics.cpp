#include "Character.h"
#include "Dynamic_Object.h"
#include "Graphics.h"

//Load the image at filename with the color specified by red, green, and blue as the transparent color. The default
//transparency color is bright blue, so it needn't be specified. Returns a pointer to this created surface
SDL_Surface *Graphics::LoadImage(std::string filename, int red = 0, int green = 255, int blue = 255)
{
	SDL_Surface *loadedImage = NULL;
	SDL_Surface *optimizedImage = NULL;
	loadedImage = IMG_Load(filename.c_str());
	if (loadedImage != NULL)
	{
		optimizedImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
		if (optimizedImage != NULL)
		{
			Uint32 colorKey = SDL_MapRGB(optimizedImage->format, red, green, blue);
			SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorKey);
		}
	}
	return optimizedImage;
}

//Apply the surface from source to destination, at the position x, y and with the clip defined by clip, which defaults to the entire surface
void Graphics::ApplyImage(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip = NULL)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, clip, destination, &offset);
}

//Initialize the SDL libraries to be used, returns false if it fails
bool Graphics::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {return false;}
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE/* | SDL_NOFRAME*/);
	if (screen == NULL) {return false;}
	SDL_WM_SetCaption("AutoRPG - Development", NULL);
	return true;
}

//Loads the necessary files to be used. Returns false if there was some error, otherwise returns true
bool Graphics::LoadFiles()
{
	background = SDL_CreateRGBSurface(SDL_SWSURFACE, 4000, 100, SCREEN_BPP, NULL, NULL, NULL, NULL);
	dynamicLayer = SDL_CreateRGBSurface(SDL_SWSURFACE, 4000, 100, SCREEN_BPP, NULL, NULL, NULL, NULL);
	dynamicSprites = LoadImage("images/dynamicobjects2x.png", 0, 0xFF, 0xFF);
	bgTiles = LoadImage("images/bgTiles2x.png", 0, 0, 0xFF);
	characters = LoadImage("images/miniDungeonCharSprites2x.png", 0xFF, 0, 0);
	if ((dynamicSprites == NULL) || (bgTiles == NULL) || (characters == NULL)) {return false;}
	return true;
}

//Frees all of the surfaces that were declared, unless they were already freed, then quits SDL
void Graphics::CleanUp()
{
	if (background != NULL)
	{
		SDL_FreeSurface(background);
	}
	if (dynamicSprites != NULL)
	{
		SDL_FreeSurface(dynamicSprites);
	}
	if (bgTiles != NULL)
	{
		SDL_FreeSurface(bgTiles);
	}
	if (characters != NULL)
	{
		SDL_FreeSurface(characters);
	}
	if (dynamicLayer != NULL)
	{
		SDL_FreeSurface(dynamicLayer);
	}
	SDL_Quit();
}

//Creates the background layer randomly from the background tiles defined in images/bgTiles2x.png
void Graphics::CreateBackground()
{
	if (bgTiles == NULL)
	{
		bgTiles = LoadImage("images/bgTiles2x.png", 0, 0, 0xFF);
	}
	SDL_FillRect(background, &background->clip_rect, SDL_MapRGB(background->format, 0xFF, 0xFF, 0xFF));

	SDL_Rect bgClip;
	bgClip.w = 200;
	bgClip.h = 100;
	for (int i=0; i<20; i++)
	{
		bgClip.x = rand()%4 * 200;
		bgClip.y = rand()%3 * 100;
		ApplyImage(200*i, 0, bgTiles, background, &bgClip);
	}
	SDL_FreeSurface(bgTiles);
}

//Updates every item in the allDynamicObjects list, if it is within 400 pixels of the screen. It then flips the buffers to display the frame.
//Returns false if an error occurs
bool Graphics::Update()
{
	SDL_Rect screenLocation;	//Defines essentially where the camera is at
	screenLocation.h = 100;
	screenLocation.w = 200;
	screenLocation.y = 0;

	//Keep the screenLocation relative to the hero's position
	if (hero != NULL)
	{
		int x, y;
		hero->GetPosition(x, y);
		screenLocation.x = x - 20;
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
	ApplyImage(0, 0, background, dynamicLayer);

	//Check every dynamicObject in our main list to see if it is close enough to the screen to warrant an update
	//and then call its update function. I am afraid that this is really inefficient to do EVERY FRAME, but I haven't
	//yet fixed this problem
	for (int i = int(allDynamicObjects.size()) - 1; i >= 0; i--)
	{
		int x, y;
		allDynamicObjects[i]->GetPosition(x, y);
		if ((x > screenLocation.x - 100) && (x < screenLocation.x + screenLocation.w + 100)
			&& (y > screenLocation.y - 50) && (y < screenLocation.y + screenLocation.h + 50))
		{
			allDynamicObjects[i]->Update();
		}
	}

	//Apply the dynamic layer to the screen layer, with the clip around the screenLocation
	ApplyImage(0, 0, dynamicLayer, screen, &screenLocation);

	//Flip the buffers and return false if this fails
	if (SDL_Flip(screen) == -1) {return false;}
	return true;
}
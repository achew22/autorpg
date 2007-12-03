#ifndef GRAPHICS_H
#define GRAPHICS_H

SDL_Surface *Graphics::LoadImage(std::string filename, int red, int green, int blue)
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

void Graphics::ApplyImage(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip = NULL)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, clip, destination, &offset);
}

bool Graphics::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {return false;}
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE/* | SDL_NOFRAME*/);
	if (screen == NULL) {return false;}
	SDL_WM_SetCaption("Mini Dungeon", NULL);
	return true;
}

bool Graphics::LoadFiles()
{
	background = SDL_CreateRGBSurface(SDL_SWSURFACE, 4000, 100, SCREEN_BPP, NULL, NULL, NULL, NULL);
	dynamicLayer = SDL_CreateRGBSurface(SDL_SWSURFACE, 4000, 100, SCREEN_BPP, NULL, NULL, NULL, NULL);
	dynamicSprites = LoadImage("dynamicobjects2x.png", 0, 0xFF, 0xFF);
	bgTiles = LoadImage("bgTiles2x.png", 0, 0, 0xFF);
	characters = LoadImage("miniDungeonCharSprites2x.png", 0xFF, 0, 0);
	if ((dynamicSprites == NULL) || (bgTiles == NULL) || (characters == NULL)) {return false;}
	return true;
}

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

void Graphics::CreateBackground()
{
	if (bgTiles == NULL)
	{
		bgTiles = LoadImage("bgTiles2x.png", 0, 0, 0xFF);
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

bool Graphics::Update()
{
	SDL_Rect screenLocation;
	screenLocation.h = 100;
	screenLocation.w = 200;
	screenLocation.y = 0;
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
	if (screenLocation.x < 0)
	{
		screenLocation.x = 0;
	}
	else if (screenLocation.x > 3800)
	{
		screenLocation.x = 3800;
	}

	ApplyImage(0, 0, background, dynamicLayer);
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
	ApplyImage(0, 0, dynamicLayer, screen, &screenLocation);
	if (SDL_Flip(screen) == -1) {return false;}
	return true;
}

#endif

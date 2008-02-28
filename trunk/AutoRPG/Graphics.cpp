#include "Graphics.h"
#include "constants.h"
#include <string>

//Load the image at filename with the color specified by red, green, and blue as the transparent color. The default
//transparency color is bright blue, so it needn't be specified. Returns a pointer to this created surface
SDL_Surface* Graphics::LoadImage(std::string filename, int red, int green, int blue)
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
void Graphics::ApplyImage(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip)
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
        screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF/* | SDL_NOFRAME*/);
        if (screen == NULL) {return false;}
        SDL_WM_SetCaption("AutoRPG - Development", NULL);
        return true;
}

SDL_Surface* Graphics::GetScreen()
{
    return screen;
}

//Updates the main screen, this way everything is hunky-dory and the screen only gets flipped once per frame
bool Graphics::Update()
{
	//Flip the buffers and return false if this fails
	if (SDL_Flip(screen) == -1) {return false;}
    return true;
}

void Graphics::CleanUp()
{
    SDL_Quit();
}

#include "Sprite_Sheet.h"
#include "constants.h"
#include <string>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

Sprite_Sheet::Sprite_Sheet(int wOfSprite, int hOfSprite, std::string filename, int red, int green, int blue)
{
    //Loads the file to the surface screen, with the alphamask indicated by red, green, and blue
    SDL_Surface *loadedImage = NULL;
	SDL_Surface *sheet = NULL;
	loadedImage = IMG_Load(filename.c_str());
	if (loadedImage != NULL)
	{
		sheet = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);   //Free this memory
	}

    int numx = (sheet->w)/wOfSprite;  //Number of sprites in the x direction
    printf("numx = %i\n", numx);
    int numy = (sheet->h)/hOfSprite;  //Number of sprites in the y direction
    printf("numy = %i\n", numy);

    //This part sets up the vector of sprites to empty surfaces
    sprites.resize(numx*numy);
    for (int i = 0; i < numx*numy; i++)
    {
        sprites[i] = SDL_CreateRGBSurface(SDL_SWSURFACE, wOfSprite, hOfSprite, SCREEN_BPP, NULL, NULL, NULL, NULL);
    }
    printf("sprites is now of size: %i\n", sprites.size());
    SDL_Rect clip;
    clip.w = wOfSprite;
    clip.h = hOfSprite;

    //Now set every one of those surfaces to be the individual sprite, with the proper alpha
    for (int i = 0; i < numy; i++)
    {
        clip.y = i * hOfSprite;
        for (int j = 0; j < numx; j++)
        {
            clip.x = j * wOfSprite;
            SDL_SetColorKey(sprites[i*numx + j], SDL_SRCCOLORKEY, SDL_MapRGB(sprites[i*numx + j]->format, red, green, blue));

            SDL_BlitSurface(sheet, &clip, sprites[i*numx + j], NULL);
        }
    }

    SDL_FreeSurface(sheet); //Free this memory
}

Sprite_Sheet::~Sprite_Sheet()
{
    for (int i = 0; i < sprites.size(); i++)
    {
        if (sprites[i] != NULL)
        {
            SDL_FreeSurface(sprites[i]);
        }
    }
}

void Sprite_Sheet::ApplySprite(int x, int y, int spriteNum, SDL_Surface* destination)
{
    if (spriteNum >= sprites.size() || spriteNum < 0)
    {
        printf("ApplySprite had a sprite out of range\n");
        return;
    }
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(sprites[spriteNum], NULL, destination, &offset);
}

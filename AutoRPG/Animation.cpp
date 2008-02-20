#include "Animation.h"
#include <vector>
#include <SDL/SDL.h>
#include <math.h>

//The constructor. Needs the name of the file from which to get the sprites, the width and height of the sprites, the
//indexes of all of the sprites (ie which sprites to use in which order), the clip time, and the color for the alpha mask
Animation::Animation(std::string file, int spriteW, int spriteH, std::vector<int> spriteIndexes, int clipTime /*default: 120*/,
    int red /*default: 0*/, int green /*default: 255*/, int blue /*default: 255*/)
{
    spriteSheet = Sprite_Sheet::FindSheet(file);    //See if this animation already exists in loaded memory
    if (spriteSheet == NULL)    //If it doesn't, load up a new one
    {
        spriteSheet = new Sprite_Sheet(spriteW, spriteH, file, red, green, blue);
    }

    sprites.resize(spriteIndexes.size());
    for (int i = 0; i < sprites.size(); i++)
    {
        sprites[i] = spriteIndexes[i];
    }
    clipLength = clipTime;
    currentSprite = sprites.begin();
    lastAnimTime = SDL_GetTicks();
}

//Applys whatever the current sprite of the animation is to the surface in destination at the coordinates x, y
void Animation::ApplyCurrentSprite(int x, int y, SDL_Surface* destination)
{
    if (SDL_GetTicks() - lastAnimTime > clipLength) //If enough time has passed
    {
        currentSprite ++;   //Go to the next sprite
        if (currentSprite == sprites.end()) //If you are at the end, go back to the beginning
        {
            currentSprite = sprites.begin();
        }
        lastAnimTime = SDL_GetTicks();
    }
    spriteSheet->ApplySprite(x, y, (*currentSprite), destination);  //Apply sprite
}

//What it says
void Animation::ApplyFirstSprite(int x, int y, SDL_Surface* destination)
{
    spriteSheet->ApplySprite(x, y, (*(sprites.begin())), destination);
}

//What it says
void Animation::ApplyLastSprite(int x, int y, SDL_Surface* destination)
{
    spriteSheet->ApplySprite(x, y, (*(sprites.rbegin())), destination);
}

//Begin the animation (ie reset the animation to the beginning
void Animation::Begin()
{
    lastAnimTime = SDL_GetTicks();
    currentSprite = sprites.begin();
}

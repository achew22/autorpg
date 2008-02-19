#include "Sprite_Sheet.h"
#include "constants.h"
#include "Graphics.h"

Sprite_Sheet::Sprite_Sheet(int wOfSprite, int hOfSprite, int wOfSheet, int hOfSheet, SDL_Surface* sheet)
{
    int numx = wOfSheet/wOfSprite;
    printf("numx = %i\n", numx);
    int numy = hOfSheet/hOfSprite;
    printf("numy = %i\n", numy);
    sprites.resize(numx*numy);
    printf("sprites is now of size: %i\n", sprites.size());
//    SDL_Surface* temp = SDL_CreateRGBSurface(SDL_SWSURFACE, wOfSprite, hOfSprite, SCREEN_BPP, NULL, NULL, NULL, NULL);
    SDL_Rect clip;
    clip.w = wOfSprite;
    clip.h = hOfSprite;

    for (int i = 0; i < numx; i++)
    {
        clip.x = i * wOfSprite;
        for (int j = 0; j < numy; j++)
        {
            SDL_Surface* temp = SDL_CreateRGBSurface(SDL_SWSURFACE, wOfSprite, hOfSprite, SCREEN_BPP, NULL, NULL, NULL, NULL);
            //SDL_SetAlpha(temp, NULL, 0);
            clip.y = j * hOfSprite;
            Graphics::ApplyImage(0, 0, sheet, temp, &clip);
            sprites.push_back(temp);
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
    Graphics::ApplyImage(x, y, sprites[spriteNum], destination);
}

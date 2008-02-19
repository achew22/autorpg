#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <vector>

//A class to handle sprite sheets. Note: all of the sprites in the sheet must be the same size.
//By setting this up when the area is loaded (which should take under a second), we save a lot
//of blitting time between frames (which is where it counts).
class Sprite_Sheet
{
private:
    std::vector<SDL_Surface*> sprites;
public:
    Sprite_Sheet(int wOfSprite, int hOfSprite, int wOfSheet, int hOfSheet, SDL_Surface* sheet);
    void ApplySprite(int x, int y, int spriteNum, SDL_Surface* destination);
};

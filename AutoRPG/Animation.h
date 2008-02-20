#ifndef ANIMATION_H
#define ANIMATION_H

#include "constants.h"
#include "Sprite_Sheet.h"
#include <vector>
#include <SDL/SDL.h>
#include <string>
//Defines the Animation Class. An animation class is just a convenient way to store and manage
//a series of clips.
class Animation
{
private:
    Sprite_Sheet* spriteSheet;  //A pointer to the Sprite_Sheet class instance containing
        //all of the sprites for this animation
    std::vector<int> sprites;
    std::vector<int>::iterator currentSprite;
    int lastAnimTime;
    int clipLength;
public:
	Animation(std::string file, int spriteW, int spriteH, std::vector<int> spriteIndexes, int clipTime = 120,
        int red = 0, int green = 255, int blue = 255);  //Pass in the name
        //of the file containing the sprites for this animation, a vector of which sprites belong
        //in the animation (in order), the width and height of the sprites, the time between sprites (in ms),
        //and the color of the alpha mask
	void ApplyCurrentSprite(int x, int y, SDL_Surface* destination);
	void ApplyFirstSprite(int x, int y, SDL_Surface* destination);
	void ApplyLastSprite(int x, int y, SDL_Surface* destination);
	void Begin();
};

#endif

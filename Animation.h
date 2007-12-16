#ifndef ANIMATION_H
#define ANIMATION_H

#include "constants.h"
#include <vector>
#include <SDL/SDL.h>
//Defines the Animation Class. An animation class is just a convenient way to store a series of
//clips, and is really just a wrapper for a vector containing those clips. Now that I think about it,
//why did I invent this class?
class Animation
{
private:
	std::vector<SDL_Rect> animSeries;	//Stores the clips
public:
	Animation(std::vector<SDL_Rect> animation);
	Animation() {};
	~Animation();
	SDL_Rect operator [](int i);	//Simply reference a clip by its index
	Animation operator =(Animation anim);
	int size();	//Return the number of frames in the animation
	SDL_Rect GetFinalClip();	//Return the first clip
	SDL_Rect GetFirstClip();	//Return the final clip
};

#endif

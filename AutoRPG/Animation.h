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
    SDL_Rect* currentClip;   //Which frame of the animation is this on?
	int lastAnimTime;   //The time that the animation was last updated (ms)
	int clipLength;     //The length of time that each clip in this animation is (ms)
	int animationLoc;   //the index value of the current clip this animation is on
	int numClips;   //The number of clips in the animation
public:
	Animation(std::vector<SDL_Rect> animation, int clipTime = 120);
	~Animation();
	SDL_Rect operator [](int i);	//Simply reference a clip by its index
	SDL_Rect GetClip(int index);    //Same as above, but in function form
	Animation operator =(Animation anim);
	void Begin();   //Begin this animation loop
	void Update();  //Update this animation loop
	int size();	//Return the number of frames in the animation
	SDL_Rect GetCurrentClip();  //Return the current clip
	SDL_Rect GetFinalClip();	//Return the first clip
	SDL_Rect GetFirstClip();	//Return the final clip
};

#endif

#include "Animation.h"
#include <vector>
#include <SDL/SDL.h>
#include <math.h>

//The constructor
Animation::Animation(std::vector<SDL_Rect> animation, int clipTime /*default: 120*/)
{
	for (int i=0; i<int(animation.size()); i++)
	{
		animSeries.push_back(animation[i]);
	}
	currentClip = &animSeries[0];
	lastAnimTime = SDL_GetTicks();
	animationLoc = 0;
	clipLength = clipTime;
	numClips = animSeries.size();
}

//Freeing the vector memory. I think that this should automatically be done when the
//default constructor is called, but I wanted to be safe
Animation::~Animation()
{
	animSeries.clear();
}

//Return an individual clip based on its index
SDL_Rect Animation::operator [](int i)
{
	return GetClip(i);
}

//Return an individual clip based on its index
SDL_Rect Animation::GetClip(int index)
{
    if (index < int(animSeries.size()))
	{
		return animSeries[index];
	}
	else
	{
		SDL_Rect newRect = {0, 0, 0, 0};
		return newRect;
	}
}

Animation Animation::operator =(Animation anim)
{
	for (int i=0; i<int(anim.numClips); i++)
	{
		animSeries.push_back(anim.animSeries[i]);
	}
	return anim;
}

void Animation::Begin()
{
    lastAnimTime = SDL_GetTicks();
    animationLoc = 0;
    currentClip = &animSeries[0];
}

void Animation::Update()
{
    if (SDL_GetTicks() - lastAnimTime >= clipLength)    //Only update if enough time has passed
    {
        animationLoc += floor((SDL_GetTicks() - lastAnimTime)/((double)clipLength));
        while (animationLoc >= numClips)
        {
            animationLoc -= numClips;
        }
        currentClip = &animSeries[animationLoc];
        lastAnimTime = SDL_GetTicks();
    }
}

//Returns the number of clips in this animation
int Animation::size()
{
	return numClips;
}

SDL_Rect Animation::GetCurrentClip()
{
    return *currentClip;
}

//Returns the final clip in the animation
SDL_Rect Animation::GetFinalClip()
{
	if (numClips != 0)
	{
		return animSeries[numClips - 1];
	}
	return SDL_Rect();
}

//Return the first clip in the animation
SDL_Rect Animation::GetFirstClip()
{
	if (numClips != 0)
	{
		return animSeries[0];
	}
	return SDL_Rect();
}

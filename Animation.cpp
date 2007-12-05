#include "Animation.h"

Animation::Animation(std::vector<SDL_Rect> animation)
{
	for (int i=0; i<int(animation.size()); i++)
	{
		animSeries.push_back(animation[i]);
	}
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
	if (i < int(animSeries.size()))
	{
		return animSeries[i];
	}
	else
	{
		SDL_Rect newRect = {0, 0, 0, 0};
		return newRect;
	}
}

Animation Animation::operator =(Animation anim)
{
	for (int i=0; i<int(anim.animSeries.size()); i++)
	{
		animSeries.push_back(anim.animSeries[i]);
	}
	return anim;
}

//Returns the number of clips in this animation
int Animation::size()
{
	return animSeries.size();
}

//Returns the final clip in the animation
SDL_Rect Animation::GetFinalClip()
{
	if (animSeries.size() != 0)
	{
		return animSeries[animSeries.size() - 1];
	}
	return SDL_Rect();
}

//Return the first clip in the animation
SDL_Rect Animation::GetFirstClip()
{
	if (animSeries.size() != 0)
	{
		return animSeries[0];
	}
	return SDL_Rect();
}

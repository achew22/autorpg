#ifndef ANIMATION_H
#define ANIMATION_H

Animation::Animation(std::vector<SDL_Rect> animation)
{
	for (int i=0; i<int(animation.size()); i++)
	{
		animSeries.push_back(animation[i]);
	}
}

Animation::~Animation()
{
	animSeries.clear();
}

SDL_Rect Animation::operator [](int i)
{
	if (i < int(animSeries.size()))
	{
		return animSeries[i];
	}
	else
	{
		SDL_Rect newRect;
		newRect.x = newRect.y = newRect.w = newRect.h = 0;
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

int Animation::size()
{
	return animSeries.size();
}

SDL_Rect Animation::GetFinalClip()
{
	if (animSeries.size() != 0)
	{
		return animSeries[animSeries.size() - 1];
	}
	return SDL_Rect();
}

SDL_Rect Animation::GetFirstClip()
{
	if (animSeries.size() != 0)
	{
		return animSeries[0];
	}
	return SDL_Rect();
}

#endif

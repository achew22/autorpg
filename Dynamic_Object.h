#ifndef DYNAMIC_OBJECT_H
#define DYNAMIC_OBJECT_H

Dynamic_Object::Dynamic_Object(int posx, int posy, int width, int height, SDL_Surface *location)
{
	x = posx;
	y = posy;
	w = width;
	h = height;
	objectSurface = location;
	animationLoc = 0;
}

void Dynamic_Object::FreeSurface()
{
	if (objectSurface != NULL)
	{
		SDL_FreeSurface(objectSurface);
	}
}

void Dynamic_Object::AddAnimation(Animation anim)
{
	animList.push_back(anim);
}

void Dynamic_Object::GetPosition(int &posx, int &posy)
{
	posx = x;
	posy = y;
}

bool Dynamic_Object::SetFlag(int index, int value)
{
	if (index < int(flagList.size()))
	{
		flagList[index] = value;
		return true;
	}
	return false;
}

int Dynamic_Object::GetFlag(int index)
{
	if (index < int(flagList.size()))
	{
		return flagList[index];
	}
	return 0;
}

/*Dynamic_Object Dynamic_Object::operator =(Dynamic_Object object)
{
	x = object.x;
	y = object.y;
	w = object.w;
	h = object.h;
	objectSurface = object.objectSurface;
	clip = object.clip;

	return object;
}*/

#endif

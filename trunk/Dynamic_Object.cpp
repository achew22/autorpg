#include "Animation.h"
#include "Dynamic_Object.h"

Dynamic_Object::Dynamic_Object(int posx, int posy, int width, int height, SDL_Surface *sourceSurface, SDL_Surface *destinationSurface)
{
	x = posx;
	y = posy;
	w = width;
	h = height;
	source = sourceSurface;
	destination = destinationSurface;
	animationLoc = 0;

	animList.clear();	//Just make sure that these are all clear
	flagList.clear();
}

//Add an animation to the end of the list
void Dynamic_Object::AddAnimation(Animation anim)
{
	animList.push_back(anim);
}

//Get the position, in x and y
void Dynamic_Object::GetPosition(int &posx, int &posy)
{
	posx = x;
	posy = y;
}

//Set the flag at index to the value. Returns false if that flag doesn't exist
bool Dynamic_Object::SetFlag(int index, int value)
{
	if (index < int(flagList.size()))
	{
		flagList[index] = value;
		return true;
	}
	return false;
}

//Returns the value of the flag at index, if it exists. Otherwise, returns 0
int Dynamic_Object::GetFlag(int index)
{
	if (index < int(flagList.size()))
	{
		return flagList[index];
	}
	return 0;
}

#include "Background_Object.h"

std::vector<Dynamic_Object*> Background_Object::backgroundObjectList;

Background_Object::Background_Object(int posx, int posy, int width, int height, SDL_Surface *sourceSurface, SDL_Surface *destinationSurface) :
    Dynamic_Object(posx, posy, width, height, sourceSurface, destinationSurface)
{
    backgroundObjectList.push_back(this);
}

//Will probably be a pure virtual function, since other classes of background objects will inherit from this class
void Background_Object::Update()
{
}

//Clean up the dynamic memory allocated within backgroundObjectList
void Background_Object::CleanUp()
{
    for (std::vector<Dynamic_Object*>::iterator i = backgroundObjectList.begin(); i != backgroundObjectList.end(); i++)
	{
		delete *i;
	}
	backgroundObjectList.clear();
}

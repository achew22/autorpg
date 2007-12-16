#include "Interact_Object.h"

std::vector<Dynamic_Object*> Interact_Object::interactObjectList;

Interact_Object::Interact_Object(int locx, int locy, int width, int height, SDL_Surface *sourceSurface, SDL_Surface *destinationSurface) :
    Dynamic_Object(locx, locy, width, height, sourceSurface, destinationSurface)
{
    interactObjectList.push_back(this);
}

//Eventually the update function for the interact object. Most likely, this will be a pure virtual function
//which will only be implemented in sub-classes
void Interact_Object::Update()
{
}

void Interact_Object::CleanUp()
{
	for (std::vector<Dynamic_Object*>::iterator i = interactObjectList.begin(); i != interactObjectList.end(); i++)
	{
		delete *i;
	}
	interactObjectList.clear();
}

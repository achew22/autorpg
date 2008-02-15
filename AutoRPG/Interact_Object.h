#ifndef INTERACT_OBJECT_H
#define INTERACT_OBJECT_H

#include "Dynamic_Object.h"
#include "constants.h"
#include <vector>
#include <SDL/SDL.h>

class Interact_Object : public Dynamic_Object
{
private:
    static std::vector<Dynamic_Object*> interactObjectList;
public:
    Interact_Object(int locs, int locy, int width, int height, SDL_Surface *sourceSurface, SDL_Surface *destinationSurface);
	virtual void Update();	//The virtual function to update all relevant information about the object
	static void CleanUp();  //Cleans up the dynamic memory allocated in interactObjectList
};

#endif

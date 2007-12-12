#ifndef INTERACT_OBJECT_H
#define INTERACT_OBJECT_H

#include "Dynamic_Object.h"
#include "include.h"
#include "Graphics.h"

class Interact_Object : public Dynamic_Object
{
friend bool Graphics::Update();
private:
    static std::vector<Dynamic_Object*> interactObjectList;
public:
    Interact_Object(int posx, int posy, int width, int height, SDL_Surface *sourceSurface, SDL_Surface *destinationSurface);
	virtual void Update();	//The virtual function to update all relevant information about the object
	static void CleanUp();  //Cleans up the dynamic memory allocated in interactObjectList
};

#endif

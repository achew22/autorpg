#ifndef TORCH_H
#define TORCH_H

#include "include.h"
#include "Dynamic_Object.h"
//The torch class, which inherits from dynamic object. Nothing fancy here
class Torch : public Dynamic_Object
{
private:
public:
	Torch(int x, SDL_Surface *sourceSurface, SDL_Surface *destinationSurface);
	virtual void Update();
};

#endif

#ifndef TORCH_H
#define TORCH_H

#include "constants.h"
#include "Background_Object.h"
#include "Animation.h"
#include "Graphics.h"
#include <SDL/SDL.h>

//The torch class, which inherits from dynamic object. Nothing fancy here
class Torch : public Background_Object
{
private:
public:
	Torch(int x, SDL_Surface *sourceSurface, SDL_Surface *destinationSurface);
	virtual void Update();
};

#endif

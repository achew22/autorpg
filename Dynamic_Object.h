#ifndef DYNAMIC_OBJECT_H
#define DYNAMIC_OBJECT_H

#include "constants.h"
#include "Animation.h"
#include <vector>
#include <SDL/SDL.h>
#include "Point.h"

//The base class for everything that has some sort of movement, change, or animation of any sort
//Most other classes will inherit from this class
class Dynamic_Object
{
protected:
	Point pos;
	Point dim;
	double animationLoc;	//The animation location. In other words, the current animation clip that should be used
	SDL_Surface *source;	//A pointer to the surface containing the sprites
	SDL_Surface *destination; //A pointer to the surface where the sprites should be blitted to
	std::vector<Animation> animList;	//A list of the different possible animations
	std::vector<int> flagList;	//A list of all of the flags
public:
	Dynamic_Object(int locx, int locy, int width, int height, SDL_Surface *sourceSurface, SDL_Surface *destinationSurface);
	virtual void Update() {};	//The pure virtual function to update all relevant information about the object
	virtual void AddAnimation(Animation anim);	//Add an animation to the list
	virtual Point GetPosition();	//Get the current position
	bool SetFlag(int index, int value);	//Set one of the flags to a value
	int GetFlag(int index);	//Return the value of one of the flags
};

#endif

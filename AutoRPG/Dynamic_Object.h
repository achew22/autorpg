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
    int lastTime;   //The time (in ms) of the last time Update was called. Allows for the positions, etc. to be adjusted
        //independently of frame rate.
	SDL_Surface *source;	//A pointer to the surface containing the sprites
	SDL_Surface *destination; //A pointer to the surface where the sprites should be blitted to
	std::vector<Animation> animList;	//A list of the different possible animations
	std::vector<int> flagList;	//A list of all of the flags
    Animation* currentAnim; //A pointer to the current animation being used
public:
	Dynamic_Object(int locx, int locy, int width, int height, SDL_Surface *sourceSurface, SDL_Surface *destinationSurface);
	virtual void Update() {};	//The pure virtual function to update all relevant information about the object
	virtual void AddAnimation(Animation anim);	//Add an animation to the list
	virtual Point GetPosition();	//Get the current position
	void ChangeAnimation(Animation* animation);  //Change the currently used animation
	bool SetFlag(int index, int value);	//Set one of the flags to a value
	int GetFlag(int index);	//Return the value of one of the flags
};

#endif

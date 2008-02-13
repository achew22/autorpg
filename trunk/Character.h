#ifndef CHARACTER_H
#define CHARACTER_H

#include "Dynamic_Object.h"
#include "Animation.h"
#include <SDL/SDL.h>
#include <list>
#include "Point.h"
#include "Graphics.h"

//The class for any and all characters in the game.
class Character : public Dynamic_Object
{
friend bool Graphics::Update();
private:
	Point vel;	//Velocity in pixels per second
	Point acc;	//Acceleration in pixels per second per second
	Point init; //Initialized values
	double mass;	//Mass
    static std::list<Character*> characterList;
	enum
	{
		FLAG_FACING,	    //The flag indicating which way the character is facing
		FLAG_AUTOPILOT,	    //The flag indicating whether or not the AI should control this character
		FLAG_JUMPING,       //The flag indicating whether or not the character is jumping
		ANIM_MOVELEFT = 0,  //The animations corresponding to moving left
		ANIM_MOVERIGHT,     //and right
		ANIM_JUMPLEFT,      //jumping animation, facing left
		ANIM_JUMPRIGHT,     //jumping animation, facing right
		ANIM_STILLLEFT,     //the standing still animation, facing left
		ANIM_STILLRIGHT,    //standing still, facing right
	};
public:
	Character(int locx, int locy, int width, int height, SDL_Surface *sourceSurface, SDL_Surface *destinationSurface);
	virtual void AddAnimation(Animation animation);
	virtual void Update();	//Updates the position based on velocity and acceleration, as well as updates
							//the surface on which the character should be updated
    //virtual Point GetPosition();
    static void CleanUp();  //Cleans up all of the dynamically allocated memory stored in characterList
	void SetVelocity(double x, double y);	//Set the velocity
	Point GetVelocity();	//Returns the velocity
	void Jump();
	void StopJump();
	void MoveRight();
	void MoveLeft();
	void StopMove();
	void SetAcceleration(double x, double y); //Set the acceleration
};

#endif

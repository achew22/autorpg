#ifndef CHARACTER_H
#define CHARACTER_H

#include "Dynamic_Object.h"
#include "Animation.h"
#include <SDL/SDL.h>
#include <map>
#include <string>
#include "Point.h"

//The class for any and all characters in the game.
class Character : public Dynamic_Object
{
private:
	Point vel;	//Velocity in pixels per second
	Point acc;	//Acceleration in pixels per second per second
	Point init; //Initialized values
	double mass;	//Mass
	std::string id;  //The unique id of this character
	enum
	{
		FLAG_FACING,	    //The flag indicating which way the character is facing
                                //1-left  2-right  3-up  4-down
		FLAG_AUTOPILOT,	    //The flag indicating whether or not the AI should control this character
                                //0-no  1-yes
		FLAG_JUMPING,       //The flag indicating whether or not the character is jumping
                                //0-no  1-yes
		ANIM_MOVELEFT = 0,  //The animations corresponding to moving left
		ANIM_MOVERIGHT,     //and right
		ANIM_MOVEUP,        //and up
		ANIM_MOVEDOWN,      //and down
		ANIM_JUMPLEFT,      //jumping animation, facing left
		ANIM_JUMPRIGHT,     //jumping animation, facing right
		ANIM_JUMPUP,        //jumping animation, facing up
		ANIM_JUMPDOWN,      //jumping animation, facing down
		ANIM_STILLLEFT,     //the standing still animation, facing left
		ANIM_STILLRIGHT,    //standing still, facing right
		ANIM_STILLUP,       //standing still, facing up
		ANIM_STILLDOWN,     //standing still, facing down
	};
public:
	Character(int locx, int locy, int width, int height, SDL_Surface *sourceSurface, SDL_Surface *destinationSurface, std::string ID);
	virtual void AddAnimation(Animation animation);
	virtual void UpdatePosition();  //Updates the position based on velocity and acceleration
	virtual void UpdateAnimation();	//Updates the surface on which the character should be updated
    //virtual Point GetPosition();
    static void CleanUp();  //Cleans up all of the dynamically allocated memory stored in characterList
	Point GetVelocity();	//Returns the velocity
	void Jump();
	void StopJump();
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();
	void StopMoveHoriz();
	void StopMoveVert();
};

#endif

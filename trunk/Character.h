#ifndef CHARACTER_H
#define CHARACTER_H

#include "include.h"
#include "Dynamic_Object.h"
//The class for any and all characters in the game.
class Character : public Dynamic_Object
{
private:
	double posx, posy;	//Position
	double velx, vely;	//Velocity
	double accx, accy;	//Acceleration
	double mass;	//Mass
	enum
	{
		FLAG_FACING,	//The flag indicating which way the character is facing
		FLAG_AUTOPILOT,	//The flag indicating whether or not the AI should control this character
	};
	enum
	{
		ANIM_MOVELEFT,  //The animations corresponding to moving left
		ANIM_MOVERIGHT, //and right
	};
public:
	Character(int locx, int locy, int width, int height, SDL_Surface *surface);
	virtual void AddAnimation(Animation animation);
	virtual void Update();	//Updates the position based on velocity and acceleration, as well as updates
							//the surface on which the character should be updated
	void SetVelocity(double x, double y);	//Set the velocity
	double GetVelocityX();	//Returns the x velocity
	double GetVelocityY();	//Returns the y velocity
	void SetAcceleration(double x, double y); //Set the acceleration
};

#endif

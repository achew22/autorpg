#include "Character.h"

std::list<Character*> Character::characterList;

Character::Character(int locx, int locy, int width, int height,
					 SDL_Surface *sourceSurface, SDL_Surface *destinationSurface) : Dynamic_Object(locx, locy,
					 width, height, sourceSurface, destinationSurface)
{
	flagList.push_back(0);	//Facing flag: 1-right, -1-left, (0-right)
	flagList.push_back(0);	//AutoPilot flag: 0-off, 1-on
	flagList.push_back(0);  //Jumping flag: 0-not jumping, 1-jumping

	init.x = locx;
	init.y = locy;

	vel.x = 0;
	vel.y = 0;
	acc.x = 0;
	acc.y = 0;
	mass = 100;

	characterList.push_back(this);
}

void Character::AddAnimation(Animation animation)
{
	animList.push_back(animation);
}

void Character::Update()
{
	pos.x += vel.x/5;

	//Position vertically
	if ((vel.y != 0)) {
		//Gravity defined
		pos.y = pos.y - vel.y;
		vel.y = vel.y + (GRAVITY);
		//pos.y = 0;
	}
	if (pos.y > init.y) { // its backwards of what you think -- you want greater than it means your lower
		vel.y = 0; //Set the Y velocity to 0
		pos.y = init.y; //Set the Y position to 0
		flagList[FLAG_JUMPING] = 0;
	}

	//Keep the position within the level, currently 4000 pixels
	if (pos.x < 0)
	{
		pos.x = 0;
	}
	else if (pos.x + dim.x > 4000)
	{
		pos.x = 4000 - dim.x;
	}

	//Every 50 frames, move the animation one clip forward
	animationLoc += vel.x/50.0;

	//If moving right, then set the facing flag to reflect this and update the appropriate surface
	if (vel.x > 0)
	{
		flagList[FLAG_FACING] = 1;
		if (animationLoc >= animList[ANIM_MOVERIGHT].size())	//Keep the animation location less than the size
		{
			animationLoc -= animList[ANIM_MOVERIGHT].size();
		}
		Graphics::ApplyImage(pos.x, pos.y, source, destination,
			&animList[ANIM_MOVERIGHT][int(animationLoc)]);
	}

	//Same, but for left
	else if (vel.x < 0)
	{
		flagList[FLAG_FACING] = -1;
		if (animationLoc < 0)
		{
			animationLoc += animList[ANIM_MOVELEFT].size();
		}
		Graphics::ApplyImage(pos.x, pos.y, source, destination,
			&animList[ANIM_MOVELEFT][int(animationLoc)]);
	}

	//Similar, but now just use the standing there animations
	else
	{
		if (flagList[FLAG_FACING] >= 0)	//Facing right
		{
			Graphics::ApplyImage(pos.x, pos.y, source, destination, &animList[ANIM_MOVERIGHT][1]);
		}
		else	//Facing left
		{
			Graphics::ApplyImage(pos.x, pos.y, source, destination, &animList[ANIM_MOVELEFT].GetFirstClip());
		}
	}
}

void Character::SetVelocity(double x, double y)
{
	vel.x = x;
	/*if (isJumping == false) { //If they are jumping don't let them jump. What would they jump off of? The air?
		vel.y = y;
	}
	if (y > 0) {
		isJumping = true;
	}*/
}

void Character::Jump()
{
    if (flagList[FLAG_JUMPING] == 0)    //If not already jumping
    {
        vel.y = 1;
        flagList[FLAG_JUMPING] = 1;
    }
}

Point Character::GetVelocity()
{
    return vel;
}

void Character::CleanUp()
{
    for (std::list<Character*>::iterator i = characterList.begin(); i != characterList.end(); i++)
	{
		delete *i;
	}
	characterList.clear();
}

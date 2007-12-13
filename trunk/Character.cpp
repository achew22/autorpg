#include "Character.h"
#include "Animation.h"
#include "Dynamic_Object.h"
#include "Graphics.h"

std::list<Character*> Character::characterList;

Character::Character(int locx, int locy, int width, int height,
					 SDL_Surface *sourceSurface, SDL_Surface *destinationSurface) : Dynamic_Object(locx, locy,
					 width, height, sourceSurface, destinationSurface)
{
	flagList.push_back(0);	//Facing flag: 1-right, -1-left, (0-right)
	flagList.push_back(0);	//AutoPilot flag: 0-off, 1-on

	initx = locx;
	inity = locy;

	posx = locx;
	posy = locy;
	velx = 0;
	vely = 0;
	accx = 0;
	accy = 0;
	mass = 100;
	isJumping = false;

	characterList.push_back(this);
}

void Character::AddAnimation(Animation animation)
{
	animList.push_back(animation);
}

void Character::Update()
{
	posx += velx/5;

	//Position verticaly
	if ((vely != 0)) {
		//Gravity defined
		posy = posy - vely;
		vely = vely + (GRAVITY);
		//posy = 0;
	}
	if (posy > inity) { // its backwards of what you think -- you want greater than it means your lower
		vely = 0; //Set the Y velocity to 0 
		posy = inity; //Set the Y position to 0
		isJumping = false;
	}	

	//Keep the position within the level, currently 4000 pixels
	if (posx < 0)
	{
		posx = 0;
	}
	else if (posx + w > 4000)
	{
		posx = 4000 - w;
	}

	//posx and posy are doubles, but the displayed location should be in pixels
	x = int(posx);
	y = int(posy);
	
	//Every 50 frames, move the animation one clip forward
	animationLoc += velx/50.0;

	//If moving right, then set the facing flag to reflect this and update the appropriate surface
	if (velx > 0)
	{
		flagList[FLAG_FACING] = 1;
		if (animationLoc >= animList[ANIM_MOVERIGHT].size())	//Keep the animation location less than the size
		{
			animationLoc -= animList[ANIM_MOVERIGHT].size();
		}
		Graphics::ApplyImage(x, y, source, destination,
			&animList[ANIM_MOVERIGHT][int(floor(animationLoc))]);
	}

	//Same, but for left
	else if (velx < 0)
	{
		flagList[FLAG_FACING] = -1;
		if (animationLoc < 0)
		{
			animationLoc += animList[ANIM_MOVELEFT].size();
		}
		Graphics::ApplyImage(x, y, source, destination,
			&animList[ANIM_MOVELEFT][int(floor(animationLoc))]);
	}

	//Similar, but now just use the standing there animations
	else
	{
		if (flagList[FLAG_FACING] >= 0)	//Facing right
		{
			Graphics::ApplyImage(x, y, source, destination, &animList[ANIM_MOVERIGHT][1]);
		}
		else	//Facing left
		{
			Graphics::ApplyImage(x, y, source, destination, &animList[ANIM_MOVELEFT].GetFirstClip());
		}
	}
}

void Character::SetVelocity(double x, double y)
{
	velx = x;
	if (isJumping == false) { //If they are jumping don't let them jump. What would they jump off of? The air?
		vely = y;
	}
	if (y > 0) {
		isJumping = true;
	}
}

void Character::GetPosition(int &posx, int &posy)
{
	posx = x;
	posy = y;
}

double Character::GetVelocityX()
{
    return velx;
}

double Character::GetVelocityY()
{
    return vely;
}

void Character::CleanUp()
{
    for (std::list<Character*>::iterator i = characterList.begin(); i != characterList.end(); i++)
	{
		delete *i;
	}
	characterList.clear();
}

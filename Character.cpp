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

	//Set up the animations, based on the current layout of the spritesheets. Should be within the character class
	//since all character spritesheets should be set up in the same way (so says I!)
    std::vector<SDL_Rect> AnimRight;    //Moving right
	AnimRight.resize(4);
	AnimRight[0].x = 0;
	AnimRight[0].y = 64;
	AnimRight[0].w = 48;
	AnimRight[0].h = 64;

	AnimRight[1].x = 48;
	AnimRight[1].y = 64;
	AnimRight[1].w = 48;
	AnimRight[1].h = 64;

	AnimRight[2].x = 96;
	AnimRight[2].y = 64;
	AnimRight[2].w = 48;
	AnimRight[2].h = 64;

	AnimRight[3] = AnimRight[1];

	std::vector<SDL_Rect> AnimLeft;     //Moving left
	AnimLeft.resize(4);
	AnimLeft[0].x = 48;
	AnimLeft[0].y = 192;
	AnimLeft[0].w = 48;
	AnimLeft[0].h = 64;

	AnimLeft[1].x = 0;
	AnimLeft[1].y = 192;
	AnimLeft[1].w = 48;
	AnimLeft[1].h = 64;

	AnimLeft[2] = AnimLeft[0];

	AnimLeft[3].x = 96;
	AnimLeft[3].y = 192;
	AnimLeft[3].w = 48;
	AnimLeft[3].h = 64;

    //Currently, jumping is just the same animation as standing still, but in midair
    //Eventually, this will probably change, but at that point, the only part of the code that
    //will need to be changed is the next few lines.
	std::vector<SDL_Rect> AnimJumpLeft;     //Jumping, facing left
	AnimJumpLeft.resize(1);
	AnimJumpLeft[0].x = 48;
	AnimJumpLeft[0].y = 192;
	AnimJumpLeft[0].w = 48;
	AnimJumpLeft[0].h = 64;

	std::vector<SDL_Rect> AnimJumpRight;    //Jumping, facing right
	AnimJumpRight.resize(1);
	AnimJumpRight[0].x = 48;
	AnimJumpRight[0].y = 64;
	AnimJumpRight[0].w = 48;
	AnimJumpRight[0].h = 64;

	std::vector<SDL_Rect> AnimStillLeft;    //Standing, facing left
	AnimStillLeft.resize(1);
	AnimStillLeft[0].x = 48;
	AnimStillLeft[0].y = 192;
	AnimStillLeft[0].w = 48;
	AnimStillLeft[0].h = 64;

	std::vector<SDL_Rect> AnimStillRight;   //Standing, facing right
	AnimStillRight.resize(1);
	AnimStillRight[0].x = 48;
	AnimStillRight[0].y = 64;
	AnimStillRight[0].w = 48;
	AnimStillRight[0].h = 64;

	AddAnimation(AnimLeft); //Push them all back, in the order of the enums related to them
	AddAnimation(AnimRight);
	AddAnimation(AnimJumpLeft);
	AddAnimation(AnimJumpRight);
	AddAnimation(AnimStillLeft);
	AddAnimation(AnimStillRight);

    currentAnim = &animList[ANIM_STILLRIGHT];   //Always begin facing right, although this should be changed almost immediately
        //in almost all circumstances
	characterList.push_back(this);
}

void Character::AddAnimation(Animation animation)
{
	animList.push_back(animation);
}

void Character::Update()
{
    double secsPassed = (SDL_GetTicks() - lastTime)/1000.0;
    printf("Seconds passed: %f\n", secsPassed);
	pos.x += vel.x * secsPassed;

	//Position vertically
	if ((vel.y != 0)) {
		//Gravity defined
		pos.y += vel.y * secsPassed;
		vel.y += (GRAVITY) * secsPassed;
		//pos.y = 0;
	}
	if (pos.y > init.y) { // its backwards of what you think -- you want greater than it means your lower
		StopJump();
		pos.y = init.y; //Set the Y position to 0
	}

	//Keep the position within the level, currently 4000 pixels by 200 pixels
	if (pos.x < 0)
	{
		pos.x = 0;
	}
	else if (pos.x + dim.x > 4000)
	{
		pos.x = 4000 - dim.x;
	}
    if (pos.y < -30)
	{
	    pos.y = -30;
	}
	else if (pos.y + dim.y > 200)
	{
	    pos.y = 200 - dim.y;
	}

    currentAnim->Update();  //The animation will determine what the appropriate current clip is, based
        //on the current time

    //Apply the image appropriately
	Graphics::ApplyImage(pos.x, pos.y, source, destination, &currentAnim->GetCurrentClip());
	lastTime = SDL_GetTicks();  //Update the lastTime function
}

void Character::SetVelocity(double x, double y)
{
	vel.x = x;
}

void Character::Jump()
{
    if (flagList[FLAG_JUMPING] == 0)    //If not already jumping
    {
        if (flagList[FLAG_FACING] < 0)  //If facing left
        {
            ChangeAnimation(&animList[ANIM_JUMPLEFT]);  //Set the appropriate animation
        }
        else
        {
            ChangeAnimation(&animList[ANIM_JUMPRIGHT]);
        }
        vel.y = -400;
        flagList[FLAG_JUMPING] = 1;
    }
}

void Character::StopJump()
{
    if (vel.x < 0)  //If moving left
    {
        ChangeAnimation(&animList[ANIM_MOVELEFT]);
    }
    else if (vel.x > 0) //If moving right
    {
        ChangeAnimation(&animList[ANIM_MOVERIGHT]);
    }
    else    //If not moving
    {
        if (flagList[FLAG_FACING] < 0)  //If facing left
        {
            ChangeAnimation(&animList[ANIM_STILLLEFT]);
        }
        else    //If facing right
        {
            ChangeAnimation(&animList[ANIM_STILLRIGHT]);
        }
    }
    vel.y = 0;
    flagList[FLAG_JUMPING] = 0;
}

void Character::MoveRight()
{
    if (flagList[FLAG_JUMPING] == 1)    //If you are jumping
    {
        ChangeAnimation(&animList[ANIM_JUMPRIGHT]); //Set the right jumping animation
    }
    else
    {
        ChangeAnimation(&animList[ANIM_MOVERIGHT]);
    }
    flagList[FLAG_FACING] = 1;
    vel.x = 80;    //800 pixels per second, give or take
}

void Character::MoveLeft()
{
    if (flagList[FLAG_JUMPING] == 1)    //If you are jumping
    {
        ChangeAnimation(&animList[ANIM_JUMPLEFT]); //Set the left jumping animation
    }
    else
    {
        ChangeAnimation(&animList[ANIM_MOVELEFT]);
    }
    flagList[FLAG_FACING] = -1;
    vel.x = -80;   //800 pixels per second, give or take
}

void Character::StopMove()
{
    if (flagList[FLAG_JUMPING] == 1)    //If you are jumping
    {
        if (flagList[FLAG_FACING] < 0)  //If you are facing left
        {
            ChangeAnimation(&animList[ANIM_JUMPLEFT]);
        }
        else
        {
            ChangeAnimation(&animList[ANIM_JUMPRIGHT]);
        }
    }
    else
    {
        if (flagList[FLAG_FACING] < 0)  //If you are facing left
        {
            ChangeAnimation(&animList[ANIM_STILLLEFT]);
        }
        else
        {
            ChangeAnimation(&animList[ANIM_STILLRIGHT]);
        }
    }
    vel.x = 0;
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

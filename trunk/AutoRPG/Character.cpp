/*
Copyright 2007, 2008 Andrew Allen and Brian Shourd

This file is part of AutoRPG.

AutoRPG is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

AutoRPG is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with AutoRPG (Called LICENSE.txt).  If not, see
<http://www.gnu.org/licenses/>.
*/

#include "Character.h"
#include "Instance.h"
#include "Graphics.h"
#include "Conversions.h"

#include <sstream>

Character::Character(int locx, int locy, int width, int height, SDL_Surface *destinationSurface, int ID)
{
	flagList.push_back(1);	//Facing flag: 1-left, 2-right, 3-up, 4-down
	flagList.push_back(0);	//AutoPilot flag: 0-off, 1-on
	flagList.push_back(0);  //Jumping flag: 0-not jumping, 1-jumping

    pos.x = locx;
	pos.y = locy;
	dim.x = width;
	dim.y = height;
	init.x = locx;
	init.y = locy;
	vel.x = 0;
	vel.y = 0;

	id = ID;

	destination = destinationSurface;
	lastTime = SDL_GetTicks();

	animList.clear();	//Just make sure that these are all clear
	//flagList.clear();

	//Set up the animations, based on the current layout of the spritesheets. Should be within the character class
	//since all character spritesheets should be set up in the same way (so says I!)
    //Walking
	std::vector<int> animLeft;
	animLeft.push_back(19);
	animLeft.push_back(18);
	animLeft.push_back(19);
	animLeft.push_back(20);
	AddAnimation(animLeft);

    std::vector<int> animRight;
	animRight.push_back(7);
	animRight.push_back(6);
	animRight.push_back(7);
	animRight.push_back(8);
	AddAnimation(animRight);

    std::vector<int> animUp;
	animUp.push_back(1);
	animUp.push_back(0);
	animUp.push_back(1);
	animUp.push_back(2);
	AddAnimation(animUp);

    std::vector<int> animDown;
	animDown.push_back(13);
	animDown.push_back(12);
	animDown.push_back(13);
	animDown.push_back(14);
	AddAnimation(animDown);

	//Jumping
    std::vector<int> animJumpLeft;
	animJumpLeft.push_back(19);
	AddAnimation(animJumpLeft);

    std::vector<int> animJumpRight;
	animJumpRight.push_back(7);
	AddAnimation(animJumpRight);

    std::vector<int> animJumpUp;
	animJumpUp.push_back(1);
	AddAnimation(animJumpUp);

    std::vector<int> animJumpDown;
	animJumpDown.push_back(13);
	AddAnimation(animJumpDown);

	//Standing still
    std::vector<int> animStillLeft;
	animStillLeft.push_back(19);
	AddAnimation(animStillLeft);

    std::vector<int> animStillRight;
	animStillRight.push_back(7);
	AddAnimation(animStillRight);

    std::vector<int> animStillUp;
	animStillUp.push_back(1);
	AddAnimation(animStillUp);

    std::vector<int> animStillDown;
	animStillDown.push_back(13);
	AddAnimation(animStillDown);

    ChangeAnimation(&animList[ANIM_STILLRIGHT]);   //Always begin facing right, although this should be changed almost immediately
        //in almost all circumstances

    fpsTicks = SDL_GetTicks();
    fpsFrames = 0;
}

Character::Character(std::string serialized)
{
	flagList.push_back(1);	//Facing flag: 1-left, 2-right, 3-up, 4-down
	flagList.push_back(0);	//AutoPilot flag: 0-off, 1-on
	flagList.push_back(0);  //Jumping flag: 0-not jumping, 1-jumping

    std::stringstream inString;
    inString.str(serialized);
    std::string temp;
    inString >> temp;
    pos.x = Conversions::StringToInt(temp);
    inString >> temp;
	pos.y = Conversions::StringToInt(temp);
    inString >> temp;
	dim.x = Conversions::StringToInt(temp);
    inString >> temp;
	dim.y = Conversions::StringToInt(temp);
    inString >> temp;
	vel.x = Conversions::StringToInt(temp);
    inString >> temp;
	vel.y = Conversions::StringToInt(temp);

    inString >> temp;
	id = Conversions::StringToInt(temp);

	destination = NULL;
	lastTime = SDL_GetTicks();

	animList.clear();	//Just make sure that these are all clear

	//Set up the animations, based on the current layout of the spritesheets. Should be within the character class
	//since all character spritesheets should be set up in the same way (so says I!)
    //Walking
	std::vector<int> animLeft;
	animLeft.push_back(19);
	animLeft.push_back(18);
	animLeft.push_back(19);
	animLeft.push_back(20);
	AddAnimation(animLeft);

    std::vector<int> animRight;
	animRight.push_back(7);
	animRight.push_back(6);
	animRight.push_back(7);
	animRight.push_back(8);
	AddAnimation(animRight);

    std::vector<int> animUp;
	animUp.push_back(1);
	animUp.push_back(0);
	animUp.push_back(1);
	animUp.push_back(2);
	AddAnimation(animUp);

    std::vector<int> animDown;
	animDown.push_back(13);
	animDown.push_back(12);
	animDown.push_back(13);
	animDown.push_back(14);
	AddAnimation(animDown);

	//Jumping
    std::vector<int> animJumpLeft;
	animJumpLeft.push_back(19);
	AddAnimation(animJumpLeft);

    std::vector<int> animJumpRight;
	animJumpRight.push_back(7);
	AddAnimation(animJumpRight);

    std::vector<int> animJumpUp;
	animJumpUp.push_back(1);
	AddAnimation(animJumpUp);

    std::vector<int> animJumpDown;
	animJumpDown.push_back(13);
	AddAnimation(animJumpDown);

	//Standing still
    std::vector<int> animStillLeft;
	animStillLeft.push_back(19);
	AddAnimation(animStillLeft);

    std::vector<int> animStillRight;
	animStillRight.push_back(7);
	AddAnimation(animStillRight);

    std::vector<int> animStillUp;
	animStillUp.push_back(1);
	AddAnimation(animStillUp);

    std::vector<int> animStillDown;
	animStillDown.push_back(13);
	AddAnimation(animStillDown);

    ChangeAnimation(&animList[ANIM_STILLRIGHT]);   //Always begin facing right, although this should be changed almost immediately
        //in almost all circumstances

    fpsTicks = SDL_GetTicks();
    fpsFrames = 0;
}

void Character::AddAnimation(std::vector<int> animation, std::string filename)
{
    animList.push_back(Animation(filename, 48, 64, animation, 120, 255, 0, 0));
}

void Character::ChangeAnimation(Animation* animation)
{
    currentAnim = animation;
    currentAnim->Begin();
}

void Character::UpdatePosition()
{
    double secsPassed = (SDL_GetTicks() - lastTime)/1000.0;
    fpsFrames++;
    if (SDL_GetTicks() - fpsTicks > 1000)
    {
        printf("Frames per second is %f\n", fpsFrames/((SDL_GetTicks() - fpsTicks)/1000.0));
        fpsTicks = SDL_GetTicks();
        fpsFrames = 0;
    }
	pos.x += vel.x * secsPassed;
	pos.y += vel.y * secsPassed;

	//Keep the position within the level, currently 4000 pixels by 400 pixels
	if (pos.x < 0)
	{
		pos.x = 0;
	}
	else if (pos.x + dim.x > SCREEN_WIDTH)
	{
		pos.x = SCREEN_WIDTH - dim.x;
	}
    if (pos.y < 0)
	{
	    pos.y = 0;
	}
	else if (pos.y + dim.y > SCREEN_HEIGHT)
	{
	    pos.y = SCREEN_HEIGHT - dim.y;
	}

	lastTime = SDL_GetTicks();  //Update the last time
}

void Character::UpdateAnimation()
{
    currentAnim->ApplyCurrentSprite(pos.x, pos.y, destination);

	lastTime = SDL_GetTicks();  //Update the lastTime function
}

Point Character::GetPosition()
{
    return pos;
}

int Character::GetId()
{
    return id;
}

void Character::AssignClient(int theClientId)
{
    clientId = theClientId;
}

void Character::Jump()
{
    if (flagList[FLAG_JUMPING] == 0)    //If not already jumping
    {
        switch (flagList[FLAG_FACING])
        {
        case 1: //If facing left
            ChangeAnimation(&animList[ANIM_JUMPLEFT]);  //Set the appropriate animation
            break;
        case 2: //If facing right
            ChangeAnimation(&animList[ANIM_JUMPRIGHT]);
            break;
        case 3: //If facing up
            ChangeAnimation(&animList[ANIM_JUMPUP]);
            break;
        case 4: //If facing down
            ChangeAnimation(&animList[ANIM_JUMPDOWN]);
            break;
        default:    //If none of these - signifies error
            ChangeAnimation(&animList[ANIM_JUMPLEFT]);
            break;
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
    else if (vel.y < 0) //If moving up
    {
        ChangeAnimation(&animList[ANIM_MOVEUP]);
    }
    else if (vel.y > 0) //If moving down
    {
        ChangeAnimation(&animList[ANIM_MOVEDOWN]);
    }
    else    //If not moving
    {
        if (flagList[FLAG_FACING] == 1)  //If facing left
        {
            ChangeAnimation(&animList[ANIM_STILLLEFT]);
        }
        else if (flagList[FLAG_FACING] == 2)   //If facing right
        {
            ChangeAnimation(&animList[ANIM_STILLRIGHT]);
        }
        else if (flagList[FLAG_FACING] == 3)
        {
            ChangeAnimation(&animList[ANIM_STILLUP]);
        }
        else if (flagList[FLAG_FACING] == 4)
        {
            ChangeAnimation(&animList[ANIM_STILLDOWN]);
        }
    }
    vel.y = 0;
    flagList[FLAG_JUMPING] = 0;
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
    flagList[FLAG_FACING] = 1;
    vel.x = -80;   //800 pixels per second, give or take
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
    flagList[FLAG_FACING] = 2;
    vel.x = 80;    //800 pixels per second, give or take
}

void Character::MoveUp()
{
    ChangeAnimation(&animList[ANIM_MOVEUP]);
    flagList[FLAG_FACING] = 3;
    vel.y = -80;
}

void Character::MoveDown()
{
    ChangeAnimation(&animList[ANIM_MOVEDOWN]);
    flagList[FLAG_FACING] = 4;
    vel.y = 80;
}

void Character::StopMoveHoriz()
{
    if (vel.y < 0)  //If moving up
    {
        ChangeAnimation(&animList[ANIM_MOVEUP]);
        flagList[FLAG_FACING] = 3;
    }
    else if (vel.y > 0)   //If moving down
    {
        ChangeAnimation(&animList[ANIM_MOVEDOWN]);
        flagList[FLAG_FACING] = 4;
    }
    else if (flagList[FLAG_FACING] == 1)    //If facing left
    {
        ChangeAnimation(&animList[ANIM_STILLLEFT]);
    }
    else if (flagList[FLAG_FACING] == 2)    //If facing right
    {
        ChangeAnimation(&animList[ANIM_STILLRIGHT]);
    }
    vel.x = 0;
}

void Character::StopMoveVert()
{
    if (vel.x < 0)  //If moving left
    {
        ChangeAnimation(&animList[ANIM_MOVELEFT]);
        flagList[FLAG_FACING] = 1;
    }
    else if (vel.x > 0)   //If moving right
    {
        ChangeAnimation(&animList[ANIM_MOVERIGHT]);
        flagList[FLAG_FACING] = 2;
    }
    else if (flagList[FLAG_FACING] == 3)    //If facing up
    {
        ChangeAnimation(&animList[ANIM_STILLUP]);
    }
    else if (flagList[FLAG_FACING] == 4)    //If facing down
    {
        ChangeAnimation(&animList[ANIM_STILLDOWN]);
    }
    vel.y = 0;
}

Point Character::GetVelocity()
{
    return vel;
}

std::string Character::Serialize()
{
    std::string serialized = "";
    serialized += Conversions::IntToString(pos.x) + " ";
    serialized += Conversions::IntToString(pos.y) + " ";
    serialized += Conversions::IntToString(dim.x) + " ";
    serialized += Conversions::IntToString(dim.y) + " ";
    serialized += Conversions::IntToString(vel.x) + " ";
    serialized += Conversions::IntToString(vel.y) + " ";
    serialized += Conversions::IntToString(id) + " ";
    return serialized;
}

void Character::CleanUp()
{
}

#ifndef CHARACTER_H
#define CHARACTER_H

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

#include "Animation.h"
#include "Slot.h"
#include "Point.h"
#include "Sector.h"
#include "Area.h"

#include <SDL/SDL.h>
#include <map>
#include <string>
#include <vector>

//The class for any and all characters in the game.
class Character
{
private:
    Point pos;  //Position
	Point dim;  //Dimensions
	Point vel;	//Velocity in pixels per second
	Point init; //Initialized values
	int id;  //The unique id of this character
	std::vector<Slot> inventory;    //The inventory

    int lastTime;   //The time (in ms) of the last time Update was called. Allows for the positions, etc. to be adjusted
        //independently of frame rate.
	//SDL_Surface *source;	//A pointer to the surface containing the sprites
	SDL_Surface *destination; //A pointer to the surface where the sprites should be blitted to
	std::vector<Animation> animList;	//A list of the different possible animations
	std::vector<int> flagList;	//A list of all of the flags
    Animation* currentAnim; //A pointer to the current animation being used

    int currentSectorId;  //The current Sector
    int currentAreaId;  //The current Area

    int clientId;

	double fpsTicks, fpsFrames; //Used for calculating framerate
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
	Character(int locx, int locy, int width, int height, SDL_Surface *destinationSurface, int ID);
	Character(std::string serialized);
	void AddAnimation(std::vector<int> animation, std::string filename = "images/miniDungeonCharSprites2x.png");
	void ChangeAnimation(Animation* animation);
    void UpdatePosition();  //Updates the position based on velocity and acceleration
	void UpdateAnimation();	//Updates the surface on which the character should be updated
    Point GetPosition();
    static void CleanUp();  //Cleans up all of the dynamically allocated memory stored in characterList
	Point GetVelocity();	//Returns the velocity
	int GetId();    //Returns the id
	void AssignClient(int theClientId);
	void Jump();
	void StopJump();
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();
	void StopMoveHoriz();
	void StopMoveVert();
	std::string Serialize();
};

#endif
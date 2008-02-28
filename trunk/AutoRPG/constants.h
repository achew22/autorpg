#ifndef INCLUDE_H
#define INCLUDE_H

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

//Globals.
static const int SCREEN_WIDTH = 200;	//Screen width
static const int SCREEN_HEIGHT = 200;	//Screen height
static const int SCREEN_BPP = 32;	//Screen BPP

//Some name defining for events. Essentially, while we can just as easily serialize a string and include the word "Attack"
//in it, we can use the highly efficient switch statement only if the argument of switch is an integer. Thus, the contants
const int ATTACK = 1;
const int DEFEND = 2;
const int TAKEDAMAGE = 3;
const int DEATH = 4;
const int SPAWN = 5;
const int MOVEMENT = 6;
const int CHAT = 7;

#endif

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

//Debug options for choosing whether or not to show some debug messages
const bool DEBUG_SHOWALL = false;
const bool DEBUG_SHOWFPS = false;
const bool DEBUG_SHOWEVENTS = false;
const bool DEBUG_SHOWERRORS = true;

//Globals.
static const int SCREEN_WIDTH = 500;	//Screen width
static const int SCREEN_HEIGHT = 500;	//Screen height
static const int SCREEN_BPP = 32;	//Screen BPP

const int CHARACTER_WIDTH = 48;
const int CHARACTER_HEIGHT = 64;

#endif

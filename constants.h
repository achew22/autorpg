#ifndef INCLUDE_H
#define INCLUDE_H

//Globals. These really need to be cut down. I think most of this can be solved by putting them all in the graphics
//class, once it has been formatted as such, and making an instance of that class global. I'm not sure.
const int SCREEN_WIDTH = 200;	//Screen width
const int SCREEN_HEIGHT = 100;	//Screen height
const int SCREEN_BPP = 32;	//Screen BPP
const int FPS = 30;
const double GRAVITY = 2500;   //gravity is about 2500 pixels per second per second

class Character;
extern Character *hero;	//A pointer to the hero instance of the character class

#endif


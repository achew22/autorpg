#ifndef INCLUDE_H
#define INCLUDE_H

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

#ifndef INSTANCE_H
#define INSTANCE_H

#include <SDL/SDL.h>
#include <string>
#include "Point.h"
#include "Sprite_Sheet.h"
#include <vector>
#include <map>
#include "Character.h"
#include "Map.h"

//Just a namespace of Graphics-related functions. Should eventually be turned into a class, since it is not really OOP
//to have all these global functions and global variables
class Instance
{
private:
    SDL_Surface *screen;	//The main display screen for the game
    SDL_Surface *dynamicLayer;
        //A very important surface. All of the dynamic objects should update to this surface, in order from
        //back to front. This surface will eventually be blitted to the screen, but only at the very last possible
        //moment.
    std::map<std::string, Character*> characterList;    //Pointers to the lists that will need to be updated that exist in this instace of graphics
    Character* player;
    Map* map;
public:
    Instance(int locx, int locy, SDL_Surface* theScreen);
	bool LoadFiles();	//Load all of the necessary files for this game
	void LoadMap(std::string indexFile, std::string tileFile);
	bool Update();	//The main update function, which calls all of the necessary updates for the dynamic objects and ultimately makes the buffer swap
		//to show them all to the screen
	void CleanUp();	//Frees all of the allocated surfaces and quits the SDL subsystems that are running
	void SetUpDynamicObjects();
	Character* GetPlayer();  //Returns a pointer to the character for this instance
};

#endif

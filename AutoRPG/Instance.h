#ifndef INSTANCE_H
#define INSTANCE_H

#include <SDL/SDL.h>
#include <string>
#include "Point.h"
#include "Sprite_Sheet.h"
#include <vector>
#include <map>
#include "Character.h"
#include "Dynamic_Object.h"

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
    SDL_Surface *background;	//The main background surface for the game
    SDL_Surface *dynamicSprites;
        //The surface containing all of the spritesheets for dynamic objects, except for the characters
    SDL_Surface *bgTiles;
        //The surface containing all of the tiles used to populate the background
    SDL_Surface *characters;
        //The surface containing all of the sprites necessary to create the characters
    Point location; //The location at which this particular veiw will be
    std::map<std::string, Character*> characterList;    //Pointers to the lists that will need to be updated that exist in this instace of graphics
    std::vector<Dynamic_Object*> backgroundObjectList;
    std::vector<Dynamic_Object*> interactObjectList;
    Character* player;

    Sprite_Sheet* tempSpriteSheet;
public:
    Instance(int locx, int locy, SDL_Surface* theScreen);
	bool LoadFiles(std::string dynamicSpritesFile, std::string bgTilesFile, std::string charactersFile);	//Load all of the necessary files for this game
	void CreateBackground();	//Build the background
	bool Update();	//The main update function, which calls all of the necessary updates for the dynamic objects and ultimately makes the buffer swap
		//to show them all to the screen
	void CleanUp();	//Frees all of the allocated surfaces and quits the SDL subsystems that are running
	void SetUpDynamicObjects();
	Character* GetPlayer();  //Returns a pointer to the character for this instance
};

#endif

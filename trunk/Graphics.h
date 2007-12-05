#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "include.h"
//Just a namespace of Graphics-related functions. Should eventually be turned into a class, since it is not really OOP
//to have all these global functions and global variables
namespace Graphics
{
	SDL_Surface *LoadImage(std::string filename, int red, int green, int blue);	//Load an image
		//The RGB values are the color that you want to be transparent. They default to bright blue, so they don't need to be specified.
	void ApplyImage(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip);
		//Apply an image at from the source to the destination, at the position x and y, and with the clip defined in clip (which defaults to the entire surface)
	bool Init();	//Initialize SDL
	bool LoadFiles();	//Load all of the necessary files for this game
	void CreateBackground();	//Build the background
	bool Update();	//The main update function, which calls all of the necessary updates for the dynamic objects and ultimately makes the buffer swap
		//to show them all to the screen
	void CleanUp();	//Frees all of the allocated surfaces and quits the SDL subsystems that are running
}

#endif

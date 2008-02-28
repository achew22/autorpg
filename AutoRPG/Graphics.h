#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>

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

class Graphics
{
private:
    SDL_Surface* screen;    //The main screen for everything!
public:
    Graphics() {};
    static void ApplyImage(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip = NULL);
		//Apply an image at from the source to the destination, at the position x and y, and with the clip defined in clip (which defaults to the entire surface)
	static SDL_Surface* LoadImage(std::string filename, int red = 0, int green = 255, int blue = 255);
    bool Init();	//Initialize the whole graphics layer
	SDL_Surface* GetScreen();
	void CleanUp();
	bool Update();
};

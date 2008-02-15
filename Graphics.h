#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>

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

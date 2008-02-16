#include "Torch.h"
#include "Graphics.h"

//The constructor automatically assumes that it knows where the animations live, and sets them up for the torch.
Torch::Torch(int x, SDL_Surface *sourceSurface, SDL_Surface *destinationSurface) : Background_Object(x, 26, 50, 50, sourceSurface, destinationSurface)
{
	std::vector<SDL_Rect> newAnim;
	SDL_Rect newClip1;
	newClip1.x = 0;
	newClip1.y = 0;
	newClip1.w = 50;
	newClip1.h = 50;
	newAnim.push_back(newClip1);

	SDL_Rect newClip2;
	newClip2.x = 50;
	newClip2.y = 0;
	newClip2.w = 50;
	newClip2.h = 50;
	newAnim.push_back(newClip2);

	animList.push_back(Animation(newAnim));
	newAnim.clear();
	currentAnim = &animList[0];
}

//Update the torches animation location to the dynamicLayer
void Torch::Update()
{
	currentAnim->Update();
	Graphics::ApplyImage(pos.x, pos.y, source, destination, &currentAnim->GetCurrentClip());
}
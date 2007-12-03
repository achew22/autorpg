#ifndef TORCH_H
#define TORCH_H

Torch::Torch(int x, SDL_Surface *surface) : Dynamic_Object(x, 26, 50, 50, surface)
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
}

void Torch::Update()
{
	animationLoc += 1/20.0;
	if (animationLoc >= 2)
	{
		animationLoc -= 2;
	}
	Graphics::ApplyImage(x, y, objectSurface, dynamicLayer, &animList[0][int(animationLoc)]);
}

#endif
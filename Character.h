#ifndef CHARACTER_H
#define CHARACTER_H

Character::Character(int locx, int locy, int width, int height, 
					 SDL_Surface *surface) : Dynamic_Object(locx, locy, 
					 width, height, surface)
{
	flagList.push_back(0);	//Moving flag: 0-not, 1-right, -1-left
	flagList.push_back(0);	//Facing flag: 1-right, -1-left, (0-right)
	flagList.push_back(0);	//AutoPilot flag: 0-off, 1-on

	posx = locx;
	posy = locy;
	velx = 0;
	vely = 0;
	accx = 0;
	accy = 0;
	mass = 100;
}

void Character::AddAnimation(Animation animation)
{
	animList.push_back(animation);
}

void Character::Update()
{
	posx += velx;
	posy += vely;
	if (posx < 0)
	{
		posx = 0;
	}
	else if (posx + w > 4000)
	{
		posx = 4000 - w;
	}
	x = int(posx);
	y = int(posy);

	animationLoc += flagList[0]/50.0;
	if (flagList[0] > 0)
	{
		flagList[1] = 1;
		if (animationLoc >= 4)
		{
			animationLoc -= 4;
		}
		Graphics::ApplyImage(x, y, objectSurface, dynamicLayer,
			&animList[1][int(floor(animationLoc))]);
	}
	else if (flagList[0] < 0)
	{
		flagList[1] = -1;
		if (animationLoc < 0)
		{
			animationLoc += 4;
		}
		Graphics::ApplyImage(x, y, objectSurface, dynamicLayer,
			&animList[0][int(floor(animationLoc))]);
	}
	else
	{
		if (flagList[1] >= 0)
		{
			Graphics::ApplyImage(x, y, objectSurface, dynamicLayer, &animList[1][1]);
		}
		else
		{
			Graphics::ApplyImage(x, y, objectSurface, dynamicLayer, &animList[0].GetFirstClip());
		}
	}
}

void Character::ApplyForce(double forcex, double forcey)
{
	accx = forcex/mass;
	accy = forcey/mass;
}

#endif

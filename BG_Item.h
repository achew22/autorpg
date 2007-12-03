#ifndef BG_ITEM_H
#define BG_ITEM_H

BG_Item::BG_Item(SDL_Surface *surface, int clipX, int clipY, int clipW, int clipH)
{
	surfaceLoc = surface;
	clip.x = clipX;
	clip.y = clipY;
	clip.w = clipW;
	clip.h = clipH;
}

BG_Item::BG_Item(SDL_Surface *surface, SDL_Rect itemClip)
{
	surfaceLoc = surface;
	clip = itemClip;
}

void BG_Item::AddItem(int x, int y, SDL_Surface *destination)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(surfaceLoc, &clip, destination, &offset);
}

void BG_Item::Populate(int maxNumItems, int from, int to, SDL_Surface *destination, int y, int minDist)
{
	int i = 0;
	std::vector<int> locations;
	while (i < maxNumItems)
	{
		int newLoc = rand()%(to - from);
		for (int j=0; j<int(locations.size()); j++)
		{
			if ((abs(newLoc - locations[j])) < minDist)
			{
				newLoc += minDist;
				j = 0;
			}
		}
		locations.push_back(newLoc);
		if (newLoc < to)
		{
			AddItem(newLoc, y, destination);
			i++;
		}
		else
		{
			break;
		}
	}
}

#endif

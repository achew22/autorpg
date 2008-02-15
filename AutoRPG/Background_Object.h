#ifndef BACKGROUND_OBJECT_H
#define BACKGROUND_OBJECT_H

#include "Dynamic_Object.h"
#include "Instance.h"
#include "constants.h"

class Background_Object : public Dynamic_Object
{
private:
    static std::vector<Dynamic_Object*> backgroundObjectList;
public:
    Background_Object(int locx, int locy, int width, int height, SDL_Surface *sourceSurface, SDL_Surface *destinationSurface);
    virtual void Update();
    static void CleanUp();
};

#endif

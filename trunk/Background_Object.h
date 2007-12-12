#ifndef BACKGROUND_OBJECT_H
#define BACKGROUND_OBJECT_H

#include "Dynamic_Object.h"
#include "Graphics.h"
#include "include.h"

class Background_Object : public Dynamic_Object
{
friend bool Graphics::Update();
private:
    static std::vector<Dynamic_Object*> backgroundObjectList;
public:
    Background_Object(int posx, int posy, int width, int height, SDL_Surface *sourceSurface, SDL_Surface *destinationSurface);
    virtual void Update();
    static void CleanUp();
};

#endif

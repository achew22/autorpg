#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <vector>
#include <list>
#include <string>

//A class to handle sprite sheets. Note: all of the sprites in the sheet must be the same size.
//By setting this up when the area is loaded (which should take under a second), we save a lot
//of blitting time between frames (which is where it counts).
class Sprite_Sheet
{
private:
    std::vector<SDL_Surface*> sprites;
    static std::list<Sprite_Sheet*> spriteSheetList;
    std::string filename;
public:
    Sprite_Sheet(int wOfSprite, int hOfSprite, std::string file, int red = 0, int green = 255, int blue = 255);
    ~Sprite_Sheet();    //The destructor
    void ApplySprite(int x, int y, int spriteNum, SDL_Surface* destination);    //Apply the sprite at index spriteNum
        //to the surface destination at the coordinates x, y
    bool operator ==(Sprite_Sheet* compare); //The obvious, compare two Sprite_Sheets
    static Sprite_Sheet* FindSheet(std::string file);   //Returns a pointer to the spriteSheet that was already
        //created with the file specified by "file". If none yet exists, returns NULL. Use this to prevent creating
        //multiple identical Sprite_Sheets, thereby wasting memory.
    static void CleanUp();  //Call when you are done with the program, deletes all Sprite_Sheets stored in
        //spriteSheetList

    static void PrintList(); //A debugging function to print out spriteSheetList
};

#endif

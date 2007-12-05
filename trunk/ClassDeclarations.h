#ifndef CLASSDECLARATIONS_H
#define CLASSDECLARATIONS_H

class Animation
{
private:
	std::vector<SDL_Rect> animSeries;
public:
	Animation(std::vector<SDL_Rect> animation);
	Animation() {};
	~Animation();
	SDL_Rect operator [](int i);
	Animation operator =(Animation anim);
	int size();
	SDL_Rect GetFinalClip();
	SDL_Rect GetFirstClip();
};

class BG_Item
{
private:
	SDL_Surface *surfaceLoc;
	SDL_Rect clip;
public:
	BG_Item(SDL_Surface *surface, int clipX = 0, int clipY = 0, int clipW = 0, int clipH = 0);
	BG_Item(SDL_Surface *surface, SDL_Rect itemClip);
	void AddItem(int x, int y, SDL_Surface *destination);
	void Populate(int maxNumItems, int from, int to, SDL_Surface *destination, int y, int minDist = 0);
};

class Dynamic_Object
{
protected:
	int x;	//Relative positions to bg, in pixels
	int y;
	int w;
	int h;
	double animationLoc;
	SDL_Surface *objectSurface;	//The surface containing the sprites
	std::vector<Animation> animList;	//A list of the different possible animations
	std::vector<int> flagList;	//A list of all of the flags
public:
	Dynamic_Object(int posx, int posy, int width, int height, SDL_Surface *location);
	virtual void FreeSurface();
	virtual void Update() {};
	virtual void AddAnimation(Animation anim);
	void GetPosition(int &posx, int &posy);
	Dynamic_Object operator =(Dynamic_Object object);
	bool SetFlag(int index, int value);
	int GetFlag(int index);
};

class Torch : public Dynamic_Object
{
private:
public:
	Torch(int x, SDL_Surface *surface);
	virtual void Update();
};

class Character : public Dynamic_Object
{
private:
	double posx, posy;
	double velx, vely;
	double accx, accy;
	double mass;
public:
	Character(int locX, int locY, int width, int height, SDL_Surface *surface);
	virtual void AddAnimation(Animation animation);
	void Update();
	void SetVelocity(double x, double y);
	double GetVelocityX();
	double GetVelocityY();
	void SetAcceleration(double x, double y);
};

namespace Graphics
{
	SDL_Surface *LoadImage(std::string filename, int red = 0, int green = 0, int blue = 0);
	void ApplyImage(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip);
	bool Init();
	bool LoadFiles();
	void CreateBackground();
	bool Update();
	void CleanUp();
}

void SetUpDynamicObjects();
bool HandleEvents();

#endif

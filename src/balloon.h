#include <string>
#include <iostream>

using namespace std;
#include <vector>

#if defined (__APPLE__)
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h"
#endif

#if defined(_WIN32) || (_WIN64)
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#endif

#if defined(__linux__)
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h"
#endif

//#include "turretbullet.h"
class Balloon{

public:
	//boolean for state of enemy
	bool active;

	//enemy texture
	SDL_Texture *bloon;

	//enemy rectanbel for position(x,y) and size(h,w)
	SDL_Rect balloonRect;

	//movement direction values
	float xDir, yDir;

	//enemy speed
	float speed;

	//enemy float posiitons to prevent precision loss
	float pos_X, pos_Y;

	//enemy angle
	float angle;

	//point for the center of you object, used for rotatoin
	SDL_Point center;

	//enemy creation method, requires the renderer, a path to the needed image
	Balloon(SDL_Renderer *renderer, string filePath, string audioPath);

	//enemy update
	void Update(float deltaTime);

	//move the balloon
	void TankMoveX(float planeSpeed, float deltaTime);

	void TankMoveY(float planeSpeed, float deltaTime);

	//enemy draw
	void Draw(SDL_Renderer *renderer);

	//enemy reset
	void Reset();

	//enemy descturion method
	~Balloon();


};

#include "balloon.h"

//enemy creation method
Balloon::Balloon(SDL_Renderer *renderer, string filePath, string audioPath)
{
	//get the path to enemts texture
	string enemyPath = filePath + "enemy.png";

	//load the texture into a surface
	SDL_Surface *surface = IMG_Load(enemyPath.c_str());

	//Create the texture form the passed Renderer and created surface
	bloon = SDL_CreateTextureFromSurface(renderer, surface);

	//free the surface for later use
	SDL_FreeSurface(surface);

	//set the width and height of the enemy's rectangle
	//by querying the texture itself
	int w, h;
	SDL_QueryTexture(bloon, NULL, NULL, &w, &h);
	balloonRect.w=w;
	balloonRect.h=h;

	//reset the nenemy
	Reset();

	//initialize the firextion vars for enemy
	//no x movement only y movment
	xDir=0;
	yDir=1;

	//start with a random angle
	angle = rand()%(360);

	//caclutlate venter pos by setting
	//_> pos to half of width
	//->y pos to half height
	center.x = balloonRect.w/2;
	center.y = balloonRect.h/2;

}

//enemy reset method
void Balloon::Reset(){

	//set random enem speed
	speed = rand() % (5) + 1;
	speed *= 100;

	//genderate random x position and set y back to the top of the screen
	balloonRect.x = rand() % (1024-balloonRect.w) + 1;
	balloonRect.y =0 - balloonRect.h;

	//set the float posiiotn balues of the tecture for preceision loss
	pos_X = balloonRect.x;
	pos_Y = balloonRect.y;

}

//enemy update method
void Balloon::Update(float deltaTime){

	//adjust posiition floats based on speed direction and deltatime
	pos_Y += (speed * yDir) * deltaTime;

	//Upate enemy position with code to account for precision loss
	balloonRect.y = (int)(pos_Y + 0.5f);

	//check to see if the enemy is off the bottom of the screen
	// and reset if it is
	if(balloonRect.y > 768){

		//reset the enemy
		Reset();
	}

	//update angle
	angle += .1;

}


//tank moves the turret in x
void Balloon::TankMoveX(float planeSpeed, float deltaTime)
{
	pos_X = (planeSpeed) * deltaTime;
	//posT_X = (planeSpeed) * deltaTime;

	//update bullet position with code to account for precision loss
	balloonRect.x = (int)(pos_X + 0.5f);
	//barrelRect.x = (int)(posT_X + 0.5f);
}

//tank moves the turret in x
void Balloon::TankMoveY(float planeSpeed, float deltaTime)
{
	pos_Y = (planeSpeed) * deltaTime;
	//posT_Y = (planeSpeed) * deltaTime;

	//update bullet position with code to account for precision loss
	balloonRect.y = (int)(pos_Y + 0.5f);
	//barrelRect.y = (int)(posT_Y + 0.5f);

}

//enemy draw method
 void Balloon::Draw(SDL_Renderer *renderer){

	 SDL_RenderCopyEx(renderer, bloon, NULL, &balloonRect, angle, &center, SDL_FLIP_NONE);
 }

//enemy destruction
Balloon::~Balloon(){

	SDL_DestroyTexture(bloon);
}

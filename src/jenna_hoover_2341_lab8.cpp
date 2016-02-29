#include <iostream>
#include <stdio.h>
#include <string>
#include <stdint.h>
#include <sstream>

using namespace std;

//screen dimension onstants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

//deltaTime car initialization - for frame rate independence
float deltaTime = 0.0;
int thisTime = 0;
int lastTime = 0;

//#include "plane.h"
//#include "enemy.h"

#if defined (__APPLE__)
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h"

string currentWorkingDirectory (getcwd(NULL,0));
string images_dir = currentWorkingDirectory + "/src/";
string audio_dir = currentWorkingDirectory + "/src/";
#endif

#if defined(_WIN32) || (_WIN64)
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include <direct.h>
#define get cwd _getcwd

string currentWorkingDirectory (getcwd(NULL,0));
string images_dir = currentWorkingDirectory + "\\src\\";
string audio_dir = currentWorkingDirectory + "\\src\\";
#endif

#if defined(__linux__)
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h"

#include <unistd.h>

string currentWorkingDirectory (getcwd(NULL,0));
string images_dir = currentWorkingDirectory + "/src/";
string audio_dir = currentWorkingDirectory + "/src/";
#endif


//variable for what font to use
TTF_Font *font;

//font colorcar var
SDL_Color colorP1 = {255, 255, 255, 255};

//surface for the player hit text
SDL_Surface *playerSurface, *enemySurface, *lilenemySurface;

//surface for the player hit text
SDL_Texture *playerTexture, *enemyTexture, *lilenemyTexture;

//SDL rects foer ther plater hit texture
SDL_Rect playerPos, enemyPos, lilenemyPos;

int playerHealth = 100;

string tempText = "";

void PlayerText(SDL_Renderer *renderer){
	//fix for to_string problems on linux

	string Result;

	ostringstream convert;

	convert << playerHealth;

	Result = convert.str();

	//create the textr for the font texture
	tempText = "Player Health: " + Result;

	//surface for font string
	playerSurface = TTF_RenderText_Solid(font, tempText.c_str(), colorP1);

	//create the player score texture
	playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);

	//get the width and height of the texutre
	SDL_QueryTexture(playerTexture, NULL, NULL, &playerPos.w, &playerPos.h);

	SDL_FreeSurface(playerSurface);
}

int main(int argc, char *argv[]){

	// *****CREAT ETHE SDL WINDOW - START &&&&&&
	//start SDL2
	SDL_Init(SDL_INIT_EVERYTHING);

	//create a SDL Window reference - pointer
	SDL_Window *window = NULL;

	//create a SDL renderTarget - pointer
	SDL_Renderer *renderer = NULL;

	//create a SDL Window in the middle of the screen
	window = SDL_CreateWindow("PaperPlane", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);





	//create an SDL RenderTaret
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	// *********CREATE THE SDL WINDOW - END **********

	// *********caraubke creatuib - start**********
	//main loop flag
	bool quit =false;

	//event handler
	SDL_Event e;
	//*************baraibel creation - end**********

	//***Turn on Game controller Eventws *****
	SDL_GameControllerEventState(SDL_ENABLE);

	//****set up a Game Controller vaiable for player 1 *****
	SDL_GameController* gGameController0 = NULL;

	// ***Open Game Controller for player 1 ****
	gGameController0 = SDL_GameControllerOpen(0);

	//open audio channel
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	//load a music file
	Mix_Music *bgm = Mix_LoadMUS((audio_dir + "Visager_-_19_-_Village_Dreaming_Loop").c_str());

	//if music file isnt' playing, play it
	if(!Mix_PlayingMusic())
		Mix_PlayMusic(bgm, -1);

	//cREATE PLAYERS START*******************************************
	//Plane plane1 = Plane(renderer, 0, images_dir.c_str(), audio_dir.c_str(), 50.0f,50.0f);

	//cREATE TURRET START*******************************************
	//Enemy enemy1 = Enemy(renderer, images_dir.c_str(), audio_dir.c_str(), 800.0f, 500.0f);


	SDL_Texture *bkgd = IMG_LoadTexture(renderer, (images_dir + "bkgd.png").c_str());

	SDL_Rect bkgdRect;

	bkgdRect.x = 0;

	bkgdRect.y = 0;

	bkgdRect.w = 2048;

	bkgdRect.h = 1536;

	float X_pos = 0.0f;

	float Y_pos = 0.0f;


	//init the ttf engine
	TTF_Init();

	//loda the font
	font = TTF_OpenFont((images_dir + "Arial Bold Italic.ttf").c_str(), 40);

	//x and y for players text
	playerPos.x = 10;
	playerPos.y = 10;

	//x and y for turrets text
	enemyPos.x = 600;
	enemyPos.y = 10;

	//create the initial player text
	PlayerText(renderer);

	//create the initial turret text
	//EnemyText(renderer, 0);


	// MAIN GAME LOOP START ************

	while(!quit)
	{

		//create deltaTime - for grame reate independence
		thisTime= SDL_GetTicks();
		deltaTime=(float)(thisTime-lastTime)/1000;
		lastTime=thisTime;

		//handle events on queue -Keypresses and such START ********
		while(SDL_PollEvent(&e)!= 0)
		{
			//User requests quit
			if(e.type == SDL_QUIT)
			{
				quit=true;
			}

			switch (e.type){
			case SDL_CONTROLLERBUTTONDOWN:

				if(e.cdevice.which == 0){

					if(e.cbutton.button == SDL_CONTROLLER_BUTTON_A){

						tank1.OnControllerButton(e.cbutton);
						break;
					}
				}

				break;

			case SDL_CONTROLLERAXISMOTION:

				//tank1.OnControllerAxis(e.caxis);

				break;

			}

		}//POLL EVENT

		//get values for both the x and y of the controller
		const Sint16 Xvalue = SDL_GameControllerGetAxis(gGameController0, SDL_CONTROLLER_AXIS_LEFTX);
		const Sint16 Yvalue = SDL_GameControllerGetAxis(gGameController0, SDL_CONTROLLER_AXIS_LEFTY);

		//pass to player 1
		enemy1.OnControllerAxis(Xvalue, Yvalue);


		//update player 1 tank************************************
		enemy1.Update(deltaTime);


		//move background
		if((enemy1.posRect.x >= 1024 - enemy1.posRect.w) && (enemy1.Xvalue > 8000)){

			//adjust position floats
			X_pos -=(enemy1.speed)*deltaTime;
			if((bkgdRect.x > -1024)){
				bkgdRect.x = (int)(X_pos + 0.5f);
				//move the turret
				enemy1.TankMoveX(-enemy1.speed, deltaTime);

			}else{
				X_pos = bkgdRect.x;
			}
		}

		if((enemy1.posRect.x <= 0) && (enemy1.Xvalue < 8000)){

			X_pos +=(enemy1.speed)*deltaTime;
			if((bkgdRect.x <0)){
				bkgdRect.x = (int)(X_pos + 0.5f);
				//move the turret
				enemy1.TankMoveX(enemy1.speed, deltaTime);

			}else{
				X_pos = bkgdRect.x;
			}
		}

		//move the background up and down
		if((enemy1.posRect.y >= 768 - enemy1.posRect.h) && (enemy1.Yvalue > 8000)){

			//adjust position floats
			Y_pos +=(enemy1.speed) * deltaTime;
			if((bkgdRect.y > -768)){
				bkgdRect.y = (int)(Y_pos + 0.5f);
				//move the turret
				enemy1.TankMoveY(enemy1.speed, deltaTime);

			}else{
				Y_pos = bkgdRect.y;
			}
		}

		//move the background up and down
		if((tank1.posRect.y <= 0 ) && (tank1.Yvalue < 8000)){

			//adjust position floats
			Y_pos += (tank1.speed) * deltaTime;
			if((bkgdRect.y < 0)){
				bkgdRect.y = (int)(Y_pos + 0.5f);
				//move the turret
				turret1.TankMoveY(tank1.speed, deltaTime);
				turret2.TankMoveY(tank1.speed, deltaTime);
				turret3.TankMoveY(tank1.speed, deltaTime);
				turret4.TankMoveY(tank1.speed, deltaTime);
			}else{
				Y_pos = bkgdRect.y;
			}
		}


		turret1.Update(deltaTime, tank1.posRect);
		turret2.Update(deltaTime, tank1.posRect);
		turret3.Update(deltaTime, tank1.posRect);
		turret4.Update(deltaTime, tank1.posRect);

		//check for hit from turret1
		for(int i = 0; i < turret1.bulletList.size(); i++)
		{
			if(SDL_HasIntersection(&tank1.posRect, &turret1.bulletList[i].posRect)){
				turret1.bulletList[i].Reset();
				playerHealth--;
				PlayerText(renderer);
				break;
			}
		}

		//check for hit from turret1
		for(int i = 0; i < turret2.bulletList.size(); i++)
		{
			if(SDL_HasIntersection(&tank1.posRect, &turret2.bulletList[i].posRect)){
				turret2.bulletList[i].Reset();
				playerHealth--;
				PlayerText(renderer);
				break;
			}
		}

		//check for hit from turret1
		for(int i = 0; i < turret3.bulletList.size(); i++)
		{
			if(SDL_HasIntersection(&tank1.posRect, &turret3.bulletList[i].posRect)){
				turret3.bulletList[i].Reset();
				playerHealth--;
				PlayerText(renderer);
				break;
			}
		}

		//check for hit from turret1
		for(int i = 0; i < turret4.bulletList.size(); i++)
		{
			if(SDL_HasIntersection(&tank1.posRect, &turret4.bulletList[i].posRect)){
				turret4.bulletList[i].Reset();
				playerHealth--;
				PlayerText(renderer);
				break;
			}
		}


		//check if the player hit a turret
		for(int i = 0; i < tank1.bulletList.size(); i++)
		{
			//turret 1
			if(SDL_HasIntersection(&turret1.baseRect, &tank1.bulletList[i].posRect)){
				tank1.bulletList[i].Reset();
				TurretText(renderer, 1);
				break;
			}
			//turret 2
			if(SDL_HasIntersection(&turret2.baseRect, &tank1.bulletList[i].posRect)){
				tank1.bulletList[i].Reset();
				TurretText(renderer, 2);
				break;
			}
			//turret 3
			if(SDL_HasIntersection(&turret3.baseRect, &tank1.bulletList[i].posRect)){
				tank1.bulletList[i].Reset();
				TurretText(renderer, 3);
				break;
			}
			//turret 4
			if(SDL_HasIntersection(&turret4.baseRect, &tank1.bulletList[i].posRect)){
				tank1.bulletList[i].Reset();
				TurretText(renderer, 4);
				break;
			}


		}


		//draw player 1 tank************************************
		//claer the SDL RenderTarget
		SDL_RenderClear(renderer);

		//dtaw the bkgd
		SDL_RenderCopy(renderer, bkgd, NULL, &bkgdRect);

		//draw the tank
		tank1.Draw(renderer);
		//draw the tuuret
		enemy1.Draw(renderer);

		//drawt he player hit tetture
		SDL_RenderCopy(renderer, playerTexture, NULL, &playerPos);

		//Draw the turret hit texture using the vars texture and posRext
		SDL_RenderCopy(renderer, turretTexture, NULL, &turretPos);

		//present new buffer to screen
		SDL_RenderPresent(renderer);


	}// end main loop

	//close and destroy the window
	SDL_DestroyWindow(window);

	//clean up
	SDL_Quit();

	return 0;

}



#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <string>
#include "Maps/Map.h"
#include <iostream>
#include "camera.h"
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();

bool loadMedia();

void close();


SDL_Texture* loadTexture(std::string path);

void drawScreen();

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

SDL_Texture* grass = NULL;
SDL_Texture* tree = NULL;
SDL_Texture* trans = NULL;

//The Currently loaded map
Map* loadedMap = NULL;

// My temporary map
int xTileLength = 12;
int yTileLength = 10;
Map myMap;

// The Camera for the game
Camera cam;

bool init() {

	if(	SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL could not be initialized! SDL Error %s\n", SDL_GetError() );
		return false;

	}
	// Set the txture filtering to be linear
	if(!(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))){
		printf( "Warning: Linear texture filtering not enabled! SDL Error %s\n", SDL_GetError() );
	}
	// Create the window
	gWindow = SDL_CreateWindow( "Coffee Quest", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if(gWindow == NULL){
		printf("Window could not be created! SDL Error %s\n", SDL_GetError());
		return false;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if(gRenderer == NULL){
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}

	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return false;
	}
	// Initialize one map
	myMap = Map(xTileLength, yTileLength);
	loadedMap = &myMap;

	// Initialize the Camera
	cam = Camera( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, loadedMap);

	return true;
}

bool loadMedia(){
	grass = loadTexture( "Textures/grass.png" );
	if( grass == NULL )
	{
		printf( "Failed to load texture image!\n" );
		return false;
	}

	tree = loadTexture("Textures/Basic_Tree_Texture_02.png");
	if( tree == NULL )
	{
		printf( "Failed to load texture image!\n" );
		return false;
	}
	trans = loadTexture("Textures/Transparent_Overlay_Dark.png");
	if( trans == NULL )
	{
		printf( "Failed to load texture image!\n" );
		return false;
	}

	//temp variable
	Tile* temp = NULL;
	//Setting the loaded texture to each of the tiles
	for(int i = 0; i<xTileLength;i++){
		for(int j = 0; j<yTileLength; j++){
			temp = loadedMap -> getTile(i,j);
			if(temp == NULL){
				//printf("Could not get tile " + i + "," +j"\n");
				cout << "Could not get tile " << i << "," << j << endl;
			}
			else{
				temp -> setTexture(grass);
			}
		}
	}


	return true;
}
void close(){
	//Free loaded image
	SDL_DestroyTexture(grass);
	grass = NULL;
	// Map free
	loadedMap = NULL;
	//cout << "about to free map" << endl;
	myMap.free();
	//cout << "map freed" << endl;
	// Destroy the window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
}

SDL_Texture* loadTexture( std::string path){
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

void drawScreen(){

	
	//Clear screen
	SDL_RenderClear( gRenderer );
	cam.renderToCamera( gRenderer );

	//SDL_Rect rect = {50, 50, 256, 256};	
	//SDL_RenderCopy(gRenderer, tree, NULL, &rect);
	//SDL_Rect rect1 = {75, 75, 256, 256};
	//SDL_RenderCopy(gRenderer, trans, NULL, &rect1);
	//Update screen
	SDL_RenderPresent( gRenderer );
}

void handleKeyPressDown(int keycode){
	//cout << "derp" << endl;
	switch(keycode) {
		case SDLK_UP:
			cam.setMoveValueY(-1);
			break;
		case SDLK_DOWN:
			cam.setMoveValueY(1);
			break;
		case SDLK_LEFT:
			cam.setMoveValueX(-1);
			break;
		case SDLK_RIGHT:
			cam.setMoveValueX(1);
		default:
		break;
	}
}

void handleKeyPressUp(int keycode){
	//printf("It works with key up! \n" );
	switch(keycode) {

		case SDLK_UP:
			cam.setMoveValueY(0);
			break;
		case SDLK_DOWN:
			cam.setMoveValueY(0);
			break;
		case SDLK_LEFT:
			cam.setMoveValueX(0);
			break;
		case SDLK_RIGHT:
			cam.setMoveValueX(0);
		default:
		break;
	}
}


int main(int argc, char* args[]){
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;
			//Event variable
			SDL_Event e;
			//While application is running
			while( !quit )
			{
				//Event handler	
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					switch(e.type){
						case SDL_QUIT:
							quit = true;
							break;
						case SDL_KEYUP:
							handleKeyPressUp(e.key.keysym.sym);
							break;
						case SDL_KEYDOWN:
							handleKeyPressDown(e.key.keysym.sym);
							break;
					}
				}
			//std::this_thread::sleep_for(std::chrono::milliseconds(1));
			//Update the camera
			cam.updateCamera();
			//draw the screen
			drawScreen();
			}



			}
		}

	//Free resources and close SDL
	close();

	return 0;
}


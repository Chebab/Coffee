
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <string>
#include "Maps/Map.h"
#include <iostream>
#include "camera.h"
#include "Shapes/Shapes.h"
#include "ObjectTesters.h"
#include "Player.h"
#include "cTimer.h"
#include "cTexture.h"

#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif





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

cTexture* testingText = NULL;

SDL_Texture* grass = NULL;
SDL_Texture* tree = NULL;
SDL_Texture* trans = NULL;
SDL_Texture* redCircle = NULL;
SDL_Texture* purpleCircle = NULL;
SDL_Texture* greenRect = NULL;
SDL_Texture* orangeRect = NULL;
SDL_Texture* playPic = NULL;

//CircleObject myObject;
//RectObject otherObject;
float xVelocity = 0;
float yVelocity = 0;
//bool moveBack = false;

//The Currently loaded map


// My temporary map
int xTileLength = 12;
int yTileLength = 10;
//Map tempMap(5,5);

Map* loadedMap = new Map(xTileLength,yTileLength);
// The Camera for the game
Camera cam;

// The Player
Player play;

// fps timer
chTimer fpsTimer;
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
    Tile* oldTile = loadedMap->getTile(xTileLength/2, yTileLength/2);
    oldTile->setWalkable(false);

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

    testingText = new cTexture();
    if( !testingText->loadFromFile("Textures/grass.png", gRenderer) )
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
    redCircle = loadTexture("Textures/64x64_circle.png");
    if( redCircle == NULL )
    {
        printf( "Failed to load texture image!\n" );
        return false;
    }
    purpleCircle = loadTexture("Textures/64x64_circle_purp.png");
    if( purpleCircle == NULL )
    {
        printf( "Failed to load texture image!\n" );
        return false;
    }
    greenRect = loadTexture("Textures/64x64_rect_green.png");
    if( purpleCircle == NULL )
    {
        printf( "Failed to load texture image!\n" );
        return false;
    }
    orangeRect = loadTexture("Textures/64x64_rect_orange.png");
    if( orangeRect == NULL )
    {
        printf( "Failed to load texture image!\n" );
        return false;
    }

    playPic = loadTexture("Textures/32x32_player.png");
    if( playPic == NULL )
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
                temp -> setTexture(testingText->getTexture());//setTexture(grass);
			}
		}
	}
    Tile* oldTile = loadedMap->getTile(xTileLength/2, yTileLength/2);
    oldTile->setTexture(orangeRect);
    
    
    

	return true;
}
void close(){
	//Free loaded image
	SDL_DestroyTexture(grass);
    SDL_DestroyTexture(tree);
    SDL_DestroyTexture(trans);
    SDL_DestroyTexture(redCircle);
    SDL_DestroyTexture(purpleCircle);
    SDL_DestroyTexture(greenRect);
    SDL_DestroyTexture(orangeRect);
    SDL_DestroyTexture(playPic);
    
    testingText->free();
	grass = NULL;
	// Map free
    //delete loadedMap;
	//loadedMap = NULL;
	//cout << "about to free map" << endl;
	//myMap.~Map();
    //play.~Player();
    //cam.~Camera();
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
    /*
    char cCurrentPath[FILENAME_MAX];
    
    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {
        return nullptr;
    }
    printf ("The current working directory is %s", cCurrentPath);
     */
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
    play.render(gRenderer);
	SDL_RenderPresent( gRenderer );
}

void handleKeyPressDown(int keycode){
	//cout << "derp" << endl;
    const float velo =0.5;
	switch(keycode) {
		case SDLK_UP:
			//cam.setMoveValueY(-1);
            yVelocity = -velo;
			break;
		case SDLK_DOWN:
			//cam.setMoveValueY(1);
            yVelocity = velo;
			break;
		case SDLK_LEFT:
			//cam.setMoveValueX(-1);
            xVelocity = -velo;
			break;
		case SDLK_RIGHT:
			//cam.setMoveValueX(1);
            xVelocity = velo;
            break;
        case SDLK_SPACE:
            //moveBack = true;
		default:
		break;
	}
}

void handleKeyPressUp(int keycode){
	//printf("It works with key up! \n" );
	switch(keycode) {

		case SDLK_UP:
			//cam.setMoveValueY(0);
            yVelocity = 0;
			break;
		case SDLK_DOWN:
			//cam.setMoveValueY(0);
            yVelocity = 0;
			break;
		case SDLK_LEFT:
			//cam.setMoveValueX(0);
            xVelocity = 0;
			break;
		case SDLK_RIGHT:
			//cam.setMoveValueX(0);
            xVelocity = 0;
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
            // Init the testobjects
            //myObject = CircleObject(50.0,50.0,32.0,purpleCircle);
            //otherObject = RectObject(200.0,200.0,64.0,greenRect);
            Uint32 rendercount = 0;
            fpsTimer.start();
            // Init player
            int startX = 20;
            int startY = 20;
            play = Player(startX, startY, loadedMap, loadedMap->getTileFromPos(startX, startY), playPic);
            
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
                bool moved = play.movePlayer(xVelocity, yVelocity);
                if (!moved) {
                    printf("Could not move\n");
                }
                //Calculate and correct fps
                float avgFPS = rendercount / ( fpsTimer.GetTime() / 1000.f );
                if( avgFPS > 2000000 )
                {
                    avgFPS = 0;
                    rendercount = 0;
                    fpsTimer.stop();
                    fpsTimer.start();
                }
			//Update the camera
            //Camera that follows the player
                //TODO: Fix the camera so that is follows the player correctly
                /*cam.setXpos(play.getXpos());
                cam.setYpos(play.getYpos());
                cam.updateCamera();*/
			//draw the screen
                printf("FPS: %f\n",avgFPS);
                drawScreen();
                ++rendercount;
			}



			}
		}

	//Free resources and close SDL
	close();

	return 0;
}


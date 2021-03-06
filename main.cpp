
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
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
#include "texture_info.h"

#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#define GAME_FREQUENCY 120 // 1/s
#define FPS 60



using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();

bool loadMedia();

bool createMap();

void close();

void drawScreen();

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

TTF_Font* cFont = NULL;
/*
 cTexture* grass        = new cTexture();
 cTexture* orangeRect   = new cTexture();
 cTexture* playPic      = new cTexture();
 cTexture* fpsText      = new cTexture();
 */

std::vector<cTexture*> tile_texture;
std::vector<cTexture*> player_texture;

float xVelocity = 0;
float yVelocity = 0;
//bool moveBack = false;

// Game update time

// My temporary map
int xTileLength = 12;
int yTileLength = 10;
//Map tempMap(5,5);

Map* loadedMap;
// The Camera for the game
Camera* cam;

// The Player
Player play;

// fps timer
chTimer fpsTimer;
chTimer gameTimer;
chTimer renderTimer;
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
    
    // Initialize image loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return false;
    }
    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        return false;
    }
    
    return true;
}

bool loadMedia(){
    
    // Load all tile textures
    for (int i=0; i<tile_texture_files.size(); i++) {
        cTexture* load_text = new cTexture();
        printf("Textpath: %s\n",tile_texture_files[i].c_str());
        if( !load_text -> loadFromFile(tile_texture_files[i], gRenderer) )
        {
            printf( "Failed to load texture image!\n" );
            return false;
        }
        else{
            tile_texture.push_back(load_text);
        }
    }
    
    grass = tile_texture[i_grass];
    orangeRect = tile_texture[i_wall];
    
    printf("loaded tile textures: %d\n",(int)tile_texture.size());
    // Load all player textures
    for (int i=0; i<player_texture_files.size(); i++) {
        cTexture* load_text = new cTexture();
        printf("Textpath: %s\n",player_texture_files[i].c_str());
        if( !load_text -> loadFromFile(player_texture_files[i], gRenderer) )
        {
            printf( "Failed to load texture image!\n" );
            return false;
        }
        else{
            player_texture.push_back(load_text);
        }
    }
    
    // Set the starting pic
    playPic = player_texture[0];
    
    
    printf("loaded player textures: %d\n",(int)player_texture.size());
    //    if( !playPic->loadFromFile("Textures/32x32_player.png", gRenderer) )
    //    {
    //        printf( "Failed to load texture image!\n" );
    //        return false;
    //    }
    
    //Open the font
    cFont = TTF_OpenFont( "Textures/Oswald-Bold.ttf", 36 );
    if( cFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        return false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 0, 0, 0 };
        if( !fpsText->loadFromRenderedText( "The quick brown fox jumps over the lazy dog", textColor,cFont,gRenderer ) )
        {
            printf( "Failed to render text texture!\n" );
            return false;
        }
    }
    
    
    return true;
}

bool createMap(){
    

    loadedMap = new Map("Maps/testmap.txt");
    // Initialize the Camera
    cam = new Camera( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, loadedMap);
    
    
    return true;
}

void close(){
    
    // Close all tile texures
    for (int i = 0; i<tile_texture.size(); i++) {
        tile_texture[i]->free();
    }
    
    // Close all player textrues
    for (int i = 0; i<player_texture.size(); i++) {
        player_texture[i]->free();
    }
    //Free loaded image
    //grass->free();
    //playPic->free();
    //orangeRect->free();
    loadedMap->free();
    fpsText->free();
    delete cam;
    
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


void drawScreen(){
    
    
    //Clear screen
    SDL_RenderClear( gRenderer );
    
    
    cam->renderToCamera( gRenderer );
    play.render(gRenderer);
    fpsText->render(gRenderer,10,350);
    
    SDL_RenderPresent( gRenderer );
}

void handleKeyPressDown(int keycode){
    //cout << "derp" << endl;
    const float velo =1.0f;
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
    //Load media
    else if( !loadMedia() )
    {
        printf( "Failed to load media!\n" );
    }
    else if (!createMap())
    {
        printf( "Failed to create map!\n" );
    }
    else
    {
        Uint32 rendercount = 0;
        fpsTimer.start();
        gameTimer.start();
        renderTimer.start();
        // Init player
        int startX = 50;
        int startY = 50;
        play = Player(startX, startY, loadedMap, loadedMap->getTileFromPos(startX, startY), playPic->getTexture());
        
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
            if (1.0f/(float)GAME_FREQUENCY < gameTimer.GetTime()/1000.0f)
            {
                gameTimer.stop();
                bool moved = play.movePlayer(xVelocity, yVelocity);
                if (!moved) {
                    printf("Could not move\n");
                }
                gameTimer.start();
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
            
            //printf("FPS: %f\n",avgFPS);
            
            if (1.0f/(float)FPS < renderTimer.GetTime() / 1000.f) {
                renderTimer.stop();
                SDL_Color textColor = { 0, 0, 0 };
                // Memmory problems DO NOT USE
                fpsText->loadFromRenderedText(to_string((int)avgFPS), textColor, cFont, gRenderer);
                drawScreen();
                ++rendercount;
                renderTimer.start();
            }
        }
        
        
        
        
    }
    
    //Free resources and close SDL
    close();
    
    return 0;
}


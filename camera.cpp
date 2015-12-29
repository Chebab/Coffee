#include "camera.h"

Camera::Camera(){
	target = NULL;
}

Camera::~Camera(){
	xCoordinate = 0;
	yCoordinate = 0;
	movex = 0;
	movey = 0;
	VIEWPORT_WIDTH = 0;
	VIEWPORT_HEIGHT = 0;
	target = NULL;
}

Camera::Camera(int startingXpos, int startingYpos,
	int CameraWidth, int CameraHeight, Map* targetMap){

	xCoordinate = startingXpos;
	yCoordinate = startingYpos;
	movex = 0;
	movey = 0;
	VIEWPORT_WIDTH = CameraWidth;
	VIEWPORT_HEIGHT = CameraHeight;
	target = targetMap;
	if(target == NULL){
		printf("Warning! No map has been set to the camera! \n");
	}
}

int Camera::getXpos(){
	return xCoordinate;
}
int Camera::getYpos(){
	return yCoordinate;
}

void Camera::setXpos(int addToPos){
	xCoordinate = addToPos;
}

void Camera::setYpos(int addToPos){
	yCoordinate = addToPos;
}

void Camera::setMoveValueX(int x){
	movex = x;
}

void Camera::setMoveValueY(int y){
	movey = y;
}

void Camera::updateCamera(){
	xCoordinate += movex;
	yCoordinate += movey;
}
int Camera::getViewWidth(){
	return VIEWPORT_WIDTH;
}
int Camera::getViewHeight(){
	return VIEWPORT_HEIGHT;
}

void Camera::setMap(Map* newmap){
	target = newmap;
	if(target == NULL){
		printf("Warning! No map has been set to the camera! \n");
	}
}

Map* Camera::getMap(){
	return target;
}

void Camera::renderToCamera(SDL_Renderer* gRend){
	Tile* loadedTile;
	// The current position of the right and the left
	// edge of the camera in coordinates
	int rightEdgePos = xCoordinate + VIEWPORT_WIDTH;
	int bottomEdgePos = yCoordinate + VIEWPORT_HEIGHT;


	for(int j = 0; j < bottomEdgePos; j += TILE_SIZE ){
		for(int i = 0; i < rightEdgePos; i += TILE_SIZE){
			loadedTile = target->getTileFromPos(i,j);
			if(!(loadedTile==NULL)){
				loadedTile->renderer(gRend, getXpos(), getYpos());
			}
		}
	}

}



#ifndef CAMERA_H
#define CAMERA_H
#include "Maps/Map.h"
#include "Player.h"
class Camera {
private:
	int xCoordinate;
	int yCoordinate;
	int VIEWPORT_WIDTH;
	int VIEWPORT_HEIGHT;
	int movex;
	int movey;
	Map* target;
    
public:
	Camera();

	~Camera();

	Camera(int,int,int, int, Map*);

	int getXpos();
	int getYpos();

	void setXpos(int);
	void setYpos(int);

	void setMoveValueX(int);

	void setMoveValueY(int);

	void updateCamera();

	int getViewWidth();
	int getViewHeight();

	void setMap(Map*);

	Map* getMap();
	void renderToCamera(SDL_Renderer*);
};

#endif
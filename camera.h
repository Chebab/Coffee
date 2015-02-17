


#ifndef CAMERA_H
#define CAMERA_H
#include "Maps/Map.h"
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
	// adds the argument to the xCoordinate
	void setXpos(int);
	// adds the argument to the yCoordinate
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
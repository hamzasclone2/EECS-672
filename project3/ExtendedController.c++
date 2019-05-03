// ExtendedController.c++

#include "ExtendedController.h"
#include "ModelView.h"

ExtendedController::ExtendedController(const std::string& name, int rcFlags):
	GLFWController(name, rcFlags)
{
}

void ExtendedController::handleMouseMotion(int x, int y)
{
	//std::cout << "Implement ExtendedController::handleMouseMotion!\n";
	// 1. Get a pixel (dx, dy)
	int dx = x-screenBaseX;
	int dy = y-screenBaseY;
	// 2. update screenbaseX, screenBaseY
	screenBaseX = x;
	screenBaseY = y;
	// 3. if translation, map (dx, dy) to (dxInLDS, dyInLDS) and pass to
	//    ModelView::addToGlobalPan
	int dimensions[4];
	glGetIntegerv(GL_VIEWPORT, dimensions);
	int max_x = dimensions[2];
	int max_y = dimensions[3];

	double midpoint_x = max_x/2;
	double midpoint_y = max_y/2;

 	double dxInLDS = dx / midpoint_x;
 	double dyInLDS = -dy / midpoint_y;
	if(mouseMotionIsTranslate){
		ModelView::addToGlobalPan(dxInLDS, dyInLDS, 0);
	}
	// 4. else if rotation, map (dx, dy) to rotation angles and pass to
	//    ModelView::addToGlobalRotationDegrees.
	if(mouseMotionIsRotate){
		double rotX = dy*(360.0/500.0);
		double rotY = dx*(360.0/500.0);
		ModelView::addToGlobalRotationDegrees(rotX, rotY, 0);
	}
	// 5. do a redraw()
	redraw();
}

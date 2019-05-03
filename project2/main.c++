// main.c++: Starter for EECS 672 Projects 2-4
//Hamza Hameed Project 2
#include "ExtendedController.h"

#include "Block.h"
#include "Cylinder.h"
#include "Building.h"
#include "Car.h"
#include "Tree.h"

#include <stdlib.h>

void createScene(ExtendedController& c, ShaderIF* sIF)
{
	srand(time(NULL));
	int colors[7] = {255, 102, 178, 51, 153, 128, 0};
	Building* b = new Building(sIF, 0.0, 1.0, 1.0, colors[rand()%6], colors[rand()%6], colors[rand()%6]);
	Building* b2 = new Building(sIF, 10.0, 1.0, 1.0, colors[rand()%6], colors[rand()%6], colors[rand()%6]);
	Building* b3 = new Building(sIF, 20.0, 1.0, 1.0, colors[rand()%6], colors[rand()%6], colors[rand()%6]);
	Building* b4 = new Building(sIF, 30.0, 1.0, 1.0, colors[rand()%6], colors[rand()%6], colors[rand()%6]);
	Building* b5 = new Building(sIF, -10.0, 1.0, 1.0, colors[rand()%6], colors[rand()%6], colors[rand()%6]);
	Building* b6 = new Building(sIF, -20.0, 1.0, 1.0, colors[rand()%6], colors[rand()%6], colors[rand()%6]);
	Building* b7 = new Building(sIF, -30.0, 1.0, 1.0, colors[rand()%6], colors[rand()%6], colors[rand()%6]);

	Block* green = new Block(sIF, -35.0, 0.5, 0.0, 75.0, 0.5, 10.0, 0, 102.0, 0);
	Block* road = new Block(sIF, -35.0, 0.5, 10.0, 75.0, 0.5, 15.0, 160.0, 160.0, 160.0);
	Block* green2 = new Block(sIF, -35.0, 0.5, 25.0, 75.0, 0.5, 10.0, 0, 102.0, 0);

	Block* strip = new Block(sIF, 0.0, 0.9, 17.5, 5.0, 0.2, 0.75, 255, 255, 255);
	c.addModel(strip);
	Block* strip1 = new Block(sIF, -10.0, 0.9, 17.5, 5.0, 0.2, 0.75, 255, 255, 255);
	c.addModel(strip1);
	Block* strip2 = new Block(sIF, 10.0, 0.9, 17.5, 5.0, 0.2, 0.75, 255, 255, 255);
	c.addModel(strip2);
	Block* strip3 = new Block(sIF, -20.0, 0.9, 17.5, 5.0, 0.2, 0.75, 255, 255, 255);
	c.addModel(strip3);
	Block* strip4 = new Block(sIF, 20.0, 0.9, 17.5, 5.0, 0.2, 0.75, 255, 255, 255);
	c.addModel(strip4);
	Block* strip5 = new Block(sIF, 30.0, 0.9, 17.5, 5.0, 0.2, 0.75, 255, 255, 255);
	c.addModel(strip5);
	Block* strip6 = new Block(sIF, -30.0, 0.9, 17.5, 5.0, 0.2, 0.75, 255, 255, 255);
	c.addModel(strip6);


	c.addModel(b);
	c.addModel(b2);
	c.addModel(b3);
	c.addModel(b4);
	c.addModel(b5);
	c.addModel(b6);
	c.addModel(b7);
	c.addModel(road);
	c.addModel(green);
	c.addModel(green2);

	Car* c1 = new Car(sIF, 0.0, 1.25, 13.0, colors[rand()%6], colors[rand()%6], colors[rand()%6]);
	Car* c2 = new Car(sIF, 6.0, 1.25, 21.0, colors[rand()%6], colors[rand()%6], colors[rand()%6]);
	Car* c3 = new Car(sIF, -5.0, 1.25, 21.0, colors[rand()%6], colors[rand()%6], colors[rand()%6]);
	Car* c4 = new Car(sIF, 18.0, 1.25, 13.0, colors[rand()%6], colors[rand()%6], colors[rand()%6]);
	Car* c5 = new Car(sIF, -10.0, 1.25, 13.0, colors[rand()%6], colors[rand()%6], colors[rand()%6]);
	Car* c6 = new Car(sIF, -15.0, 1.25, 21.0, colors[rand()%6], colors[rand()%6], colors[rand()%6]);
	Car* c7 = new Car(sIF,-25.0, 1.25, 13.0, colors[rand()%6], colors[rand()%6], colors[rand()%6]);
	Car* c8 = new Car(sIF, 30.0, 1.25, 13.0, colors[rand()%6], colors[rand()%6], colors[rand()%6]);
	Car* c9 = new Car(sIF, 22.0, 1.25, 21.0, colors[rand()%6], colors[rand()%6], colors[rand()%6]);


	c.addModel(c1);
	c.addModel(c2);
	c.addModel(c3);
	c.addModel(c4);
	c.addModel(c5);
	c.addModel(c6);
	c.addModel(c7);
	c.addModel(c8);
	c.addModel(c9);

	Tree* t1 = new Tree(sIF, 5.0, 1.0, 27.0);
	Tree* t2 = new Tree(sIF, 10.0, 1.0, 30.0);
	Tree* t3 = new Tree(sIF, 13.0, 1.0, 32.0);
	Tree* t4 = new Tree(sIF, 22.0, 1.0, 28.0);
	Tree* t5 = new Tree(sIF, 31.0, 1.0, 31.0);
	Tree* t6 = new Tree(sIF, 0.0, 1.0, 27.5);
	Tree* t7 = new Tree(sIF, -6.0, 1.0, 29.0);
	Tree* t8 = new Tree(sIF, -11.0, 1.0, 31.0);
	Tree* t9 = new Tree(sIF, -24.0, 1.0, 30.0);
	Tree* t10 = new Tree(sIF, -28.0, 1.0, 32.0);
	Tree* t11 = new Tree(sIF, -33.0, 1.0, 27.0);
	c.addModel(t1);
	c.addModel(t2);
	c.addModel(t3);
	c.addModel(t4);
	c.addModel(t5);
	c.addModel(t6);
	c.addModel(t7);
	c.addModel(t8);
	c.addModel(t9);
	c.addModel(t10);
	c.addModel(t11);

	Tree* t12 = new Tree(sIF, -33.0, 1.0, 3.0);
	c.addModel(t12);
	Tree* t13 = new Tree(sIF, -23.0, 1.0, 3.0);
	c.addModel(t13);
	Tree* t14 = new Tree(sIF, -13.0, 1.0, 3.0);
	c.addModel(t14);
	Tree* t15 = new Tree(sIF, -3.0, 1.0, 3.0);
	c.addModel(t15);
	Tree* t16 = new Tree(sIF, 7.0, 1.0, 3.0);
	c.addModel(t16);
	Tree* t17 = new Tree(sIF, 17.0, 1.0, 3.0);
	c.addModel(t17);
	Tree* t18 = new Tree(sIF, 27.0, 1.0, 3.0);
	c.addModel(t18);
	Tree* t19 = new Tree(sIF, 37.0, 1.0, 3.0);
	c.addModel(t19);

}

void set3DViewingInformation(double overallBB[])
{
	// IF we are using Viewing Strategy #1, THEN
	//     Notify class ModelView that we initially want to see the entire scene:
	//   ModelView::setMCRegionOfInterest(overallBB);
	// ELSE (Viewing Strategy #2)
	//     Modify all three of deltaX, deltaY, and deltaZ of the incoming overallBB
	//     to have the dimensions of the desired field of view, then invoke:
	//   ModelView::setMCRegionOfInterest(modified_overallBB);
	//   Tell the ModelView class that dynamic rotations are to be done about the eye.
	ModelView::setMCRegionOfInterest(overallBB);
	// MC -> EC:

	cryph::AffPoint eye, center;
	cryph::AffVector up;

	double r = (overallBB[1]-overallBB[0]);
	if((overallBB[3]-overallBB[2]) > r){
		r = (overallBB[3]-overallBB[2]);
	}
	if((overallBB[5]-overallBB[4]) > r){
		r = (overallBB[5]-overallBB[4]);
	}

	center.assign((overallBB[0] + overallBB[1])/2, (overallBB[2] + overallBB[3])/2, (overallBB[4] + overallBB[5])/2);
	cryph::AffVector dir;
	dir.assign(0,0,1);
	double d = 3.5 * r;
	eye = center + d * dir;
	up.assign(0,1,0);
	ModelView::setEyeCenterUp(eye, center, up);

	// EC -> LDS:

	// Specify the initial projection type desired
	ModelView::setProjection(PERSPECTIVE);

	double ecZmin, ecZmax;

	ecZmin = -d-r;
	ecZmax = -d+r;
	ModelView::setECZminZmax(ecZmin, ecZmax);

	double ecZpp;
	ecZpp = ecZmax;
	ModelView::setProjectionPlaneZ(ecZpp);
}

int main(int argc, char* argv[])
{
	ExtendedController c("--Hamza Hameed Project 2: A Colorful Street--", MVC_USE_DEPTH_BIT);
	c.reportVersions(std::cout);

	ShaderIF* sIF = new ShaderIF("shaders/basic.vsh", "shaders/phong.fsh");

	createScene(c, sIF);

	glClearColor(1.0, 1.0, 1.0, 1.0);

	double xyz[6];
	c.getOverallMCBoundingBox(xyz);
	std::cout << "Bounding box: " << xyz[0] << " <= x <= " << xyz[1] << '\n';
	std::cout << "              " << xyz[2] << " <= y <= " << xyz[3] << '\n';
	std::cout << "              " << xyz[4] << " <= z <= " << xyz[5] << "\n\n";
	set3DViewingInformation(xyz);

	c.run();

	delete sIF;

	return 0;
}

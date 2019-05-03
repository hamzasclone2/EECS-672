// Truck.h

#ifndef Truck_H
#define Truck_H

#include "Block.h"
#include "Cylinder.h"
#include "SceneElement.h"

class Truck : public SceneElement
{
public:
	// As before: you will likely want to add parameters to the constructor
	Truck(ShaderIF* sIF, float cx, float cy, float cz, PhongMaterial& p);
	virtual ~Truck();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
	float xmin, xmax, ymin, ymax, zmin, zmax;
	Block* blocks[6];
	Cylinder* cyls[10];
};

#endif

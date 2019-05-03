// Car.h

#ifndef Car_H
#define Car_H

#include "Block.h"
#include "Cylinder.h"
#include "SceneElement.h"

class Car : public SceneElement
{
public:
	// As before: you will likely want to add parameters to the constructor
	Car(ShaderIF* sIF, float cx, float cy, float cz, PhongMaterial& p);
	virtual ~Car();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
	float xmin, xmax, ymin, ymax, zmin, zmax;
	Block* blocks[5];
	Cylinder* cyls[4];
};

#endif

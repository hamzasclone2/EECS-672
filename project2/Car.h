// Car.h

#ifndef Car_H
#define Car_H

#include "ModelView.h"
#include "ShaderIF.h"
#include "Block.h"
#include "Cylinder.h"

class Car : public ModelView
{
public:
	// As before: you will likely want to add parameters to the constructor
	Car(ShaderIF* sIF, float cx, float cy, float cz, int r, int g, int b);
	virtual ~Car();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
	float xmin, xmax, ymin, ymax, zmin, zmax;
	Block* blocks[5];
	Cylinder* cyls[4];
	ShaderIF* shaderIF;
	float ka[3], kd[3];
};

#endif

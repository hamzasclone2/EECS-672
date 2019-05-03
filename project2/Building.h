// Building.h

#ifndef Building_H
#define Building_H

#include "ModelView.h"
#include "ShaderIF.h"
#include "Block.h"

class Building : public ModelView
{
public:
	Building(ShaderIF* sIF, float cx, float cy, float cz, int r, int g, int b);
	virtual ~Building();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void renderBuilding();
	void render();
private:
	float xmin, xmax, ymin, ymax, zmin, zmax;
	Block* blocks[10];
	ShaderIF* shaderIF;
	float ka[3], kd[3];
};

#endif

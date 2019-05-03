// Building.h

#ifndef Building_H
#define Building_H

#include "Block.h"
#include "SceneElement.h"

class Building : public SceneElement
{
public:
	Building(ShaderIF* sIF, float cx, float cy, float cz, PhongMaterial& p);
	virtual ~Building();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void renderBuilding();
	void render();
private:
	float xmin, xmax, ymin, ymax, zmin, zmax;
	Block* blocks[10];
};

#endif

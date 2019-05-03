// Tree.h

#ifndef Tree_H
#define Tree_H

#include "SceneElement.h"

#include "Cylinder.h"
#include "Block.h"

class Tree : public SceneElement
{
public:
	// As before: you will likely want to add parameters to the constructor
	Tree(ShaderIF* sIF, float cx, float cy, float cz);
	virtual ~Tree();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
	Cylinder* cyls[3];
	Block* block;
	float xmin, xmax, ymin, ymax, zmin, zmax;
};

#endif

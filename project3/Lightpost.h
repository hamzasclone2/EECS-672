// lightpost.h

#ifndef Lightpost_H
#define Lightpost_H

#include "SceneElement.h"

#include "Block.h"

class Lightpost : public SceneElement
{
public:
	// As before: you will likely want to add parameters to the constructor
	Lightpost(ShaderIF* sIF, float cx, float cy, float cz);
	virtual ~Lightpost();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
	Block* blocks[4];
	float xmin, xmax, ymin, ymax, zmin, zmax;
};

#endif

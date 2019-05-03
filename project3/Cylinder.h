// Cylinder.h

#ifndef CYLINDER_H
#define CYLINDER_H

#include <GL/gl.h>

#include "SceneElement.h"

class Cylinder : public SceneElement
{
public:
	Cylinder(ShaderIF* sIF, double z1, double z2, double yb, double xb,
			 double radius, PhongMaterial& p);
	virtual ~Cylinder();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimits) const;
	bool handleCommand(unsigned char anASCIIChar, double ldsX, double ldsY);
	void render();
	void renderCylinder();
private:
	GLuint vao[3];
	GLuint vbo[2];
	GLuint vbo1[2];
	GLuint vbo2[2]; // 0: coordinates; 1: normal vectors
	double xmin, xmax, ymin, ymax, zmin, zmax;

	void defineCylinder(double x1, double x2, double yb, double zb, double r);
	void defineEnd(double z, double yb, double xb, double radius);
	void defineEndPos(double z, double yb, double xb, double radius);
};

#endif

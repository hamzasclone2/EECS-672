// Cylinder.h

#ifndef CYLINDER_H
#define CYLINDER_H

#include <GL/gl.h>

#include "ModelView.h"
#include "ShaderIF.h"

class Cylinder : public ModelView
{
public:
	Cylinder(ShaderIF* sIF, double z1, double z2, double yb, double xb,
			 double radius, int r, int g, int b);
	virtual ~Cylinder();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimits) const;
	bool handleCommand(unsigned char anASCIIChar, double ldsX, double ldsY);
	void render();
	void renderCylinder();
private:
	ShaderIF* shaderIF;
	GLuint vao[3];
	GLuint vbo[2];
	GLuint vbo1[2];
	GLuint vbo2[2]; // 0: coordinates; 1: normal vectors
	float kd[3];
	double xmin, xmax, ymin, ymax, zmin, zmax;

	void defineCylinder(double x1, double x2, double yb, double zb, double r);
	void defineEnd(double z, double yb, double xb, double radius);
	void defineEndPos(double z, double yb, double xb, double radius);
};

#endif

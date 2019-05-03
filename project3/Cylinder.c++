// Cylinder.c++

#include <iostream>
#include <math.h>

#include "Cylinder.h"

// *************************************************************************
// EXERCISE: Modify the constructor prototype to accept information
//           necessary to address the EXERCISE in Cylinder::defineCylinder.
// *************************************************************************
// This simple Cylinder class creates a cylinder along the x-axis:
// (x1, yb, zb) to (x2, yb, zb) with radius=r
Cylinder::Cylinder(ShaderIF* sIF, double z1, double z2, double yb, double xb,
				   double radius, PhongMaterial& p) : SceneElement(sIF)
{
	matl = p;

	xmin = xb - radius;
	xmax = xb + radius;
	ymin = yb - radius;
	ymax = yb + radius;
	zmin = z1;
	zmax = z2;
	glGenVertexArrays(3, vao);
	defineCylinder(z1, z2, yb, xb, radius);
	defineEnd(z1, yb, xb, radius);
	defineEndPos(z2, yb, xb, radius);

}

Cylinder::~Cylinder()
{
	glDeleteBuffers(2, vbo);
	glDeleteVertexArrays(1, vao);
}

const int N_POINTS_AROUND_SLICE = 40; // number points around a cross-section

void Cylinder::defineEnd(double z, double yb, double xb, double radius){
	typedef float vec3[3];
	int nPoints = (N_POINTS_AROUND_SLICE + 2); // "+1" because last point = first
	vec3* coords = new vec3[nPoints];
	vec3* normals = new vec3[nPoints];
	double theta = 0.0;
	double dTheta = 2.0*M_PI/N_POINTS_AROUND_SLICE;

	coords[0][0] = xb;
	coords[0][1] = yb;
	coords[0][2] = z;

	normals[0][0] = 0;
	normals[0][1] = 0;
	normals[0][2] = -1;


	for (int i=1 ; i < nPoints ; i++)
	{
		// Each time through this loop, create two points and their corresponding
		// (and common) normal vectors

		// Refer to 672's InClass/3DModeling/3DGeometryAndAttributeModeling101.html
		float ny = radius*cos(theta) + yb;
		float nx = radius*sin(theta) + xb;

		coords[i][0] = nx;
		coords[i][1] = ny;
		coords[i][2] = (float)z;
		normals[i][0] = nx;
		normals[i][1] = ny;
		normals[i][2] = 0;
		theta += dTheta;
	}

	glBindVertexArray(vao[2]);

	glGenBuffers(2, vbo2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2[0]);
	glBufferData(GL_ARRAY_BUFFER, nPoints*sizeof(vec3), coords, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));

	glBindBuffer(GL_ARRAY_BUFFER, vbo2[1]);
	glBufferData(GL_ARRAY_BUFFER, nPoints*sizeof(vec3), normals, GL_STATIC_DRAW);

	glVertexAttribPointer(shaderIF->pvaLoc("mcNormal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcNormal"));

	delete [] coords;
	delete [] normals;
}

void Cylinder::defineEndPos(double z, double yb, double xb, double radius){
	typedef float vec3[3];
	int nPoints = (N_POINTS_AROUND_SLICE + 2); // "+1" because last point = first
	vec3* coords = new vec3[nPoints];
	vec3* normals = new vec3[nPoints];
	double theta = 0.0;
	double dTheta = 2.0*M_PI/N_POINTS_AROUND_SLICE;

	coords[0][0] = xb;
	coords[0][1] = yb;
	coords[0][2] = z;

	normals[0][0] = 0;
	normals[0][1] = 0;
	normals[0][2] = 1;


	for (int i=1 ; i < nPoints ; i++)
	{
		// Each time through this loop, create two points and their corresponding
		// (and common) normal vectors

		// Refer to 672's InClass/3DModeling/3DGeometryAndAttributeModeling101.html
		float ny = radius*cos(theta) + yb;
		float nx = radius*sin(theta) + xb;

		coords[i][0] = nx;
		coords[i][1] = ny;
		coords[i][2] = (float)z;
		normals[i][0] = nx;
		normals[i][1] = ny;
		normals[i][2] = 0;
		theta += dTheta;
	}


	glBindVertexArray(vao[1]);

	glGenBuffers(2, vbo1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo1[0]);
	glBufferData(GL_ARRAY_BUFFER, nPoints*sizeof(vec3), coords, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));

	glBindBuffer(GL_ARRAY_BUFFER, vbo1[1]);
	glBufferData(GL_ARRAY_BUFFER, nPoints*sizeof(vec3), normals, GL_STATIC_DRAW);

	glVertexAttribPointer(shaderIF->pvaLoc("mcNormal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcNormal"));

	delete [] coords;
	delete [] normals;
}

void Cylinder::defineCylinder(double z1, double z2, double yb, double xb, double r)
{
	typedef float vec3[3];
	int nPoints = 2 * (N_POINTS_AROUND_SLICE + 1); // "+1" because last point = first
	vec3* coords = new vec3[nPoints];
	vec3* normals = new vec3[nPoints];
	double theta = 0.0;
	double dTheta = 2.0*M_PI/N_POINTS_AROUND_SLICE;

	for (int i=0 ; i < nPoints ; i+=2)
	{
		// Each time through this loop, create two points and their corresponding
		// (and common) normal vectors

		// Refer to 672's InClass/3DModeling/3DGeometryAndAttributeModeling101.html
		float ny = r*cos(theta) + yb;
		float nx = r*sin(theta) + xb;

		coords[i][0] = nx;
		coords[i][1] = ny;
		coords[i][2] = (float)z1;
		coords[i+1][0] = nx;
		coords[i+1][1] = ny;
		coords[i+1][2] = (float)z2;
		normals[i][0] = normals[i+1][0] = nx;
		normals[i][1] = normals[i+1][1] = ny;
		normals[i][2] = normals[i+1][2] = 0;
		theta += dTheta;
	}

	//glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);

	glGenBuffers(2, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, nPoints*sizeof(vec3), coords, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, nPoints*sizeof(vec3), normals, GL_STATIC_DRAW);

	glVertexAttribPointer(shaderIF->pvaLoc("mcNormal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcNormal"));

	delete [] coords;
	delete [] normals;
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Cylinder::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}

bool Cylinder::handleCommand(unsigned char anASCIIChar, double ldsX, double ldsY)
{
	// Cylinder does not look for events. Just hand off back to inherited handleCommand.
	return this->ModelView::handleCommand(anASCIIChar, ldsX, ldsY);
}

void Cylinder::renderCylinder()
{
	//glUniform3fv(shaderIF->ppuLoc("kd"), 1, kd);
	//matl = PhongMaterial(ra, ga, ba, 1.0, 1.0, 1.0, 1.0, 1.0);
	establishMaterial(matl);

	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 2*(N_POINTS_AROUND_SLICE+1));

	glBindVertexArray(vao[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, N_POINTS_AROUND_SLICE + 2);
	glBindVertexArray(vao[2]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, N_POINTS_AROUND_SLICE + 2);
}

void Cylinder::render()
{
	typedef float vec3[3];
	GLint pgm;
	glGetIntegerv(GL_CURRENT_PROGRAM, &pgm);
	glUseProgram(shaderIF->getShaderPgmID());

	// cryph::Matrix4x4 mc_ec, ec_lds;
	// getMatrices(mc_ec, ec_lds);
	// float mat[16];
	// glUniformMatrix4fv(shaderIF->ppuLoc("mc_ec"), 1, false, mc_ec.extractColMajor(mat));
	// glUniformMatrix4fv(shaderIF->ppuLoc("ec_lds"), 1, false, ec_lds.extractColMajor(mat));

	establishView();
	establishLightingEnvironment();

	renderCylinder();

	glUseProgram(pgm);
}

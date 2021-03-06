// Car.c++

#include "Car.h"


Car::Car(ShaderIF* sIF, float cx, float cy, float cz, int r, int g, int b) : shaderIF(sIF)
{
	xmin = cx;
    xmax = cx+3.0;
    ymin = cy;
    ymax = cy+0.5;
    zmin = cz;
    zmax = cz+2.0;

	blocks[0] = new Block(sIF, cx, cy, cz, 3.0, 1.0, 2.0, r, g, b);
	blocks[1] = new Block(sIF, cx+0.5, 1.5*cy, cz, 2.0, 1.0, 2.0, r, g, b);
	blocks[2] = new Block(sIF, cx+0.4, 1.4*cy, cz+0.1, 0.5, 0.9, 1.8, 204, 255, 255);
	blocks[3] = new Block(sIF, cx-0.1, cy+0.2, cz, 0.1, 0.5, 0.5, 255, 251, 51);
	blocks[4] = new Block(sIF, cx-0.1, cy+0.2, cz+1.5, 0.1, 0.5, 0.5, 255, 255, 51);

	cyls[0] = new Cylinder(sIF, (double)cz-.25, (double)cz+0.75, (double)cy, (double)cx+0.5, 0.4, 32, 32, 32);
	cyls[1] = new Cylinder(sIF, (double)cz-.25, (double)cz+0.75, (double)cy, (double)cx+2.5, 0.4, 32, 32, 32);
	cyls[2] = new Cylinder(sIF, (double)cz+2.25, (double)cz+2.0, (double)cy, (double)cx+0.5, 0.4, 32, 32, 32);
	cyls[3] = new Cylinder(sIF, (double)cz+2.25, (double)cz+2.0, (double)cy, (double)cx+2.5, 0.4, 32, 32, 32);

}

Car::~Car()
{
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Car::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}

void Car::render()
{
	// 1. Save current and establish new current shader program
	// ...
	int savedPgm;
	glGetIntegerv(GL_CURRENT_PROGRAM, &savedPgm);
	glUseProgram(shaderIF->getShaderPgmID());

	// 2. Establish "mc_ec" and "ec_lds" matrices
	// ...
	cryph::Matrix4x4 mc_ec, ec_lds;
	getMatrices(mc_ec, ec_lds);
	float m[16];
	glUniformMatrix4fv(shaderIF->ppuLoc("mc_ec"), 1, false, mc_ec.extractColMajor(m));
	glUniformMatrix4fv(shaderIF->ppuLoc("ec_lds"), 1, false, mc_ec.extractColMajor(m));

	// Steps 3 and 4 may be performed in a "renderXxx" method as we have seen.
	// (If so, be sure to add the declaration of the method to the header file.)

	// 3. Set GLSL's "ka" and "kd" uniforms using this object's "ka" and "kd"
	//    instance variables
	// ...

	// 4. Establish any other attributes and make one or more calls to
	//    glDrawArrays and/or glDrawElements
	// ...
	for(int i = 0; i < 5; i++){
		blocks[i]->render();
	}

	for(int i = 0; i < 4; i++){
		cyls[i]->render();
	}
	// 5. Reestablish previous shader program
	// ...
	glUseProgram(savedPgm);
}

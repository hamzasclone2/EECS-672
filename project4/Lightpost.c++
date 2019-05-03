// Lightpost.c++

#include "Lightpost.h"

Lightpost::Lightpost(ShaderIF* sIF, float cx, float cy, float cz) : SceneElement(sIF)
{
	xmin = cx;
    xmax = cx+0.3;
    ymin = cy;
    ymax = cy+7.5;
    zmin = cz;
    zmax = cz+0.5;

	PhongMaterial black = PhongMaterial(
		0.05375, 0.05, 0.06625,
		0.18275, 0.17, 0.22525,
		0.332741, 0.328634, 0.346435,
		38.4, 1.0
	);

	PhongMaterial white = PhongMaterial(
		0.25, 0.20725, 0.20725,
		1, 0.829, 0.829,
		0.296648, 0.296648, 0.296648,
		0.088, 0.7
	);

	blocks[0] = new Block(sIF, cx, cy, cz, 1.0, 0.25, 1.0, black);
	blocks[1] = new Block(sIF, cx+0.3, cy, cz+0.25, 0.25, 7.5, 0.25, black);
	blocks[2] = new Block(sIF, cx, cy+7.5, cz-0.6, 1.0, 0.25, 2.0, black);
	blocks[3] = new Block(sIF, cx, cy+7.4, cz-0.4, 1.0, 0.1, 1.6, white);
}

Lightpost::~Lightpost()
{
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Lightpost::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}

void Lightpost::render()
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
	blocks[0]->render();
	blocks[1]->render();
	blocks[2]->render();
	blocks[3]->render();
	// 5. Reestablish previous shader program
	// ...
	glUseProgram(savedPgm);
}

// Tree.c++

#include "Tree.h"

Tree::Tree(ShaderIF* sIF, float cx, float cy, float cz) : SceneElement(sIF)
{
	xmin = cx;
    xmax = cx+3.0;
    ymin = cy;
    ymax = cy+0.5;
    zmin = cz;
    zmax = cz+2.0;

	PhongMaterial wood = PhongMaterial(
		0.2125, 0.1275, 0.054,
		0.714, 0.4284, 0.18144,
		0.393548, 0.271906, 0.166721,
		25.6, 1.0
	);

	PhongMaterial leaves = PhongMaterial(
		0.135, 0.2225, 0.1575,
		0.54, 0.89, 0.63,
		0.316228, 0.316228, 0.316228,
		12.8, 0.5
	);

	block = new Block(sIF, cx+0.5, cy, cz+0.5, 0.3, 3.0, 0.3, wood);
	cyls[0] = new Cylinder(sIF, cz, cz+1.0, cy+3.0, cx, 1.0, leaves, 1);
	cyls[1] = new Cylinder(sIF, cz+0.1, cz+1.1, cy+3.0, cx+1.0, 1.0, leaves, 1);
	cyls[2] = new Cylinder(sIF, cz-0.1, cz+0.9, cy+3.5, cx+0.5, 1.0, leaves, 1);
}

Tree::~Tree()
{
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Tree::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}

void Tree::render()
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
	block->render();
	cyls[0]->render();
	cyls[1]->render();
	cyls[2]->render();
	// 5. Reestablish previous shader program
	// ...
	glUseProgram(savedPgm);
}

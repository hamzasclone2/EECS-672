// Building.c++

#include "Building.h"

Building::Building(ShaderIF* sIF, float cx, float cy, float cz, PhongMaterial& p) : SceneElement(sIF)
{
    xmin = cx;
    xmax = cx+5.0;
    ymin = cy;
    ymax = cy+5.0;
    zmin = cz;
    zmax = cz+5.0;

    PhongMaterial door = PhongMaterial(
		0.329412, 0.223529, 0.027451,
		0.780392, 0.568627, 0.113725,
		0.992157, 0.941176, 0.807843,
		0.21794872, 1.0
	);

    PhongMaterial window = PhongMaterial(
		0.25, 0.20725, 0.20725,
		1, 0.829, 0.829,
		0.296648, 0.296648, 0.296648,
		0.088, 1.0
	);

    //main building
    blocks[0] = new Block(sIF, cx, cy, cz, 5.0, 5.0, 5.0, p);
    //first window
    blocks[1] = new Block(sIF, cx+0.5, cy+0.5, cz+5.0, 1.0, 1.0, 0.1, window);
    //door
    blocks[2] = new Block(sIF, cx+2.0, cy, cz+5.0, 1.0, 1.5, 0.1, door);
    //rest of the windows
    blocks[3] = new Block(sIF, cx+3.5, cy+0.5, cz+5.0, 1.0, 1.0, 0.1, window);
    blocks[4] = new Block(sIF, cx+0.5, cy+2.0, cz+5.0, 1.0, 1.0, 0.1, window);
    blocks[5] = new Block(sIF, cx+2.0, cy+2.0, cz+5.0, 1.0, 1.0, 0.1, window);
    blocks[6] = new Block(sIF, cx+3.5, cy+2.0, cz+5.0, 1.0, 1.0, 0.1, window);
    blocks[7] = new Block(sIF, cx+0.5, cy+3.5, cz+5.0, 1.0, 1.0, 0.1, window);
    blocks[8] = new Block(sIF, cx+2.0, cy+3.5, cz+5.0, 1.0, 1.0, 0.1, window);
    blocks[9] = new Block(sIF, cx+3.5, cy+3.5, cz+5.0, 1.0, 1.0, 0.1, window);

}

Building::~Building()
{
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Building::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}

void Building::renderBuilding(){
    for(int i = 0; i < 10; i++){
        blocks[i]->render();
    }
}

void Building::render()
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

    renderBuilding();

	// 5. Reestablish previous shader program
	// ...
	glUseProgram(savedPgm);
}

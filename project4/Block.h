// Block.h

#ifndef BLOCK_H
#define BLOCK_H

#include <GL/gl.h>

#include "SceneElement.h"

class Block : public SceneElement
{
public:
	Block(ShaderIF* sIF, float cx, float cy, float cz, // lower left corner
	      float lx, float ly, float lz, // lengths in 3 directions
		  PhongMaterial& p); //color

	Block(ShaderIF* sIF, float cx, float cy, float cz, // lower left corner
		float lx, float ly, float lz, // lengths in 3 directions
		PhongMaterial& p, int tex);
	virtual ~Block();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimits) const;
	bool handleCommand(unsigned char anASCIIChar, double ldsX, double ldsY);
	void render();
	void renderBlock();
private:
	GLuint vao[1];
	GLuint vbo[2];
	GLuint ebo[3];
	GLuint texID;
	int usingTexture;

	// "float" here to match the need to send float to VBO.
	float xmin, xmax, ymin, ymax, zmin, zmax;

	static GLuint indexList[3][4];

	void defineBlock();
};

#endif

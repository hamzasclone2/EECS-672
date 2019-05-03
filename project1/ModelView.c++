// ModelView.c++ - a basic combined Model and View for OpenGL
// Hamza Hameed
// KUID: 2796053

#include <iostream>
#include <cmath>

#include "ModelView.h"
#include "Controller.h"
#include "ShaderIF.h"

double ModelView::mcRegionOfInterest[6] = { -1.0, 1.0, -1.0, 1.0, -1.0, 1.0 };
bool ModelView::aspectRatioPreservationEnabled = false;

int numPoints = 100;
int ModelView::numInstances = 0;

ModelView::ModelView(ShaderIF* sIF, float f[], int s) : shaderIF(sIF), serialNumber(++numInstances)
{
	size = s;
	initModels(f);
}

ModelView::~ModelView()
{
	// TODO: delete the vertex array objects and buffers here
}

//Takes single line and performs function on it to get value that it should be
//drawn to. Then cycles through the colors and creates vao and vbo
void ModelView::initModels(float f[]){

	vec2 v[numPoints];
	float incr = 2.0 * M_PI / numPoints;
	float sum = 0;
	float t = -M_PI;
	int n = 1;
	bool isSin = true;
	for(int i = 0; i < numPoints; i++){
		for(int j = 0; j < size; j++){
			if(j == 0){
				sum += f[0] / sqrt(2);
			}else{
				if(isSin){
					sum += f[j] * sin(n * t);
					isSin = false;
				}else if(!isSin){
					sum += f[j] * cos(n * t);
					isSin = true;
					n++;
				}
			}
		}
		if(sum > ymax){
			ymax = sum;
		}else if(sum < ymin){
			ymin = sum;
		}
		v[i][0] = t;
		v[i][1] = sum;
		sum = 0;
		n = 1;
		t += incr;
		isSin = true;
	}

	if(serialNumber%7 == 1){
		lineColor[0] = 166/255.0;
		lineColor[1] = 206/255.0;
		lineColor[2] = 227/255.0;
	}else if(serialNumber%7 == 2){
		lineColor[0] = 31/255.0;
		lineColor[1] = 120/255.0;
		lineColor[2] = 180/255.0;
	}else if(serialNumber%7 == 3){
		lineColor[0] = 178/255.0;
		lineColor[1] = 223/255.0;
		lineColor[2] = 138/255.0;
	}else if(serialNumber%7 == 4){
		lineColor[0] = 51/255.0;
		lineColor[1] = 160/255.0;
		lineColor[2] = 44/255.0;
	}else if(serialNumber%7 == 5){
		lineColor[0] = 251/255.0;
		lineColor[1] = 154/255.0;
		lineColor[2] = 153/255.0;
	}else if(serialNumber%7 == 6){
		lineColor[0] = 227/255.0;
		lineColor[1] = 26/255.0;
		lineColor[2] = 28/255.0;
	}else {
		lineColor[0] = 253/255.0;
		lineColor[1] = 191/255.0;
		lineColor[2] = 111/255.0;
	}

	glGenVertexArrays(1, vao);
	glGenBuffers(1, vbo);

	// Initialize them
	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	// Allocate space for AND send data to GPU
	int numBytesInBuffer = numPoints * sizeof(vec2);
	glBufferData(GL_ARRAY_BUFFER, numBytesInBuffer, v, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));
}

void ModelView::compute2DScaleTrans(float* scaleTransF) // CLASS METHOD
{

	double xmin = mcRegionOfInterest[0];
	double xmax = mcRegionOfInterest[1];
	double ymin = mcRegionOfInterest[2];
	double ymax = mcRegionOfInterest[3];

	if (aspectRatioPreservationEnabled)
	{
		// preserve aspect ratio. Make "region of interest" wider or taller to
		// match the Controller's viewport aspect ratio.
		double vAR = Controller::getCurrentController()->getViewportAspectRatio();
		matchAspectRatio(xmin, xmax, ymin, ymax, vAR);
	}

    // We are only concerned with the xy extents for now, hence we will
    // ignore mcRegionOfInterest[4] and mcRegionOfInterest[5].
    // Map the overall limits to the -1..+1 range expected by the OpenGL engine:
	double scaleTrans[4];
	linearMap(xmin, xmax, -1.0, 1.0, scaleTrans[0], scaleTrans[1]);
	linearMap(ymin, ymax, -1.0, 1.0, scaleTrans[2], scaleTrans[3]);
	for (int i=0 ; i<4 ; i++)
		scaleTransF[i] = static_cast<float>(scaleTrans[i]);
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void ModelView::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = -M_PI; xyzLimits[1] = M_PI;
	xyzLimits[2] = ymin; xyzLimits[3] = ymax;
	xyzLimits[4] = -1.0; xyzLimits[5] = 1.0;
}

bool ModelView::handleCommand(unsigned char anASCIIChar, double ldsX, double ldsY)
{
	return true;
}

// linearMap determines the scale and translate parameters needed in
// order to map a value, f (fromMin <= f <= fromMax) to its corresponding
// value, t (toMin <= t <= toMax). Specifically: t = scale*f + trans.
void ModelView::linearMap(double fromMin, double fromMax, double toMin, double toMax,
					  double& scale, double& trans) // CLASS METHOD
{
	scale = (toMax - toMin) / (fromMax - fromMin);
	trans = toMin - scale*fromMin;
}

void ModelView::matchAspectRatio(double& xmin, double& xmax,
        double& ymin, double& ymax, double vAR)
{

	double wHeight = ymax - ymin;
	double wWidth = xmax - xmin;
	double wAR = wHeight / wWidth;
	if (wAR > vAR)
	{
		// make window wider
		wWidth = wHeight / vAR;
		double xmid = 0.5 * (xmin + xmax);
		xmin = xmid - 0.5*wWidth;
		xmax = xmid + 0.5*wWidth;
	}
	else
	{
		// make window taller
		wHeight = wWidth * vAR;
		double ymid = 0.5 * (ymin + ymax);
		ymin = ymid - 0.5*wHeight;
		ymax = ymid + 0.5*wHeight;
	}
}

void ModelView::render() const
{
	// save the current GLSL program in use
	GLint pgm;
	glGetIntegerv(GL_CURRENT_PROGRAM, &pgm);

	// draw the triangles using our vertex and fragment shaders
	glUseProgram(shaderIF->getShaderPgmID());

	float scaleTrans[4];
	compute2DScaleTrans(scaleTrans);
	glUniform4fv(shaderIF->ppuLoc("scaleTrans"), 1, scaleTrans);
	glUniform3fv(shaderIF->ppuLoc("color"), 1, lineColor);
	glBindVertexArray(vao[0]);
	glDrawArrays( GL_LINE_STRIP, 0, numPoints);
	glClearColor(1,1,1,1);

	// restore the previous program
	glUseProgram(pgm);
}

void ModelView::setMCRegionOfInterest(double xyz[6])
{
	for (int i=0 ; i<6 ; i++)
		mcRegionOfInterest[i] = xyz[i];
}

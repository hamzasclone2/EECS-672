#version 410 core

layout ( triangles ) in;

// Each incoming triangle is shrunk and then passed on
layout ( triangle_strip, max_vertices = 12 ) out;

// Since "triangles" are coming in, this shader will be called once
// per triangle and hence there will be data in pva_in[i], 0<=i<= 2.

in PVA
{
	vec3 ecPosition;
	vec3 ecUnitNormal;
	vec2 texCoords; // (s,t)
} pvaIn[];

out PVA
{
	vec3 ecPosition;
	vec3 ecUnitNormal;
	vec2 texCoords; // (s,t)
} pvaOut; // We write one vertex at a time, hence pva_out is NOT an array.

uniform int shrink = 0;
uniform float shrinkFactor = 0.75;

void outputAttributesFor(int i)
{
	pvaOut.ecPosition = pvaIn[i].ecPosition;
	pvaOut.ecUnitNormal = pvaIn[i].ecUnitNormal;
	pvaOut.texCoords = pvaIn[i].texCoords;
}

void shrinkTriangle(vec4 v0, vec4 v1, vec4 v2, float factor)
{
	vec4 centerOfGravity = (v0 + v1 + v2) / 3.0;
	gl_Position = centerOfGravity + factor * (v0 - centerOfGravity);
	outputAttributesFor(0);
	EmitVertex();
	gl_Position = centerOfGravity + factor * (v1 - centerOfGravity);
	outputAttributesFor(1);
	EmitVertex();
	gl_Position = centerOfGravity + factor * (v2 - centerOfGravity);
	outputAttributesFor(2);
	EmitVertex();

	EndPrimitive();
}

void main()
{
	if(shrink == 1){
		shrinkTriangle(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_in[2].gl_Position,
			shrinkFactor);
	}else{
		shrinkTriangle(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_in[2].gl_Position,
			1.0);
	}
}

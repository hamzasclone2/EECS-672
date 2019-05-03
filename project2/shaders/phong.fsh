#version 410 core

// phong.fsh - a fragment shader that implements a Phong Lighting model.

in PVA
{
	vec3 ecPosition;
	vec3 ecUnitNormal;
} pvaIn;

// For lighing model:
uniform mat4 ec_lds; // so projection type and hence vHat can be determined

// Phong material properties (RGB reflectances);
uniform vec3 ka = vec3(0.8, 0.0, 0.0); // default: darkish red
uniform vec3 kd = vec3(0.8, 0.0, 0.0); // default: darkish red
// Lighting environment
// RGB strength of assumed ambient light:
uniform vec3 La = vec3(0.15, 0.15, 0.15);

// output color from the lighting model:
out vec4 fragmentColor;

vec4 evaluateLightingModel()
{
	// THIS IS JUST A PLACEHOLDER FOR A LIGHTING MODEL.
	// It only currently implements simple Lambert shading.

	// NOTE: We assume a single directional light source defined in EC (liHat).
	//
	// In project 3, several aspects of this will be generalized.

	vec3 vhat;
	if(ec_lds[3][3] == 0){
		vhat = normalize(-pvaIn.ecPosition);
	}else{
		vhat = normalize(vec3(-ec_lds[2][0]/ec_lds[0][0], -ec_lds[2][1]/ec_lds[1][1], 1.0));
	}

	vec3 liHat = vec3(0.0, 0.0, 1.0); // directional light in EC at eye (a flashlight)
	vec3 I = ka*La;
	vec3 normal;
	if(dot(vhat, pvaIn.ecUnitNormal) < 0){
		normal = -pvaIn.ecUnitNormal;
	}else{
		normal = pvaIn.ecUnitNormal;
	}

	I = I + kd*(dot(liHat, normal));

	// Use liHat, the uniforms, and the incoming PVA values to compute
	// the simplified Phong model we are using for project 2.

	// For now:
	return vec4(I, 1.0);
}

void main ()
{
	fragmentColor = evaluateLightingModel();
}

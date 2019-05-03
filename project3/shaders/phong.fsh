#version 410 core

// phong.fsh - a fragment shader that implements a Phong Lighting model.

in PVA
{
	vec3 ecPosition;
	vec3 ecUnitNormal;
} pvaIn;

const int MAX_NUM_LIGHTS = 12;

// For lighing model:
uniform mat4 ec_lds; // so projection type and hence vHat can be determined

// Phong material properties (RGB reflectances);
uniform vec3 ka = vec3(0.8, 0.0, 0.0); // default: darkish red
uniform vec3 kd = vec3(0.8, 0.0, 0.0); // default: darkish red
uniform vec3 ks = vec3(0.8, 0.0, 0.0);

// Lighting environment
// RGB strength of assumed A light:
uniform vec3 La = vec3(0.15, 0.15, 0.15);
uniform vec3 lightStrength[MAX_NUM_LIGHTS];
uniform vec4 p_ecLightPos[MAX_NUM_LIGHTS];
uniform float m;

// output color from the lighting model:
out vec4 fragmentColor;

float atten(vec3 i, vec3 Q){
	float d = distance(i, Q);
	return 5.0/((0.2*d)+(0.2*pow(d,2)));
}

vec4 evaluateLightingModel()
{
	vec3 vHat;
	if(ec_lds[3][3] == 0){
		vHat = normalize(-pvaIn.ecPosition);
	}else{
		vHat = normalize(vec3(-ec_lds[2][0]/ec_lds[0][0], -ec_lds[2][1]/ec_lds[1][1], 1.0));
	}

	vec3 normal;
	if(dot(vHat, pvaIn.ecUnitNormal) < 0){
		normal = -pvaIn.ecUnitNormal;
	}else{
		normal = pvaIn.ecUnitNormal;
	}

	vec3 I = vec3(0.0, 0.0,0.0);

	float fiQ;
	vec3 liHat;
	vec3 riHat;

	vec3 A = ka * La;
	vec3 B = vec3(0.0, 0.0, 0.0);
	vec3 C = vec3(0.0, 0.0, 0.0);

	for(int i = 0; i < MAX_NUM_LIGHTS; i++) {

		if(p_ecLightPos[i].w == 0) {
			liHat = normalize(p_ecLightPos[i].xyz);
		} else {
			liHat = normalize(p_ecLightPos[i].xyz - pvaIn.ecPosition);
			fiQ = atten(p_ecLightPos[i].xyz, pvaIn.ecPosition);
		}

		if(dot(liHat, normal) > 0) {
			B += fiQ * lightStrength[i] * kd * dot(liHat, normal);
		}
		riHat = 2 * dot(liHat, normal) * normal - liHat;

		if(dot(riHat, vHat) > 0)
		{
			C += fiQ * lightStrength[i] * ks * pow(dot(riHat,vHat), m);
		}
	}

	I.r = A[0] + B[0] + C[0];
	I.g = A[1] + B[1] + C[1];
	I.b = A[2] + B[2] + C[2];

	if(I.r > 1 || I.g > 1 || I.b > 1){
		float cap = I.r;
		if(I.g > cap){
			cap = I.g;
		}

		if(I.b > cap){
			cap = I.b;
		}
		I = I/cap;
	}

	return vec4(I, 1.0);
}

void main ()
{
	fragmentColor = evaluateLightingModel();
}

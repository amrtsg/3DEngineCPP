#include "Perlin.h"


Perlin::Perlin(int w, int h) {
	width = w;
	height = h;

}

/// TODO1: Implement the linear interpolation (weightage-5%)

float Perlin::lerp(float x, float y, float t) {
	/// TODO: Implement linear interpolation between x and y
	float result;
	result = x + (t * (y - x));
	return result; //to be changed
}


/// TODO2: Implement the fade function (try both cubic as well as quintic polynomials and generatee the corresponding noise textures) (weightage-5%)

float Perlin::fade(float t) {
	/// TODO: Implement the quintic function (optimized)      
	float result;
	result = t * t * t * (t * (t * 6 - 15) + 10); //6t^5-15t^4+10t^3
	return result;//to be changed	
}

//function returns one of the eight gradients
glm::vec2 Gradient(int index) {
	//index is the value from the permutation table
	int h = index & 7;
	if (h == 0)
		return  glm::vec2(1.0, 0.0);
	else if (h == 1)
		return glm::vec2(0.707, 0.707);
	else if (h == 2)
		return  glm::vec2(0.0, 1.0);
	else if (h == 3)
		return glm::vec2(-0.707, 0.707);
	else if (h == 4)
		return  glm::vec2(-1.0, 0.0);
	else if (h == 5)
		return glm::vec2(-0.707, -0.707);
	else if (h == 6)
		return glm::vec2(0.0, -1.0);
	else
		return glm::vec2(0.707, -0.707);

}

//TODO3: Complete the following noise generation function. THe function takes three coordinates of the sample point and retirns the noise vlaue at that point. 
//Since this is 2D Noise, we keep z=0 for all the points and use x and y coordinates to generate the noise value.

float Perlin::noise(float xCoord, float yCoord, float zCoord) {

	// TODO: Unit cube vertex coordinates surrounding the sample point. In this example find the unit square vertex coordinates in X and Y coords. (Weightage-10%)
	int X0 = int(floor(xCoord));
	int X1 = X0 + 1;
	int Y0 = int(floor(yCoord));
	int Y1 = Y0 + 1;
	int Z0 = 0, Z1 = 0;

	// Determine sample point position within unit cube (unit square in our case) (Weightage-10%)
	float pointX0 = xCoord - X0;
	float pointX1 = pointX0 - 1.0f;
	float pointY0 = yCoord - Y0;
	float pointY1 = pointY0 - 1.0f;
	float pointZ0 = 0, pointZ1 = 0;

	//Construct distance vectors from each corner to the sample point (Weightage-10%)	
	glm::vec2 V00(pointX0, pointY0);
	glm::vec2 V01(pointX0, pointY1);
	glm::vec2 V10(pointX1, pointY0);
	glm::vec2 V11(pointX1, pointY1);

	//Fetch the gradients at corners (Weightage-10%)
	float index00 = P[(P[X0 & 255] + Y0 & 255) & 255];
	float index10 = P[(P[X1 & 255] + Y0 & 255) & 255];
	float index01 = P[(P[X0 & 255] + Y1 & 255) & 255];
	float index11 = P[(P[X1 & 255] + Y1 & 255) & 255];

	//TODO: Get scalars at corners HINT: take the dot product of gradient and the distance vectors. (Weightage-10%)
	float dotX0Y0Z0, dotX0Y1Z0, dotX1Y0Z0, dotX1Y1Z0;

	dotX0Y0Z0 = glm::dot(V00, Gradient(index00));
	dotX0Y1Z0 = glm::dot(V01, Gradient(index01));
	dotX1Y0Z0 = glm::dot(V10, Gradient(index10));
	dotX1Y1Z0 = glm::dot(V11, Gradient(index11));

	//TODO: Interpolate along X (Weightage-5%)
	float st = lerp(dotX0Y0Z0, dotX1Y0Z0, fade(pointX0));

	//TODO: Interpolate along Y (Weightage-5%)
	float uv = lerp(dotX0Y1Z0, dotX1Y1Z0, fade(pointX0));

	float result = lerp(st, uv, fade(pointY0));

	// Return the result
	return result;

}

float Perlin::FBM(glm::vec3 point, float H, float l, int octaves) { 
	float value = 0.0; for (int i = 0; i < octaves; i++) { 
		value += noise(point.x, point.y, point.z) * pow(l, -H * i); 
		point.x *= l; 
		point.y *= l;
		point.z *= l;
	}
	return value; 
}

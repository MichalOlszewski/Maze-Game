
#ifndef GRASS_H
#define GRASS_H


int grassVertexCount = 6;

float grassVerts[] = {
	-1.0f,0.0f,1.0f,1.0f, //A
	 1.0f,0.0f,1.0f,1.0f, //B
	 1.0f,0.0f,-1.0f,1.0f, //C

	 -1.0f,0.0f,1.0f,1.0f, //A
	 -1.0f,0.0f,-1.0f,1.0f, //D
	 1.0f,0.0f,-1.0f,1.0f, //C
};

float grassNormals[] = {
	0.0f,1.0f, 0.0f,0.0f, //A
	0.0f,1.0f, 0.0f,0.0f, //B
	0.0f,1.0f, 0.0f,0.0f, //C

	0.0f,1.0f, 0.0f,0.0f, //A
	0.0f,1.0f, 0.0f,0.0f, //D
	0.0f,1.0f, 0.0f,0.0f, //C
};


float grassTexCoords[] = {
	0.0f,1.0f,  1.0f,1.0f,  1.0f,0.0f,
	0.0f,1.0f,  0.0f,0.0f,  1.0f,0.0f
};

#endif

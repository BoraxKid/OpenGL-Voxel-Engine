#ifndef CHUNK_H_
#define CHUNK_H_

#define BLOCK_SIZE 1.0f
#define CHUNK_X 16
#define CHUNK_Y 16
#define CHUNK_Z 16
#define CHUNK_SIZE (CHUNK_X * CHUNK_Y * CHUNK_Z)

#include <math.h>
#include <time.h>
#include <iostream>
#include <glm/glm.hpp>
#include "../Dependencies/glew/glew.h"
#include "../System/Vector.h"

typedef glm::tvec4<GLfloat> float4;

typedef struct s_surround
{
	void *north;
	void *east;
	void *south;
	void *west;
	void *above;
	void *below;
} t_surround;

class Chunk
{
public:
	Chunk();
	Chunk(int x, int y, int z);
	~Chunk();
	void generate();
	void addBlockToVertices(vector3i blockColor);
	void render(GLint attributeCoord);

private:
	float4 _vertices[CHUNK_SIZE * 36];
	GLuint _vboVertices;
	vector3i _it;
	t_surround *_surround;
	vector3i _chunckPos;
	int _vertNumb;
	int _vertColor;
	int _elemNumb;
};

#endif // !CHUNK_H_

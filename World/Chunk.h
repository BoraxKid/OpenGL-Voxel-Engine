#ifndef CHUNK_H_
#define CHUNK_H_

#define BLOCK_SIZE 1
#define CHUNK_X 100
#define CHUNK_Y 100
#define CHUNK_Z 100
#define CHUNK_SIZE (CHUNK_X * CHUNK_Y * CHUNK_Z)

#include <math.h>
#include <time.h>
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include <noise\noise.h>
#include "../Noise/NoiseUtils.h"
#include "../Dependencies/glew/glew.h"
#include "../System/Vector.h"

typedef glm::tvec3<GLint> int3;

typedef struct s_surround
{
	void *north;
	void *east;
	void *south;
	void *west;
	void *above;
	void *below;
} Surround;

enum Color
{
	NONE, WATER, GRASS, STONE, SAND, DIRT, SNOW
};

using namespace noise;

class Chunk
{
public:
	Chunk();
	Chunk(int x, int y, int z);
	~Chunk();
	Color getEnumColor(float height);
	vector3i getRGBColor(Color color);
	void generateChunk();
	void generateVertices();
	void addBlockToVertices(vector3i blockColor);
	void render(GLint attributeCoord, GLint attributeColor);

private:
	int3 _vertices[CHUNK_SIZE * 36];
	int3 _colors[CHUNK_SIZE * 36];
	Color _blocks[CHUNK_X][CHUNK_Y][CHUNK_Z];
	GLuint _vboVertices;
	GLuint _vboColors;
	vector3i _it;
	Surround *_surround;
	vector3i _chunckPos;
	int _vertNumb;
	int _vertColor;
	int _elemNumb;
};

#endif // !CHUNK_H_

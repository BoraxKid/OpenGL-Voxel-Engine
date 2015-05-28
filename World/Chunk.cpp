#include "Chunk.h"

Chunk::Chunk()
{
	this->_chunckPos = vector3i(0, 0, 0);
	this->_surround = new t_surround;
	this->_surround->north = nullptr;
	this->_surround->east = nullptr;
	this->_surround->south = nullptr;
	this->_surround->west = nullptr;
	this->_surround->above = nullptr;
	this->_surround->below = nullptr;
	this->generate();
}

Chunk::Chunk(int x, int y, int z)
{
	this->_chunckPos = vector3i(x, y, z);
	this->_surround = new t_surround;
	this->_surround->north = nullptr;
	this->_surround->east = nullptr;
	this->_surround->south = nullptr;
	this->_surround->west = nullptr;
	this->_surround->above = nullptr;
	this->_surround->below = nullptr;
	this->generate();
}

Chunk::~Chunk()
{
	delete (this->_surround);
}

void Chunk::generate()
{
	int red;
	int green;
	int blue;

	srand(time(NULL));
	this->_vertNumb = -1;
	this->_vertColor = -1;
	this->_elemNumb = -1;
	this->_it.z = 0;
	while (this->_it.z < CHUNK_Z)
	{
		this->_it.y = 0;
		while (this->_it.y < CHUNK_Y)
		{
			this->_it.x = 0;
			while (this->_it.x < CHUNK_X)
			{
				this->addBlockToVertices(vector3i(std::rand() % 256, std::rand() % 256, std::rand() % 256));
				++this->_it.x;
			}
			++this->_it.y;
		}
		++this->_it.z;
	}
	glGenBuffers(1, &this->_vboVertices);
	glBindBuffer(GL_ARRAY_BUFFER, this->_vboVertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->_vertices), this->_vertices, GL_STATIC_DRAW);
}

void Chunk::addBlockToVertices(vector3i blockColor)
{
	int colorInt;
	float color;

	colorInt = ((blockColor.x & 0x0ff) << 16) | ((blockColor.y & 0x0ff) << 8) | (blockColor.z & 0x0ff);
	color = colorInt;
	// negative x
	this->_vertices[++this->_vertNumb] = float4(this->_it.x, this->_it.y, this->_it.z, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x, this->_it.y, this->_it.z + BLOCK_SIZE, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x, this->_it.y + BLOCK_SIZE, this->_it.z, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x, this->_it.y + BLOCK_SIZE, this->_it.z, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x, this->_it.y, this->_it.z + BLOCK_SIZE, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x, this->_it.y + BLOCK_SIZE, this->_it.z + BLOCK_SIZE, color);
	// positive x
	this->_vertices[++this->_vertNumb] = float4(this->_it.x + BLOCK_SIZE, this->_it.y, this->_it.z, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x + BLOCK_SIZE, this->_it.y + BLOCK_SIZE, this->_it.z, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x + BLOCK_SIZE, this->_it.y, this->_it.z + BLOCK_SIZE, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x + BLOCK_SIZE, this->_it.y + BLOCK_SIZE, this->_it.z, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x + BLOCK_SIZE, this->_it.y + BLOCK_SIZE, this->_it.z + BLOCK_SIZE, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x + BLOCK_SIZE, this->_it.y, this->_it.z + BLOCK_SIZE, color);
	// negative y
	this->_vertices[++this->_vertNumb] = float4(this->_it.x, this->_it.y, this->_it.z, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x + BLOCK_SIZE, this->_it.y, this->_it.z, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x, this->_it.y, this->_it.z + BLOCK_SIZE, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x + BLOCK_SIZE, this->_it.y, this->_it.z, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x + BLOCK_SIZE, this->_it.y, this->_it.z + BLOCK_SIZE, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x, this->_it.y, this->_it.z + BLOCK_SIZE, color);
	// positive y
	this->_vertices[++this->_vertNumb] = float4(this->_it.x, this->_it.y + BLOCK_SIZE, this->_it.z, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x, this->_it.y + BLOCK_SIZE, this->_it.z + BLOCK_SIZE, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x + BLOCK_SIZE, this->_it.y + BLOCK_SIZE, this->_it.z, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x + BLOCK_SIZE, this->_it.y + BLOCK_SIZE, this->_it.z, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x, this->_it.y + BLOCK_SIZE, this->_it.z + BLOCK_SIZE, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x + BLOCK_SIZE, this->_it.y + BLOCK_SIZE, this->_it.z + BLOCK_SIZE, color);
	// negative z
	this->_vertices[++this->_vertNumb] = float4(this->_it.x, this->_it.y, this->_it.z, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x, this->_it.y + BLOCK_SIZE, this->_it.z, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x + BLOCK_SIZE, this->_it.y, this->_it.z, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x, this->_it.y + BLOCK_SIZE, this->_it.z, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x + BLOCK_SIZE, this->_it.y + BLOCK_SIZE, this->_it.z, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x + BLOCK_SIZE, this->_it.y, this->_it.z, color);
	// positive z
	this->_vertices[++this->_vertNumb] = float4(this->_it.x, this->_it.y, this->_it.z + BLOCK_SIZE, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x + BLOCK_SIZE, this->_it.y, this->_it.z + BLOCK_SIZE, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x, this->_it.y + BLOCK_SIZE, this->_it.z + BLOCK_SIZE, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x, this->_it.y + BLOCK_SIZE, this->_it.z + BLOCK_SIZE, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x + BLOCK_SIZE, this->_it.y, this->_it.z + BLOCK_SIZE, color);
	this->_vertices[++this->_vertNumb] = float4(this->_it.x + BLOCK_SIZE, this->_it.y + BLOCK_SIZE, this->_it.z + BLOCK_SIZE, color);
}

void Chunk::render(GLint attributeCoord)
{
	if (!this->_vertNumb)
		return;
	glEnableVertexAttribArray(attributeCoord);
	glBindBuffer(GL_ARRAY_BUFFER, this->_vboVertices);
	glVertexAttribPointer(attributeCoord, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, this->_vertNumb + 1);
	glDisableVertexAttribArray(attributeCoord);
}
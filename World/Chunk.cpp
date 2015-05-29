#include "Chunk.h"

Chunk::Chunk()
{
	this->_chunckPos = vector3i(0, 0, 0);
	this->_surround = new Surround;
	this->_surround->north = nullptr;
	this->_surround->east = nullptr;
	this->_surround->south = nullptr;
	this->_surround->west = nullptr;
	this->_surround->above = nullptr;
	this->_surround->below = nullptr;
	this->generateChunk();
	this->generateVertices();
}

Chunk::Chunk(int x, int y, int z)
{
	this->_chunckPos = vector3i(x, y, z);
	this->_surround = new Surround;
	this->_surround->north = nullptr;
	this->_surround->east = nullptr;
	this->_surround->south = nullptr;
	this->_surround->west = nullptr;
	this->_surround->above = nullptr;
	this->_surround->below = nullptr;
	this->generateChunk();
	this->generateVertices();
}

Chunk::~Chunk()
{
	delete (this->_surround);
}

Color Chunk::getEnumColor(float height)
{
	if (height > 0.0000 && height <= 0.0625)
		return (SAND);
	if (height > 0.0625 && height <= 0.1250)
		return (GRASS);
	if (height > 0.1250 && height <= 0.3750)
		return (DIRT);
	if (height > 0.3750 && height <= 0.7500)
		return (STONE);
	if (height > 0.7500)
		return (SNOW);
	return (WATER);
}

vector3i Chunk::getRGBColor(Color color)
{
	if (color == SAND)
		return (vector3i(240, 240, 64));
	if (color == GRASS)
		return (vector3i(32, 160, 0));
	if (color == DIRT)
		return (vector3i(224, 224, 0));
	if (color == STONE)
		return (vector3i(128, 128, 128));
	if (color == SNOW)
		return (vector3i(255, 255, 255));
	if (color == WATER)
		return (vector3i(0, 0, 255));
	return (vector3i(255, 0, 0));

}

void Chunk::generateChunk()
{
	noise::module::Perlin perlin;
	noise::utils::NoiseMap heightMap;
	noise::utils::NoiseMapBuilderPlane heightMapBuilder;
	heightMapBuilder.SetSourceModule(perlin);
	heightMapBuilder.SetDestNoiseMap(heightMap);
	heightMapBuilder.SetDestSize(256, 256);
	heightMapBuilder.SetBounds(2.0, 6.0, 1.0, 5.0);
	heightMapBuilder.Build();
	noise::utils::RendererImage renderer;
	noise::utils::Image image;
	renderer.SetSourceNoiseMap(heightMap);
	renderer.SetDestImage(image);
	renderer.ClearGradient();
	renderer.AddGradientPoint(-1.0000, utils::Color(0, 0, 128, 255)); // deeps
	renderer.AddGradientPoint(-0.2500, utils::Color(0, 0, 255, 255)); // shallow
	renderer.AddGradientPoint(0.0000, utils::Color(0, 128, 255, 255)); // shore
	renderer.AddGradientPoint(0.0625, utils::Color(240, 240, 64, 255)); // sand
	renderer.AddGradientPoint(0.1250, utils::Color(32, 160, 0, 255)); // grass
	renderer.AddGradientPoint(0.3750, utils::Color(224, 224, 0, 255)); // dirt
	renderer.AddGradientPoint(0.7500, utils::Color(128, 128, 128, 255)); // rock
	renderer.AddGradientPoint(1.0000, utils::Color(255, 255, 255, 255)); // snow
	renderer.EnableLight();
	renderer.SetLightContrast(3.0); // Triple the contrast
	renderer.SetLightBrightness(2.0); // Double the brightness
	renderer.Render();
	noise::utils::WriterBMP writer;
	writer.SetSourceImage(image);
	writer.SetDestFilename("tutorial.bmp");
	writer.WriteDestFile();

	vector3i i;
	float height;
	int blockHeight;
	int tmp;
	int index;
	i.x = 0;
	while (i.x < CHUNK_X)
	{
		i.z = 0;
		while (i.z < CHUNK_Z)
		{
			height = heightMap.GetValue(i.x, i.z);
			blockHeight = (int)(height * (float)CHUNK_Y);
			i.y = 0;
			while (i.y < blockHeight)
			{
				this->_blocks[i.x][i.z][i.y] = this->getEnumColor(height);
				++i.y;
			}
			if (i.y == 0)
			{
				this->_blocks[i.x][i.z][i.y++] = this->getEnumColor(height);
			}
			while (i.y < CHUNK_Y)
			{
				this->_blocks[i.x][i.z][i.y] = NONE;
				++i.y;
			}
			++i.z;
		}
		++i.x;
	}
}

void Chunk::generateVertices()
{
	GLint index;
	Color color;
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
				color = this->_blocks[this->_it.x][this->_it.z][this->_it.y];
				if (color != NONE)
					this->addBlockToVertices(getRGBColor(color));
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
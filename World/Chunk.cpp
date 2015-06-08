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
		return (vector3i(147, 105, 46));
	if (color == DIRT)
		return (vector3i(32, 160, 0));
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
	/*
	noise::utils::WriterBMP writer;
	writer.SetSourceImage(image);
	writer.SetDestFilename("tutorial.bmp");
	writer.WriteDestFile();
	*/

	vector3i i;
	float height;
	int blockHeight;
	i.x = 0;
	while (i.x < CHUNK_X)
	{
		i.y = 0;
		while (i.y < CHUNK_Y)
		{
			height = heightMap.GetValue(i.x, i.y);
			blockHeight = (int)(height * (float)CHUNK_Z / 2);
			i.z = 0;
			while (i.z < blockHeight)
			{
				this->_blocks[i.x][i.y][i.z] = this->getEnumColor(height);
				++i.z;
			}
			if (i.z == 0)
			{
				this->_blocks[i.x][i.y][i.z++] = this->getEnumColor(height);
			}
			while (i.z < CHUNK_Z)
			{
				this->_blocks[i.x][i.y][i.z] = NONE;
				++i.z;
			}
			++i.y;
		}
		++i.x;
	}
}

void Chunk::generateVertices()
{
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
				color = this->_blocks[this->_it.x][this->_it.y][this->_it.z];
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
	glGenBuffers(1, &this->_vboColors);
	glBindBuffer(GL_ARRAY_BUFFER, this->_vboColors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->_colors), this->_colors, GL_STATIC_DRAW);
}

void Chunk::addBlockToVertices(vector3i blockColor)
{/*
	int colorInt;
	int color;

	colorInt = ((blockColor.x) << 16) | ((blockColor.y) << 8) | (blockColor.z);
	color = colorInt;*/
	int value = 1;
	// negative x
	vector3i tmp;

	tmp = blockColor;
	if (!(this->_it.x > 0 && this->_blocks[this->_it.x - 1][this->_it.y][this->_it.z] != NONE))
	{
		blockColor /= 2;
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value), (this->_it.y * value), (this->_it.z * value));
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value), (this->_it.y * value), (this->_it.z * value) + BLOCK_SIZE);
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value), (this->_it.y * value) + BLOCK_SIZE, (this->_it.z * value));
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value), (this->_it.y * value) + BLOCK_SIZE, (this->_it.z * value));
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value), (this->_it.y * value), (this->_it.z * value) + BLOCK_SIZE);
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value), (this->_it.y * value) + BLOCK_SIZE, (this->_it.z * value) + BLOCK_SIZE);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
	}
	// positive x
	blockColor = tmp;
	if (!(this->_it.x < CHUNK_X - 1 && this->_blocks[this->_it.x + 1][this->_it.y][this->_it.z] != NONE))
	{
		blockColor /= 2;
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value) + BLOCK_SIZE, (this->_it.y * value), (this->_it.z * value));
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value) + BLOCK_SIZE, (this->_it.y * value) + BLOCK_SIZE, (this->_it.z * value));
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value) + BLOCK_SIZE, (this->_it.y * value), (this->_it.z * value) + BLOCK_SIZE);
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value) + BLOCK_SIZE, (this->_it.y * value) + BLOCK_SIZE, (this->_it.z * value));
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value) + BLOCK_SIZE, (this->_it.y * value) + BLOCK_SIZE, (this->_it.z * value) + BLOCK_SIZE);
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value) + BLOCK_SIZE, (this->_it.y * value), (this->_it.z * value) + BLOCK_SIZE);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
	}
	// negative y
	blockColor = tmp;
	if (!(this->_it.y > 0 && this->_blocks[this->_it.x][this->_it.y - 1][this->_it.z] != NONE))
	{
		blockColor /= 2;
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value), (this->_it.y * value), (this->_it.z * value));
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value) + BLOCK_SIZE, (this->_it.y * value), (this->_it.z * value));
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value), (this->_it.y * value), (this->_it.z * value) + BLOCK_SIZE);
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value) + BLOCK_SIZE, (this->_it.y * value), (this->_it.z * value));
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value) + BLOCK_SIZE, (this->_it.y * value), (this->_it.z * value) + BLOCK_SIZE);
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value), (this->_it.y * value), (this->_it.z * value) + BLOCK_SIZE);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
	}
	// positive y
	blockColor = tmp;
	if (!(this->_it.y < CHUNK_Y - 1 && this->_blocks[this->_it.x][this->_it.y + 1][this->_it.z] != NONE))
	{
		blockColor /= 2;
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value), (this->_it.y * value) + BLOCK_SIZE, (this->_it.z * value));
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value), (this->_it.y * value) + BLOCK_SIZE, (this->_it.z * value) + BLOCK_SIZE);
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value) + BLOCK_SIZE, (this->_it.y * value) + BLOCK_SIZE, (this->_it.z * value));
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value) + BLOCK_SIZE, (this->_it.y * value) + BLOCK_SIZE, (this->_it.z * value));
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value), (this->_it.y * value) + BLOCK_SIZE, (this->_it.z * value) + BLOCK_SIZE);
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value) + BLOCK_SIZE, (this->_it.y * value) + BLOCK_SIZE, (this->_it.z * value) + BLOCK_SIZE);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
	}
	// negative z
	blockColor = tmp;
	if (!(this->_it.z > 0 && this->_blocks[this->_it.x][this->_it.y][this->_it.z - 1] != NONE))
	{
		blockColor /= 2;
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value), (this->_it.y * value), (this->_it.z * value));
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value), (this->_it.y * value) + BLOCK_SIZE, (this->_it.z * value));
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value) + BLOCK_SIZE, (this->_it.y * value), (this->_it.z * value));
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value), (this->_it.y * value) + BLOCK_SIZE, (this->_it.z * value));
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value) + BLOCK_SIZE, (this->_it.y * value) + BLOCK_SIZE, (this->_it.z * value));
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value) + BLOCK_SIZE, (this->_it.y * value), (this->_it.z * value));
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
	}
	// positive z
	blockColor = tmp;
	if (!(this->_it.z < CHUNK_Z - 1 && this->_blocks[this->_it.x][this->_it.y][this->_it.z + 1] != NONE))
	{
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value), (this->_it.y * value), (this->_it.z * value) + BLOCK_SIZE);
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value) + BLOCK_SIZE, (this->_it.y * value), (this->_it.z * value) + BLOCK_SIZE);
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value), (this->_it.y * value) + BLOCK_SIZE, (this->_it.z * value) + BLOCK_SIZE);
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value), (this->_it.y * value) + BLOCK_SIZE, (this->_it.z * value) + BLOCK_SIZE);
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value) + BLOCK_SIZE, (this->_it.y * value), (this->_it.z * value) + BLOCK_SIZE);
		this->_vertices[++this->_vertNumb] = int3((this->_it.x * value) + BLOCK_SIZE, (this->_it.y * value) + BLOCK_SIZE, (this->_it.z * value) + BLOCK_SIZE);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
		this->_colors[++this->_vertColor] = int3(blockColor.x, blockColor.y, blockColor.z);
	}
}

void Chunk::render(GLint attributeCoord, GLint attributeColor)
{
	if (!this->_vertNumb)
		return;
	glEnableVertexAttribArray(attributeCoord);
	glEnableVertexAttribArray(attributeColor);
	glBindBuffer(GL_ARRAY_BUFFER, this->_vboVertices);
	glVertexAttribPointer(attributeCoord, 3, GL_INT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, this->_vboColors);
	glVertexAttribPointer(attributeColor, 3, GL_INT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, this->_vertNumb + 1);
	glDisableVertexAttribArray(attributeCoord);
	glDisableVertexAttribArray(attributeColor);
}
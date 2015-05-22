#include "Shader.h"

GLuint getShader(std::string filename, GLenum type)
{
	std::fstream shaderFile(filename, std::ios::in);
	std::string shader;
	std::stringstream buffer;
	GLuint shaderID;
	const char *tmp[1];
	GLint status;

	if (shaderFile.is_open())
	{
		buffer << shaderFile.rdbuf();
		shader = buffer.str();
	}
	if ((shaderID = glCreateShader(type)) == 0)
	{
		std::stringstream error;
		error << "Error creating the " << ((type == GL_VERTEX_SHADER) ? "vertex" : ((type == GL_FRAGMENT_SHADER) ? "fragment" : "unknown")) << " shader";
		printError(error.str());
		return (0);
	}
	tmp[0] = shader.c_str();
	glShaderSource(shaderID, 1, tmp, NULL);
	glCompileShader(shaderID);
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		std::stringstream error;
		error << "Error getting the " << ((type == GL_VERTEX_SHADER) ? "vertex" : ((type == GL_FRAGMENT_SHADER) ? "fragment" : "unknown")) << " shader compilation status";
		printError(error.str());
		glDeleteShader(shaderID);
		return (0);
	}
}

GLuint getProgram(std::string vertexFilename, std::string fragmentFilename)
{
	GLuint program = glCreateProgram();
	GLuint shader;
	GLint status;

	if ((shader = getShader(vertexFilename, GL_VERTEX_SHADER)) == 0)
		return (0);
	glAttachShader(program, shader);
	if ((shader = getShader(fragmentFilename, GL_FRAGMENT_SHADER)) == 0)
		return (0);
	glAttachShader(program, shader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		std::stringstream error;
		error << "Error linking program";
		printError(error.str());
		return (0);
	}
	return (program);
}
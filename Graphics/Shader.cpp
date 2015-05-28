#include "Shader.h"

void printLog(GLuint object)
{
	GLint logLength = 0;
	char *log;

	if (glIsShader(object))
		glGetShaderiv(object, GL_INFO_LOG_LENGTH, &logLength);
	else if (glIsProgram(object))
		glGetProgramiv(object, GL_INFO_LOG_LENGTH, &logLength);
	else
	{
		std::cerr << "Not a shader nor a program" << std::endl;
		return;
	}
	log = (char *)malloc(logLength);
	if (glIsShader(object))
		glGetShaderInfoLog(object, logLength, NULL, log);
	else if (glIsProgram(object))
		glGetProgramInfoLog(object, logLength, NULL, log);
	std::cerr << log << std::endl;
	free(log);
}

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
		shaderFile.close();
	}
	else
	{
#ifdef DEBUG
		std::stringstream error;
		error << "Error opening the " << ((type == GL_VERTEX_SHADER) ? "vertex" : ((type == GL_FRAGMENT_SHADER) ? "fragment" : "unknown")) << " shader";
		printError(error.str());
#endif
		return (0);
	}
	if ((shaderID = glCreateShader(type)) == 0)
	{
#ifdef DEBUG
		std::stringstream error;
		error << "Error creating the " << ((type == GL_VERTEX_SHADER) ? "vertex" : ((type == GL_FRAGMENT_SHADER) ? "fragment" : "unknown")) << " shader";
		printError(error.str());
		printLog(shaderID);
#endif
		return (0);
	}
	tmp[0] = shader.c_str();
	glShaderSource(shaderID, 1, tmp, NULL);
	glCompileShader(shaderID);
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
#ifdef DEBUG
		std::stringstream error;
		error << "Error getting the " << ((type == GL_VERTEX_SHADER) ? "vertex" : ((type == GL_FRAGMENT_SHADER) ? "fragment" : "unknown")) << " shader compilation status";
		printError(error.str());
		printLog(shaderID);
		glDeleteShader(shaderID);
#endif
		return (0);
	}
	return (shaderID);
}

GLuint getProgram(std::string vertexFilename, std::string fragmentFilename)
{
	GLuint program;
	GLuint shader;
	GLint status;

	program = glCreateProgram();
	if ((shader = getShader(vertexFilename, GL_VERTEX_SHADER)) == 0)
		return (0);
	if (shader)
		glAttachShader(program, shader);
	if ((shader = getShader(fragmentFilename, GL_FRAGMENT_SHADER)) == 0)
		return (0);
	if (shader)
		glAttachShader(program, shader);
	glLinkProgram(program);
	status = GL_TRUE;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (!status)
	{
#ifdef DEBUG
		std::stringstream error;
		error << "Error linking program";
		printError(error.str());
		printLog(program);
#endif
		return (0);
	}
	return (program);
}

GLint getAttrib(GLuint program, std::string attributeName)
{
	GLint attribute = glGetAttribLocation(program, attributeName.c_str());

	if (attribute == -1)
	{
#ifdef DEBUG
		std::stringstream error;
		error << "Error binding attribute " << attributeName << " to the program";
		printError(error.str());
#endif
	}
	return (attribute);
}

GLint getUniform(GLuint program, std::string uniformName)
{
	GLint uniform = glGetUniformLocation(program, uniformName.c_str());

	if (uniform == -1)
	{
#ifdef DEBUG
		std::stringstream error;
		error << "Error binding uniform " << uniformName << " to the program";
		printError(error.str());
#endif
	}
	return (uniform);
}
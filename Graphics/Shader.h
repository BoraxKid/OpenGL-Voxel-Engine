#ifndef SHADER_H_
#define SHADER_H_

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "../System/Error.h"

GLuint getShader(std::string filename, GLenum type);
GLuint getProgram(std::string vertexFilename, std::string fragmentFilename);
GLint getAttrib(GLuint program, std::string attributeName);
GLint getUniform(GLuint program, std::string uniformName);

#endif // !SHADER_H_

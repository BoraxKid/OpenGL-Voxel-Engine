#ifndef CONTROLS_H_
#define CONTROLS_H_

#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "../Dependencies/glew/glew.h"
#include "Vector.h"

class ControlManager
{
public:
	ControlManager();
	~ControlManager();
	void init();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	void computeMatrices(vector2i windowSize, vector2i mousePos, unsigned int keys);

private:
	glm::mat4 _viewMatrix;
	glm::mat4 _projectionMatrix;
	glm::vec3 _position;
	vector2i _mousePos;
	GLdouble _lastTime;
	GLfloat _horizontalAngle;
	GLfloat _verticalAngle;
	GLfloat _FOV;
	GLfloat _speed;
	GLfloat _mouseSpeed;
};

#endif // !CONTROLS_H_

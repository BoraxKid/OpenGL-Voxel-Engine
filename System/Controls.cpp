#include "Controls.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
ControlManager::ControlManager()
{

}

ControlManager::~ControlManager()
{

}

void ControlManager::init()
{
	this->_lastTime = glutGet(GLUT_ELAPSED_TIME);
	this->_position = glm::vec3(-12, 9, 8);
	this->_horizontalAngle = 3.14f / 2.0f;
	this->_verticalAngle = 0.0f;

	this->_FOV = 45.0f;
	this->_speed = 0.01f;
	this->_mouseSpeed = 0.005f;
	this->_mousePos = vector2i(0, 0);
}

glm::mat4 ControlManager::getViewMatrix()
{
	return (this->_viewMatrix);
}

glm::mat4 ControlManager::getProjectionMatrix()
{
	return (this->_projectionMatrix);
}

void ControlManager::computeMatrices(vector2i windowSize, vector2i mousePos, unsigned int keys)
{
	GLdouble currentTime = glutGet(GLUT_ELAPSED_TIME);
	GLfloat deltaTime = float(currentTime - this->_lastTime);
	glm::vec3 direction;
	glm::vec3 right;
	glm::vec3 up;

	if (this->_mousePos != mousePos)
	{
		this->_mousePos = mousePos;
		this->_horizontalAngle += this->_mouseSpeed * float(windowSize.x / 2 - mousePos.x);
		this->_verticalAngle += this->_mouseSpeed * float(windowSize.y / 2 - mousePos.y);
	}
	direction = glm::vec3(cos(this->_verticalAngle) * sin(this->_horizontalAngle), sin(this->_verticalAngle), cos(this->_verticalAngle) * cos(this->_horizontalAngle));
	right = glm::vec3(sin(this->_horizontalAngle - 3.14f / 2.0f), 0, cos(this->_horizontalAngle - 3.14f / 2.0f));
	up = glm::cross(right, direction);
	if (keys & 4) // UP ARROW
		this->_position += direction * deltaTime * this->_speed;
	if (keys & 8) // DOWN ARROW
		this->_position -= direction * deltaTime * this->_speed;
	if (keys & 2) // RIGHT ARROW
		this->_position += right * deltaTime * this->_speed;
	if (keys & 1) // LEFT ARROW
		this->_position -= right * deltaTime * this->_speed;
	if (keys & 16) // GO UP
		this->_position += up * deltaTime * this->_speed;
	if (keys & 32) // GO DOWN
		this->_position -= up * deltaTime * this->_speed;
	this->_projectionMatrix = glm::perspective(this->_FOV, 16.0f / 9.0f, 0.1f, 100.0f);
	this->_viewMatrix = glm::lookAt(this->_position, this->_position + direction, up);
	this->_lastTime = currentTime;
}

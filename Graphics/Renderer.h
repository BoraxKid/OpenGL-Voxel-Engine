#ifndef RENDERER_H_
#define RENDERER_H_

#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "../World/Chunk.h"
#include "../System/Controls.h"

class Renderer
{
public:
	Renderer(int ac, char **av, vector2i position, vector2i size, std::string name);
	~Renderer();
	bool init();
	void onReshape(vector2i size);
	void onDisplay();
	void onIdle();
	void onSpecial(int key, int x, int y);
	void onSpecialUp(int key, int x, int y);
	void onMotion(int x, int y);
	void onMouse(int button, int state, int x, int y);
	void onKeyboard(unsigned char key, int x, int y);
	void onKeyboardUp(unsigned char key, int x, int y);

private:
	int _window;
	vector2i _windowPosition;
	vector2i _windowSize;
	vector2i _mousePos;
	std::vector<Chunk *> _chunks;
	ControlManager _controlManager;
	bool _quit;
	unsigned int _keys;
	GLuint	_program;
	GLint _attCoord;
	GLint _uniMvp;
};

#endif // !RENDERER_H_

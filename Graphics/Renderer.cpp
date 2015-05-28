#include "Renderer.h"

Renderer::Renderer(int ac, char **av, vector2i position, vector2i size, std::string name)
{
	glutInit(&ac, av);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(position.x, position.y);
	glutInitWindowSize(size.x, size.y);
	this->_window = glutCreateWindow(name.c_str());
	this->_windowPosition = position;
	this->_windowSize = size;
	this->_program = 0;
	this->_attCoord = 0;
	this->_uniMvp = 0;
	this->_quit = false;
}

Renderer::~Renderer()
{
	if (this->_program)
		glDeleteProgram(this->_program);
	if (!this->_quit)
		glutDestroyWindow(this->_window);
}

bool Renderer::init()
{
	if (glewInit() != GLEW_OK)
	{
#ifdef DEBUG
		std::stringstream error;
		error << "Error initializing glew";
		printError(error.str());
#endif
		return (false);
	}
	this->_program = getProgram("cube.v.glsl", "cube.f.glsl");
	if (!this->_program)
		return (false);
	this->_attCoord = getAttrib(this->_program, "coord");
	this->_uniMvp = getUniform(this->_program, "mvp");
	if (this->_attCoord == -1 || this->_uniMvp == -1)
		return (false);
	glClearColor(0.0, 0.0, 0.4, 1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glEnableVertexAttribArray(this->_attCoord);
	Chunk *tmp;
	tmp = new Chunk();
	this->_chunks.push_back(tmp);
	this->_controlManager.init();
	return (true);
}

void Renderer::onReshape(vector2i size)
{
	this->_windowSize = size;
	glViewport(0, 0, size.x, size.y);
}

void Renderer::onDisplay()
{
	glm::mat4 mvp;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(this->_program);
	this->_controlManager.computeMatrices(this->_windowSize, this->_mousePos, this->_keys);
	mvp = this->_controlManager.getProjectionMatrix() * this->_controlManager.getViewMatrix() * glm::mat4(1.0);
	glUniformMatrix4fv(this->_uniMvp, 1, GL_FALSE, glm::value_ptr(mvp));
	this->_chunks.at(0)->render(this->_attCoord);
	glutSwapBuffers();
}

void Renderer::onIdle()
{
	glutPostRedisplay();
}

void Renderer::onSpecial(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
		this->_keys |= 1;
	if (key == GLUT_KEY_RIGHT)
		this->_keys |= 2;
	if (key == GLUT_KEY_UP)
		this->_keys |= 4;
	if (key == GLUT_KEY_DOWN)
		this->_keys |= 8;
	if (key == GLUT_KEY_PAGE_UP)
		this->_keys |= 16;
	if (key == GLUT_KEY_PAGE_DOWN)
		this->_keys |= 32;
	if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
		this->_keys |= 32;
}

void Renderer::onSpecialUp(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
		this->_keys &= ~1;
	if (key == GLUT_KEY_RIGHT)
		this->_keys &= ~2;
	if (key == GLUT_KEY_UP)
		this->_keys &= ~4;
	if (key == GLUT_KEY_DOWN)
		this->_keys &= ~8;
	if (key == GLUT_KEY_PAGE_UP)
		this->_keys &= ~16;
	if (key == GLUT_KEY_PAGE_DOWN)
		this->_keys &= ~32;
	if (glutGetModifiers() != GLUT_ACTIVE_SHIFT)
		this->_keys &= ~32;
}

void Renderer::onMotion(int x, int y)
{
	static bool warp = false;
	
	if (!warp)
	{
		this->_mousePos = vector2i(x, y);
		glutWarpPointer(this->_windowSize.x / 2, this->_windowSize.y / 2);
		warp = true;
	}
	else
		warp = false;
}

void Renderer::onMouse(int button, int state, int x, int y)
{
	if (state != GLUT_DOWN)
		return;
}

void Renderer::onKeyboard(unsigned char key, int x, int y)
{
	if (key == 27)
	{
		this->_quit = true;
		glutDestroyWindow(this->_window);
	}
	if (key == 'q' || key == 'Q')
		this->_keys |= 1;
	if (key == 'd' || key == 'D')
		this->_keys |= 2;
	if (key == 'z' || key == 'Z')
		this->_keys |= 4;
	if (key == 's' || key == 'S')
		this->_keys |= 8;
	if (key == ' ')
		this->_keys |= 16;
	if (key == 'a' || key == 'A')
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (key == 'e' || key == 'E')
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Renderer::onKeyboardUp(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 'Q')
		this->_keys &= ~1;
	if (key == 'd' || key == 'D')
		this->_keys &= ~2;
	if (key == 'z' || key == 'Z')
		this->_keys &= ~4;
	if (key == 's' || key == 'S')
		this->_keys &= ~8;
	if (key == ' ')
		this->_keys &= ~16;
}

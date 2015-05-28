#include "Graphics/Renderer.h"

Renderer *g_window;

void onReshape(int x, int y)
{
	g_window->onReshape(vector2i(x, y));
}

void onDisplay()
{
	g_window->onDisplay();
}

void onIdle()
{
	g_window->onIdle();
}

void onSpecial(int key, int x, int y)
{
	g_window->onSpecial(key, x, y);
}

void onSpecialUp(int key, int x, int y)
{
	g_window->onSpecialUp(key, x, y);
}

void onMotion(int x, int y)
{
	g_window->onMotion(x, y);
}

void onMouse(int button, int state, int x, int y)
{
	g_window->onMouse(button, state, x, y);
}

void onKeyboard(unsigned char key, int x, int y)
{
	g_window->onKeyboard(key, x, y);
}

void onKeyboardUp(unsigned char key, int x, int y)
{
	g_window->onKeyboardUp(key, x, y);
}

int main(int ac, char **av)
{
	g_window = new Renderer(ac, av, vector2i(500, 0), vector2i(640, 480), "OpenGL");
	if (g_window->init())
	{
		glutSetCursor(GLUT_CURSOR_NONE);
		glutWarpPointer(320, 240);
		glutDisplayFunc(onDisplay);
		glutIdleFunc(onIdle);
		glutReshapeFunc(onReshape);
		glutKeyboardFunc(onKeyboard);
		glutKeyboardUpFunc(onKeyboardUp);
		glutSpecialFunc(onSpecial);
		glutSpecialUpFunc(onSpecialUp);
		glutPassiveMotionFunc(onMotion);
		glutMotionFunc(onMotion);
		glutMouseFunc(onMouse);
		glutMainLoop();
	}
	delete (g_window);
	return (0);
}

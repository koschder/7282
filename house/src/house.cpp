/////////////////////////////////////////////////////////////////////////////////////////
// Assignment: CG-02.01A - 3D House (Ver 2.0)                                          //
/////////////////////////////////////////////////////////////////////////////////////////


#if defined(__APPLE__) && defined(__MACH__)
	#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

#include "zpr.h"

const float HOUSE_WIDTH = 5.0F;     // width of house
const float HOUSE_HEIGHT = 3.0F;    // height of roof


void checkErrorCode(void)
/////////////////////////////////////////////////////////////////////////////////////////
{
	GLenum errCode;
	const GLubyte *errString;

	if ((errCode = glGetError()) != GL_NO_ERROR)
	{
		errString = gluErrorString(errCode);
		cout << "OpenGL Error Code: " << errCode << " (" << errString << ")" << endl;
	}
}



void drawHouse(float witdth, float heigth)
/////////////////////////////////////////////////////////////////////////////////////////
{
	float base = witdth / 2.0F;
	float fence = heigth / 2.0F;

	// draw ground
	glColor3f(0.0, 0.75, 0.0);
    glBegin(GL_QUADS);
		glVertex3f(-witdth, -witdth, 0.0);
		glVertex3f( witdth, -witdth, 0.0);
		glVertex3f( witdth,  witdth, 0.0);
		glVertex3f(-witdth,  witdth, 0.0);
    glEnd();

}


void display(void)
/////////////////////////////////////////////////////////////////////////////////////////
{
    glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

    glClear(GL_COLOR_BUFFER_BIT);

	drawHouse(HOUSE_WIDTH, HOUSE_HEIGHT);
	glFlush();

	glPopMatrix();
	checkErrorCode();
}


void initRendering()
/////////////////////////////////////////////////////////////////////////////////////////
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

	glDisable(GL_CULL_FACE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
}


void menu1(int item)
/////////////////////////////////////////////////////////////////////////////////////////
{
	switch (item)
	{
		case 0:
		{
			exit(0);
			break;
		}
		case 1:
		{
			glutSetWindowTitle("3D House (Wireframe Mode)");
			glutChangeToMenuEntry(1, "Disable Wireframe", 2);
			break;
		}
		case 2:
		{
			glutSetWindowTitle("3D House (Solid Mode)");
			glutChangeToMenuEntry(1, "Enable Wireframe", 1);
			break;
		}
		case 3:
		{
			glEnable(GL_CULL_FACE);
			glutChangeToMenuEntry(2, "Disable Culling", 4);
			break;
		}
		case 4:
		{
			glDisable(GL_CULL_FACE);
			glutChangeToMenuEntry(2, "Enable Culling", 3);
			break;
		}
		default:
		{
		}
	}
	glutPostRedisplay();
}



void initMenu()
/////////////////////////////////////////////////////////////////////////////////////////
{
    // create menu
    glutCreateMenu(menu1);
    glutAddMenuEntry("Enable Wireframe", 1);
    glutAddMenuEntry("Enable Culling", 3);
    glutAddMenuEntry("Exit", 0);

    // attach menu to right mouse button
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


int main(int argc, char** argv)
/////////////////////////////////////////////////////////////////////////////////////////
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("3D House");
    initRendering();
    initMenu();
	zprInit();

	// register callbacks
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}

/* Compile code as: gcc hello.c -lGL -lglut */

#include<GL/glut.h>

void display()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-6,6,-6,6);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_POLYGON);
		glVertex2f(-5, -5);
		glVertex2f(5, -5);
		glVertex2f(5, 5);
		glVertex2f(-5, 5);
	glEnd();
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("Simple Polygon");
	glutDisplayFunc(display);
	glutMainLoop();
}



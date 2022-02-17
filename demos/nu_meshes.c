/* Compile code as: gcc hello.c -lGL -lglut */

#include<GL/glut.h>

void display()
{
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-3,2.5,-3,2.5);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	GLfloat my_vertex[8][2] = { {-5,0}, {-2.5,2.5}, {0, 2.5}, {2.5, 0}, {2.5, -2.5}, {0, -5}, {-2.5, -5}, {-5, -2.5} };

	glBegin(GL_TRIANGLES);
		glVertex2fv(my_vertex[0]);
		glVertex2fv(my_vertex[1]);
		glVertex2fv(my_vertex[2]);
		glVertex2fv(my_vertex[3]);
		glVertex2fv(my_vertex[4]);
		glVertex2fv(my_vertex[5]);
		glVertex2fv(my_vertex[6]);
		glVertex2fv(my_vertex[7]);
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



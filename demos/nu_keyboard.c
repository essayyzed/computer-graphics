/* Compile code as: gcc hello.c -lGL -lglut */

#include<GL/glut.h>

float move_y = 0;
float move_x = 0;

void display()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_POLYGON);
		glVertex2f(-.5 + move_x, -.5 + move_y);
		glVertex2f( .5 + move_x, -.5 + move_y);
		glVertex2f( .5 + move_x,  .5 + move_y);
		glVertex2f(-.5 + move_x,  .5 + move_y);
	glEnd();
	glFlush();
}

void keyboard(int key, int x, int y)
{
	switch(key)
	{
case GLUT_KEY_RIGHT:	move_x += .1; break;
case GLUT_KEY_LEFT:		move_x -= .1; break;
case GLUT_KEY_UP:			move_y += .1; break;
case GLUT_KEY_DOWN:		move_y -= .1; break;
	}

	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("Simple Polygon");
	glutDisplayFunc(display);
	glutSpecialFunc(keyboard);
	glutMainLoop();
}



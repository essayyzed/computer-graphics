/* Compile code as: gcc hello.c -lGL -lglut */

#include<GL/glut.h>
#include<math.h>

double rotate_x = 0;
double rotate_y = 0;

void keyboard(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_RIGHT:	rotate_x += .1; break;
		case GLUT_KEY_LEFT:		rotate_x -= .1; break;
		case GLUT_KEY_UP:			rotate_y += .1; break;
		case GLUT_KEY_DOWN:		rotate_y -= .1; break;
	}

	glutPostRedisplay();
}

GLUquadricObj *sphere1;

void display()
{
	glRotatef(rotate_y, 1.0, 0.0, 0.0);
	glRotatef(rotate_x, 0.0, 1.0, 0.0);

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0.0, 0.0, 0.0);

	gluSphere(sphere1, 1, 50, 50);

	glFlush();
	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("Simple Polygon");
	glutDisplayFunc(display);
	glutSpecialFunc(keyboard);

	sphere1 = gluNewQuadric();
	gluQuadricDrawStyle(sphere1, GLU_LINE);

	glutMainLoop();
}

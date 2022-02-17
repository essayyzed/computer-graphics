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

void display()
{
	glRotatef( rotate_y, 1.0, 0.0, 0.0 );
	glRotatef( rotate_x, 0.0, 1.0, 0.0 );

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	int i;
	int points = 360;
	double theta = acos(-1)*2 / (double)points, x, y;
	glBegin(GL_LINE_STRIP);
		for (i = 0; i <= points; i++) {
			x = 0.5*cos(i*theta);
			y = 0.5*sin(i*theta);
			glVertex3f(x, y, .5);
		}
	glEnd();
	glBegin(GL_LINE_LOOP);
		for (i = 0; i < points; i++) {
			x = 0.5*cos(i*theta);
			y = 0.5*sin(i*theta);
			glVertex3f(x, y, -.5);
		}
	glEnd();
	points = 50;
	glBegin(GL_LINE_LOOP);
		for (i = 0; i < points; i++) {
			x = 0.5*cos(i*(360/points)*theta);
			y = 0.5*sin(i*(360/points)*theta);
			glVertex3f(x, y, +.5);
			glVertex3f(x, y, -.5);
			x = 0.5*cos((i+(360/points))*(360/points)*theta);
			y = 0.5*sin((i+(360/points))*(360/points)*theta);
			glVertex3f(x, y, -.5);
			glVertex3f(x, y, +.5);
		}
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
	glutSpecialFunc(keyboard);
	glutMainLoop();
}



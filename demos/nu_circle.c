/* Compile code as: gcc hello.c -lGL -lglut */

#include<GL/glut.h>
#include<math.h>

void display()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	int i;
	int points = 20;
	float step = 2. / (double)points, x, y;
	glBegin(GL_POLYGON);
		for (i = points/2; i >= (-1*points/2); i--) {
			x = i*step;
			y = sqrt(1-pow(x,2));
			glVertex2f(x, y);
		}
		for (i = -1*points/2; i < points/2; i++) {
			x = i*step;
			y = -sqrt(1-pow(x,2));
			glVertex2f(x, y);
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
	glutMainLoop();
}



/* Compile code as: gcc hello.c -lGL -lglut */

#include<stdio.h>
#include<math.h>
#include<GL/glut.h>

float vy = 0;
float dy = 15;
double g = -9.8*10;
int A = 1;

GLfloat points[] = {	-.5,	-.5,	0, 
											.5, -.5,	0, 
											.5, .5, 0, 
											-.5, .5, 0, 
											-.5,	-.5, .5, 
											.5, -.5, .5, 
											.5, .5, .5, 
											-.5, .5, .5 };

void quad (GLint n1, GLint n2, GLint n3, GLint n4, float x, float y, float z)
{
	glBegin(GL_POLYGON);
		glVertex3f( points[3*n1]+x, points[3*n1+1]+y, points[3*n1+2]+z );
		glVertex3f( points[3*n2]+x, points[3*n2+1]+y, points[3*n2+2]+z );
		glVertex3f( points[3*n3]+x, points[3*n3+1]+y, points[3*n3+2]+z );
		glVertex3f( points[3*n4]+x, points[3*n4+1]+y, points[3*n4+2]+z );
	glEnd();
}

void cube(float x, float y, float z)
{
	glColor3f(1.0, 0.0, 0.0);
	quad(0, 1, 2, 3, x, y, z);
	
	glColor3f(0.0, 1.0, 0.0);
	quad(4, 5, 6, 7, x, y, z);

	glColor3f(0.0, 0.0, 1.0);
	quad(2, 3, 7, 6, x, y, z);

	glColor3f(1.0, 1.0, 0.0);
	quad(0, 1, 5, 4, x, y, z);

	glColor3f(1.0, 0.0, 1.0);
	quad(1, 2, 6, 5, x, y, z);

	glColor3f(0.0, 1.0, 1.0);
	quad(3, 7, 4, 0, x, y, z);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-15,15,-15,15,-1,1);

	glScalef(A, 1, 1);
	cube(0, dy, 0);
	
	glFlush();
	glutSwapBuffers();
}


void keyboard(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_RIGHT:	A=10; break;
		case GLUT_KEY_LEFT:		A=1;  break;
		case GLUT_KEY_UP:			break;
		case GLUT_KEY_DOWN:		break;
	}
	glutPostRedisplay();
}

void timer(int x)
{
	if (g < 0) {
		vy += 1/(double)(1000/(double)25) * g;
		dy += 1/(double)(1000/(double)25) * vy;
		if (dy < 0) g *= -1;
	}
	else {
		vy += 1/(double)(1000/(double)25) * g;
		dy -= 1/(double)(1000/(double)25) * 0.8 * vy;
		if (vy > 0) g *= -1;
	}
	printf("%f %f %f\n", g, dy, vy);
	glutPostRedisplay();
	glutTimerFunc(1000/25, timer, 0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("Simple Polygon");
	glutTimerFunc(1000/25, timer, 0);
	glutSpecialFunc(keyboard);
	glutDisplayFunc(display);
	glutMainLoop();
}


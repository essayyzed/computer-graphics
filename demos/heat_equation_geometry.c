/* Compile code as: gcc hello.c -lGL -lglut */

#include <GL/glut.h>
#include <stdio.h>
float rotate_y = 0;
float rotate_x = 0;

void keyboard(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_RIGHT:	rotate_x += 10; break;
		case GLUT_KEY_LEFT:		rotate_x -= 10; break;
		case GLUT_KEY_UP:			rotate_y += 10; break;
		case GLUT_KEY_DOWN:		rotate_y -= 10; break;
	}

	glutPostRedisplay();
}

GLfloat points[8][3] = {	{0, 0,  0}, {1, 0,  0}, {1, 1,  0}, {0, 1,  0}, 
													{0, 0,  1}, {1, 0,  1}, {1, 1,  1}, {0, 1,  1} };

void quad (GLint n1, GLint n2, GLint n3, GLint n4, GLfloat dx, GLfloat dy, GLfloat dz)
{
	glBegin(GL_POLYGON);
		glVertex3f( points[n1][0]*dx, points[n1][1]*dy, points[n1][2]*dz );
		glVertex3f( points[n2][0]*dx, points[n2][1]*dy, points[n2][2]*dz );
		glVertex3f( points[n3][0]*dx, points[n3][1]*dy, points[n3][2]*dz );
		glVertex3f( points[n4][0]*dx, points[n4][1]*dy, points[n4][2]*dz );
	glEnd();
}

void cube(GLfloat dx, GLfloat dy, GLfloat dz)
{
	glColor3f(rand()/(double)RAND_MAX, 0.0, 0.0);
	quad(0, 1, 2, 3, dx, dy, dz);
	quad(4, 5, 6, 7, dx, dy, dz);
	quad(2, 3, 7, 6, dx, dy, dz);
	quad(0, 1, 5, 4, dx, dy, dz);
	quad(1, 2, 6, 5, dx, dy, dz);
	quad(3, 7, 4, 0, dx, dy, dz);
}

void cubeMesh(GLfloat l, GLfloat r, GLfloat t, GLfloat b, GLfloat n, GLfloat f, GLint nx, GLint ny, GLint nz)
{
	GLfloat dx = abs(r-l)/(double)nx;
	GLfloat dy = abs(t-b)/(double)ny;
	GLfloat dz = abs(f-n)/(double)nz;
	int i, j, k;
	glTranslatef(l, t, n);
	for (k = 0; k < nz; k++) {
		for (j = 0; j < ny; j++) {
			for (i = 0; i < nx; i++) {
				cube(dx, dy, dz);
				glTranslatef(dx, 0, 0);
			}
			glTranslatef(-dx*nx, 0, 0);
			glTranslatef(0, dy, 0);
		}
		glTranslatef(0, -dy*ny, 0);
		glTranslatef(0, 0, dz);
	}
	glTranslatef(0, 0, -dz*nz);
}

void display()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-5.,5.,-5,5.,-5.,5.);

	glRotatef( rotate_y, 1.0, 0.0, 0.0 );
	glRotatef( rotate_x, 0.0, 1.0, 0.0 );

	cubeMesh(-2, +2., -2, 2, -2, 2, 10, 10, 10);

	glFlush();
	glutSwapBuffers();
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



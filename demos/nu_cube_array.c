/* Compile code as: gcc hello.c -lGL -lglut */

#include<GL/glut.h>

float rotate_y = 0;
float rotate_x = 0;

void keyboard(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_RIGHT:	rotate_x += 1; break;
		case GLUT_KEY_LEFT:		rotate_x -= 1; break;
		case GLUT_KEY_UP:			rotate_y += 1; break;
		case GLUT_KEY_DOWN:		rotate_y -= 1; break;
	}

	glutPostRedisplay();
}

GLfloat points[8][3] = {	{0, 0, 0}, {.5, 0, 0}, {.5, .5, 0}, {0, .5, 0}, 
													{0, 0, .5}, {.5, 0, .5}, {.5, .5, .5}, {0, .5, .5} };

void quad (GLint n1, GLint n2, GLint n3, GLint n4)
{
	glBegin(GL_POLYGON);
		glVertex3fv( points[n1] );
		glVertex3fv( points[n2] );
		glVertex3fv( points[n3] );
		glVertex3fv( points[n4] );
	glEnd();
}

void display()
{
	glRotatef( rotate_y, 1.0, 0.0, 0.0 );
	glRotatef( rotate_x, 0.0, 1.0, 0.0 );

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 0.0, 0.0);
	quad(0, 1, 2, 3);
	
	glColor3f(0.0, 1.0, 0.0);
	quad(4, 5, 6, 7);

	glColor3f(0.0, 0.0, 1.0);
	quad(2, 3, 7, 6);

	glColor3f(1.0, 1.0, 0.0);
	quad(0, 1, 5, 4);

	glColor3f(1.0, 0.0, 1.0);
	quad(1, 2, 6, 5);

	glColor3f(0.0, 1.0, 1.0);
	quad(3, 7, 4, 0);

	glFlush();
	//glutSwapBuffers();	
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



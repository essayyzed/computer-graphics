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

void display()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	glRotatef( rotate_y, 1.0, 0.0, 0.0 );
	glRotatef( rotate_x, 0.0, 1.0, 0.0 );

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f( -0.5, -0.5, 0.5 );
		glVertex3f(  0.5, -0.5, 0.5 );
		glVertex3f( -0.5,  0.5, 0.5 );
		// glColor3f(0., 1., 0.);
		glVertex3f(  0.5,  0.5, 0.5 );
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f( -0.5, -0.5, -0.5 );
		glVertex3f(  0.5, -0.5, -0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
		// glColor3f(0., 0., 1.);
		glVertex3f(  0.5,  0.5, -0.5 );
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(  0.5, -0.5, 0.5 );
		glVertex3f(  0.5,  0.5, 0.5 );
		glVertex3f(  0.5, -0.5, -0.5 );
		glColor3f(1., 0., 0.);
		glVertex3f(  0.5,  0.5, -0.5 );
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f( -0.5, -0.5,  0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
		glVertex3f( -0.5, -0.5, -0.5 );
		// glColor3f(0., 1., 0.);
		glVertex3f( -0.5,  0.5,  0.5 );
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f( -0.5,  0.5,  0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
		glVertex3f(  0.5,  0.5,  0.5 );
		// glColor3f(0., 0., 1.);
		glVertex3f(  0.5,  0.5, -0.5 );
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f( -0.5, -0.5,  0.5 );
		glVertex3f( -0.5, -0.5, -0.5 );
		glVertex3f(  0.5, -0.5,  0.5 );
		// glColor3f(1., 0., 0.);
		glVertex3f(  0.5, -0.5, -0.5 );
	glEnd();

	glFlush();
	glutSwapBuffers();	
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



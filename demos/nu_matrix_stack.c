/* Compile code as: gcc hello.c -lGL -lglut */

#include<math.h>
#include<stdio.h>
#include<GL/glut.h>

float rotate_y = 0;
float rotate_x = 0;

void drawCube(GLfloat x, GLfloat y, GLfloat z)
{
	
	glMatrixMode(GL_MODELVIEW);
	
	glTranslatef(x, y, z);
	glBegin(GL_QUADS);
		glColor3f(1., 0., 0.);
		glVertex3f(-0.5, -0.5, 0.5);
		glVertex3f( 0.5, -0.5, 0.5);
		glVertex3f( 0.5,  0.5, 0.5);
		glVertex3f(-0.5,  0.5, 0.5);
	glEnd();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_QUADS);
		glColor3f(0., 1., 0.);
		glVertex3f(-0.5, -0.5, 0.5);
		glVertex3f( 0.5, -0.5, 0.5);
		glVertex3f( 0.5,  0.5, 0.5);
		glVertex3f(-0.5,  0.5, 0.5);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 0, 1, 0);
	glBegin(GL_QUADS);
		glColor3f(0., 0., 1.);
		glVertex3f(-0.5, -0.5, 0.5);
		glVertex3f( 0.5, -0.5, 0.5);
		glVertex3f( 0.5,  0.5, 0.5);
		glVertex3f(-0.5,  0.5, 0.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glBegin(GL_QUADS);
		glColor3f(1., 0., 1.);
		glVertex3f(-0.5, -0.5, 0.5);
		glVertex3f( 0.5, -0.5, 0.5);
		glVertex3f( 0.5,  0.5, 0.5);
		glVertex3f(-0.5,  0.5, 0.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glBegin(GL_QUADS);
		glColor3f(1., 1., 1.);
		glVertex3f(-0.5, -0.5, 0.5);
		glVertex3f( 0.5, -0.5, 0.5);
		glVertex3f( 0.5,  0.5, 0.5);
		glVertex3f(-0.5,  0.5, 0.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glBegin(GL_QUADS);
		glColor3f(1., 1., 0.);
		glVertex3f(-0.5, -0.5, 0.5);
		glVertex3f( 0.5, -0.5, 0.5);
		glVertex3f( 0.5,  0.5, 0.5);
		glVertex3f(-0.5,  0.5, 0.5);
	glEnd();
	glPopMatrix();

	glRotatef(rotate_y, 0, 0.5, 0.5);
	
	glTranslatef(-x, -y, -z);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5, 5, -5, 5);

	//drawCube(-2.5, 0, 0);
	drawCube(0, 0, 0);
	//drawCube(2.5, 0, 0);

	glFlush();
	glutSwapBuffers();
}

void timer(int x)
{
	rotate_x = x + 0.2;
	rotate_y = x + 0.2;
	glutPostRedisplay();
	glutTimerFunc(1000/60., timer, 0);
}

void mouse(int button, int state, int x, int y)
{
	switch(button)
	{
	case GLUT_LEFT_BUTTON:
		printf("left\n"); break;
	case GLUT_MIDDLE_BUTTON: // do that
		printf("middle\n"); break;
	case GLUT_RIGHT_BUTTON:
		printf("right\n"); break;
	}

	switch(state)
	{
	case GLUT_UP: // do this
		printf("up\n"); break;
	case GLUT_DOWN: // do that
		printf("down\n"); break;
	}
	
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("Simple Polygon");
	glutTimerFunc(1000/60., timer, 0);
	glutMouseFunc(mouse);
	glutDisplayFunc(display);
	glutMainLoop();
}


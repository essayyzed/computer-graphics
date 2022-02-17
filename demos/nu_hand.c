/* Compile code as: gcc hello.c -lGL -lglut */

#include<math.h>
#include<GL/glut.h>

float rotate_y = 0;
float rotate_x = 0;

void prepareCube(GLfloat x, GLfloat y, GLfloat z)
{
	glMatrixMode(GL_MODELVIEW);

	glTranslatef(x, y, z);

	glBegin(GL_POLYGON);
		glColor3f(   1.0,  1.0, 0.0 );
		glVertex3f( -0.5, -0.5, -0.5 );
		glVertex3f(  0.5, -0.5, -0.5 );
		glVertex3f(  0.5,  0.5, -0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
	glEnd();

	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		glColor3f(   1.0,  0.0, 0.0 );
		glVertex3f( -0.5, -0.5, -0.5 );
		glVertex3f(  0.5, -0.5, -0.5 );
		glVertex3f(  0.5,  0.5, -0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		glColor3f(   0.0,  0.0, 1.0 );
		glVertex3f( -0.5, -0.5, -0.5 );
		glVertex3f(  0.5, -0.5, -0.5 );
		glVertex3f(  0.5,  0.5, -0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		glColor3f(   0.0,  1.0, 1.0 );
		glVertex3f( -0.5, -0.5, -0.5 );
		glVertex3f(  0.5, -0.5, -0.5 );
		glVertex3f(  0.5,  0.5, -0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glColor3f(   1.0,  0.0, 1.0 );
		glVertex3f( -0.5, -0.5, -0.5 );
		glVertex3f(  0.5, -0.5, -0.5 );
		glVertex3f(  0.5,  0.5, -0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glColor3f(   1.0,  0.0, 1.0 );
		glVertex3f( -0.5, -0.5, -0.5 );
		glVertex3f(  0.5, -0.5, -0.5 );
		glVertex3f(  0.5,  0.5, -0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
	glEnd();
	glPopMatrix();

	glTranslatef(-x, -y, -z);	
}

GLfloat elements[16];
GLfloat elements2[16];
	
void display()
{
  glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glRotatef(rotate_x, 1, 0, 0);
	glRotatef(rotate_y, 0, 1, 0);

	prepareCube( -1, 0, 0);

	glFlush();
	glutSwapBuffers();
}

void timer(int x)
{
	rotate_x += 0.0025;
	rotate_y -= 0.0025;
	glutPostRedisplay();
	glutTimerFunc(1000/60., timer, 0);
}

void glInit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-3, 3, -3, 3, 1, 20);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("Simple Polygon");
	glutTimerFunc(1000/60., timer, 0);
	glInit();
	glutDisplayFunc(display);
	glutMainLoop();
}


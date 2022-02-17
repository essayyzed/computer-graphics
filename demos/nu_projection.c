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

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	#if 0
	elements[0] = cos(rotate_x);
	elements[1] = sin(rotate_x);;
	elements[2] = 0;
	elements[3] = 0;

	elements[4] = -sin(rotate_x);
	elements[5] = cos(rotate_x);
	elements[6] = 0;
	elements[7] = 0;

	elements[8] = 0;
	elements[9] = 0;
	elements[10] = 1;
	elements[11] = 0;

	elements[12] = 0;
	elements[13] = 0;
	elements[14] = 0;
	elements[15] = 1;
	glLoadMatrixf(elements);
	#endif
	glOrtho(-3, 3, -3, 3, 1, 20);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	#if 0
	elements2[0] = cos(-rotate_x);
	elements2[1] = sin(-rotate_x);;
	elements2[2] = 0;
	elements2[3] = 0;

	elements2[4] = -sin(-rotate_x);
	elements2[5] = cos(-rotate_x);
	elements2[6] = 0;
	elements2[7] = 0;

	elements2[8] = 0;
	elements2[9] = 0;
	elements2[10] = 1;
	elements2[11] = 0;

	elements2[12] = 0;
	elements2[13] = 0;
	elements2[14] = 0;
	elements2[15] = 1;
	glLoadMatrixf(elements2);
#endif
	gluLookAt(-0.5, 0, 1, 0, 0, 0, 0, 1, 0);

//	prepareCube(-2.5, 0, 0);
	prepareCube( 0.5, 0.5, 0);
//	prepareCube( 2.5, 0, 0);

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

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("Simple Polygon");
	glutTimerFunc(1000/60., timer, 0);
	glutDisplayFunc(display);
	glutMainLoop();
}


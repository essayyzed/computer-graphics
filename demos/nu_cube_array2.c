/* Compile code as: gcc hello.c -lGL -lglut */

#include<GL/glut.h>

float rotate_y = 0;
float rotate_x = 0;

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

GLfloat points[] = {	0,	0,	0, 
											.5, 0,	0, 
											.5, .5, 0, 
											0,	.5, 0, 
											0,	0, .5, 
											.5, 0, .5, 
											.5, .5, .5, 
											0, .5, .5 };

GLubyte vertIndex[] = {	0, 1, 2, 3, 
												7, 6, 5, 4, 
												6, 7, 3, 2, 
												4, 5, 1, 0, 
												5, 6, 2, 1, 
												0, 4, 7, 3};

GLubyte colors[] = {	255, 0, 0,
											255, 0, 0,
											255, 0, 0,
											255, 0, 0,
											0, 0, 255,
											0, 0, 255,
											0, 0, 255,
											0, 0, 255
};

void display()
{
  glEnable(GL_DEPTH_TEST);

	glRotatef( rotate_y, 1.0, 0.0, 0.0 );
	glRotatef( rotate_x, 0.0, 1.0, 0.0 );

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableClientState(GL_VERTEX_ARRAY);
	// glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, points);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, colors);

	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, vertIndex);

	glFlush();
	glutSwapBuffers();
}

void timer(int x)
{
	rotate_x = x + 0.1;
	rotate_y = x - 0.1;
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
	glutSpecialFunc(keyboard);
	glutMainLoop();
}



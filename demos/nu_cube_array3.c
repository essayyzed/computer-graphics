/* Compile code as: gcc hello.c -lGL -lglut */

#include<math.h>
#include<GL/glut.h>

float rotate_y = 0;
float rotate_x = 0;

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

	GLfloat elements[16];
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

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(elements);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, points);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, colors);

	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, vertIndex);

	glFlush();
	glutSwapBuffers();
}

void timer(int x)
{
	rotate_x += 0.01;
	rotate_y -= 0.01;
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

//glFrontFace(GL_CCW);
	
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);


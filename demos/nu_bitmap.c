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

const GLubyte bitshape[] =
									{	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 
										 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 
										 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 
										 0, 0, 0, 1, 1, 1, 0, 0, 0, 0 , 
										 0, 0, 0, 1, 1, 1, 0, 0, 0, 0 , 
										 0, 0, 0, 1, 1, 1, 0, 0, 0, 0 , 
										 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 
										 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 
										 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 
										 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  };

void display()
{
	glRotatef( rotate_y, 1.0, 0.0, 0.0 );
	glRotatef( rotate_x, 0.0, 1.0, 0.0 );

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glRasterPos2i(20,20);

	glBitmap(10,10, 0, 0, 11, 0, bitshape);

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



/* Compile code as: gcc hello.c -lGL -lglut */

#include<GL/glut.h>
#include<math.h>

double rotate_x = 0;
double rotate_y = 0;

void mouse(int button, int state, int x, int y)
{

}

void keyboard(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_RIGHT:	rotate_x += .1; break;
		case GLUT_KEY_LEFT:		rotate_x -= .1; break;
		case GLUT_KEY_UP:			rotate_y += .1; break;
		case GLUT_KEY_DOWN:		rotate_y -= .1; break;
		case 'a': rotate_y -= 2; break;
	}

	glutPostRedisplay();
}

void display()
{
	glRotatef( rotate_y, 1.0, 0.0, 0.0 );
	glRotatef( rotate_x, 0.0, 1.0, 0.0 );

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int i, j;
	int points = 10;
	double theta = acos(-1)*2 / (double)points, x, y, z;
	double phi   = acos(-1)*2 / (double)points;

	for (i = 0; i < points; i++) 
	{
		for (j = 0; j < points; j++) 
		{
			glBegin(GL_QUADS);//LINE_LOOP);
			
				glColor3f(0., 0., rand()/(double)RAND_MAX + 0.5);
				x = 0.75*cos(i*phi)*cos(j*theta);
				y = 0.75*cos(i*phi)*sin(j*theta);
				z = 0.75*sin(i*phi);
				glVertex3f(x, y, z);

				x = 0.75*cos((i+1)*phi)*cos(j*theta);
				y = 0.75*cos((i+1)*phi)*sin(j*theta);
				z = 0.75*sin((i+1)*phi);
				glVertex3f(x, y, z);
	
				x = 0.75*cos((i+1)*phi)*cos((j+1)*theta);
				y = 0.75*cos((i+1)*phi)*sin((j+1)*theta);
				z = 0.75*sin((i+1)*phi);
				glVertex3f(x, y, z);
			
				x = 0.75*cos(i*phi)*cos((j+1)*theta);
				y = 0.75*cos(i*phi)*sin((j+1)*theta);
				z = 0.75*sin(i*phi);
				glVertex3f(x, y, z);
								
			glEnd();
			glFlush();
		}
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("Simple Polygon");
	glutDisplayFunc(display);
	glutSpecialFunc(keyboard);
	glutMouseFunc(mouse);
	glutMainLoop();
}



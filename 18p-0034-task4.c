/* Compile code as: gcc hello.c -lGL -lglut */

#include<GL/glut.h>
#include<math.h>

double rotate_x = 0;
double rotate_y = 0;

void drawSphere(int x_pos, int y_pos, int z_pos, int points)
{
	double theta = acos(-1)*2 / (double)points;
	double phi   = acos(-1)*2 / (double)points;
	double x, y, z;

	int i, j;
	for (i = 0; i < points; i++) 
	{
		for (j = 0; j < points; j++) 
		{
			glBegin(GL_LINE_LOOP);
			
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

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glRotatef( rotate_y, 1.0, 0.0, 0.0 );
	glRotatef( rotate_x, 0.0, 1.0, 0.0 );

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	drawSphere(0, 0, 0, 50);
	glutSwapBuffers();
}

void timer(int x)
{
	rotate_x += 0.025;
	rotate_y += 0.025;
	glutPostRedisplay();
	glutTimerFunc(1000/100, timer, 0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("Simple Polygon");
	glutTimerFunc(1000/60., timer, 0);
	glutDisplayFunc(display);
	glutMainLoop();
}



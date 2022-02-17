/* Compile code as: gcc hello.c -lGL -lglut */

#include<GL/glut.h>
#include<math.h>

double rotate_x = 0;
double rotate_y = 0;

int points = 20;
GLfloat *vertices;
GLubyte *vertIndex;
GLubyte *colors;

void prepareVertices()
{
	double theta = acos(-1)*2./(double)points;
	double phi   = acos(-1)*2/(double)points;
	double x, y, z;

	int i, j;
	for (i = 0; i < points; i++)
	{
		for (j = 0; j < points; j++)
		{
			x = 0.75*cos(i*phi)*cos(j*theta);
			y = 0.75*cos(i*phi)*sin(j*theta);
			z = 0.75*sin(i*phi);
			
			vertices[3*(j*points+i)+0] = x;
			vertices[3*(j*points+i)+1] = y;
			vertices[3*(j*points+i)+2] = z;
		}
	}

	for (i = 0; i < points; i++)
	{
		for (j = 0; j < points; j++)
		{
			vertIndex[4*(j*points+i)+0] = j*points+i;
			vertIndex[4*(j*points+i)+1] = j*points+((i+1)%points);
			vertIndex[4*(j*points+i)+2] = ((j+1)%points)*points+((i+1)%points);
			vertIndex[4*(j*points+i)+3] = ((j+1)%points)*points+i;
		}
	}

	colors[0] = 255;
	colors[1] = 0;
	colors[2] = 0;
	
	colors[3] = 255;
	colors[4] = 0;
	colors[5] = 0;

	colors[6] = 255;
	colors[7] = 0;
	colors[8] = 0;

	colors[9] = 255;
	colors[10] = 0;
	colors[11] = 0;

}

void drawSphere(int x_pos, int y_pos, int z_pos)
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
				
				vertices[3*(j*points+i)+0] = x;
				vertices[3*(j*points+i)+1] = y;
				vertices[3*(j*points+i)+2] = z;

				glVertex3f(vertices[3*(j*points+i)+0],
									 vertices[3*(j*points+i)+1], 
									 vertices[3*(j*points+i)+2]);

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

	drawSphere(0, 0, 0);
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	//glVertexPointer(3, GL_FLOAT, 0, vertices);
	//glColorPointer(3, GL_UNSIGNED_BYTE, 0, colors);
	//glDrawElements(GL_QUADS, points*4, GL_UNSIGNED_BYTE, vertIndex);

	glFlush();
	glutSwapBuffers();
}

void timer(int x)
{
	rotate_x = x + 0.25;
	rotate_y = x - 0.25;
	glutPostRedisplay();
	glutTimerFunc(1000/100, timer, 0);
}

int main(int argc, char **argv)
{
	vertices  = malloc(sizeof(GLfloat)*3*points*points);
	vertIndex = malloc(sizeof(GLubyte)*4*points*points);
	colors    = malloc(sizeof(GLubyte)*12);
	prepareVertices();

	glutInit(&argc, argv);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("Simple Polygon");
	glutTimerFunc(1000/60., timer, 0);
	glutDisplayFunc(display);
	glutMainLoop();
}



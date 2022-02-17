/* Compile code as: gcc hello.c -lGL -lglut */

#include<GL/glut.h>
#include<stdio.h>

void cross(GLfloat *a, GLfloat *b)
{
	float comp1 = a[1]*b[2] - a[2]*b[1];
	float comp2 = a[2]*b[0] - a[0]*b[2];
	float comp3 = a[0]*b[1] - a[1]*b[0];

	//printf("%f %f %f\n", comp1, comp2, comp3);
}

void polygonChecker(GLfloat *a, GLfloat *b, GLfloat *c)
{
	GLfloat my_edge[2][3] = { {b[0]-a[0], b[1]-a[1], b[2]-a[2]},
													 {c[0]-b[0], c[1]-b[1], c[2]-b[2]} };

	cross(my_edge[0], my_edge[1]);
}

void display()
{
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-1,2,-1,2);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	GLfloat my_vertex[6][3] = { {0,0,0}, {1,0,0}, {2,1,0}, {3, 0,0}, {3, 3,0}, {0, 3,0} };

	polygonChecker(my_vertex[0], my_vertex[1], my_vertex[2]);
	polygonChecker(my_vertex[1], my_vertex[2], my_vertex[3]);
	polygonChecker(my_vertex[2], my_vertex[3], my_vertex[4]);
	polygonChecker(my_vertex[3], my_vertex[4], my_vertex[5]);
	polygonChecker(my_vertex[4], my_vertex[5], my_vertex[0]);

	glBegin(GL_POLYGON);
		glVertex2fv(my_vertex[0]);
		glVertex2fv(my_vertex[1]);
		glVertex2fv(my_vertex[2]);
		glVertex2fv(my_vertex[3]);
		glVertex2fv(my_vertex[4]);
		glVertex2fv(my_vertex[5]);
	glEnd();
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("Simple Polygon");
	glutDisplayFunc(display);
	glutMainLoop();
}



/* Compile code as: gcc hello.c -lGL -lglut */

#include <GL/glut.h>
#include <stdio.h>
float rotate_y = 0;
float rotate_x = 0;

float FPS = 25;

GLfloat dx, dy, dz;
GLfloat l, r, t, b, n, f;
GLint nx, ny, nz;
GLfloat ***U;
GLfloat max = 0, min = 0;

void keyboard(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_RIGHT:	rotate_x += 10; break;
		case GLUT_KEY_LEFT:		rotate_x -= 10; break;
		case GLUT_KEY_UP:			rotate_y += 10; break;
		case GLUT_KEY_DOWN:		rotate_y -= 10; break;
	}

	glutPostRedisplay();
}

GLfloat points[8][3] = {	{0, 0,  0}, {1, 0,  0}, {1, 1,  0}, {0, 1,  0}, 
													{0, 0,  1}, {1, 0,  1}, {1, 1,  1}, {0, 1,  1} };

void quad (GLint n1, GLint n2, GLint n3, GLint n4)
{
	glBegin(GL_POLYGON);
		glVertex3f( points[n1][0]*dx, points[n1][1]*dy, points[n1][2]*dz );
		glVertex3f( points[n2][0]*dx, points[n2][1]*dy, points[n2][2]*dz );
		glVertex3f( points[n3][0]*dx, points[n3][1]*dy, points[n3][2]*dz );
		glVertex3f( points[n4][0]*dx, points[n4][1]*dy, points[n4][2]*dz );
	glEnd();
}

void cube(GLfloat r, GLfloat b, GLfloat g, GLfloat alpha)
{
	glColor4f(r, g, b, alpha);
	quad(0, 1, 2, 3);
	quad(4, 5, 6, 7);
	quad(2, 3, 7, 6);
	quad(0, 1, 5, 4);
	quad(1, 2, 6, 5);
	quad(3, 7, 4, 0);
}

GLfloat maxValue(GLfloat a, GLfloat b)
{
	if (a > b) return a;
	else			 return b;
}

void cubeMesh()
{
	int i, j, k;
	GLfloat r, g, b, ratio;
	glTranslatef(l, t, n);
	for (k = 0; k < nz; k++) {
		for (j = 0; j < ny; j++) {
			for (i = 0; i < nx; i++) {
				ratio = 2*(U[i][j][k] - min)/(double)(max-min);
				
				r = maxValue(0,ratio-1);
				b = maxValue(0,1-ratio);
				g = 1 - b - r;
			
				//glEnable(GL_BLEND);
				//glDepthMask(GL_FALSE);
				//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				cube(r, b, g, (k+1)*1/(double)dz);
					
				//glDepthMask(GL_TRUE);
				//glDisable(GL_BLEND);
				
				glTranslatef(dx, 0, 0);
			}
			glTranslatef(-dx*nx, 0, 0);
			glTranslatef(0, dy, 0);
		}
		glTranslatef(0, -dy*ny, 0);
		glTranslatef(0, 0, dz);
	}
	glTranslatef(0, 0, -dz*nz);
}

void display()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-5.,5.,-5,5.,-5.,5.);

	glRotatef( rotate_y, 1.0, 0.0, 0.0 );
	glRotatef( rotate_x, 0.0, 1.0, 0.0 );

	cubeMesh();

	glFlush();
	glutSwapBuffers();
}

void GLInit(GLfloat ll, GLfloat rr, GLfloat tt, GLfloat bb, GLfloat nn, GLfloat ff, GLint nxx, GLint nyy, GLint nzz)
{
	nx = nxx;
	ny = nyy;
	nz = nzz;

	l = ll;
	r = rr;
	b = bb;
	t = tt;
	n = nn;
	f = ff;

	dx = abs(r-l)/(double)nx;
	dy = abs(t-b)/(double)ny;
	dz = abs(f-n)/(double)nz;

	U = (GLfloat***)malloc(nx*sizeof(GLfloat**));
  int i, j, k;
  for (i = 0; i < nx ; i++) {
    U[i] = (GLfloat**)malloc(ny*sizeof(GLfloat*));
    for (j = 0; j < ny; j++) {
      U[i][j] = (GLfloat*)malloc(nz*sizeof(GLfloat));
    }
  }
	for (k = 0; k < nz; k++) {
		for (j = 0; j < ny; j++) {
			for (i = 0; i < nx; i++) {
				U[i][j][k] = 0;//rand()/(double)RAND_MAX;
			}
		}
	}
}


void timer(int x)
{
	int i, j, k;
	
	//for (i = -4; i < 5; i++) {
	//	for (j = -4; j < 5; j++) {
			U[nx/2][ny/2][nz/2] = 50;
	//	}
	//}

	#if 0
	GLfloat dt = 1/(double)(1000/(double)FPS);
	GLfloat dd;
	
	for (k = 0; k < nz; k++) {
		for (j = 0; j < ny; j++) {
			for (i = 0; i < nx; i++) { 

				//if (k == nz-1) {
					//dd = 384.1/0.5091/8940/dx/dx/dy/dy/dz/dz;
				//}
				//else {
					//dd = 0.6089/4.1813/997.0479/dx/dx/dy/dy/dz/dz;
					dd = 2.25/1133./921./dx/dx/dy/dy/dz/dz;
				//}

				if (k < nz/2) {
					if (j < ny/2) {
						if (i < nx/2)
							U[i][j][k] += dt*dd*(U[i+2][j][k] - 2*U[i+1][j][k] + U[i][j][k] +
																	 U[i][j+2][k] - 2*U[i][j+1][k] + U[i][j][k] + 
																	 U[i][j][k+2] - 2*U[i][j][k+1] + U[i][j][k]);
						else 
							U[i][j][k] += dt*dd*(U[i][j][k] - 2*U[i-1][j][k] + U[i-2][j][k] +
																	 U[i][j+2][k] - 2*U[i][j+1][k] + U[i][j][k] +
																	 U[i][j][k+2] - 2*U[i][j][k+1] + U[i][j][k]);
					}
					else {
						if (i < nx/2)
							U[i][j][k] += dt*dd*(U[i+2][j][k] - 2*U[i+1][j][k] + U[i][j][k] +
																	 U[i][j][k] - 2*U[i][j-1][k] + U[i][j-2][k] +
																	 U[i][j][k+2] - 2*U[i][j][k+1] + U[i][j][k]);

						else 
							U[i][j][k] += dt*dd*(U[i][j][k] - 2*U[i-1][j][k] + U[i-2][j][k] +
																	 U[i][j][k] - 2*U[i][j-1][k] + U[i][j-2][k] +
																   U[i][j][k+2] - 2*U[i][j][k+1] + U[i][j][k]);
					}
				}
				else {
					if (j < ny/2) {
						if (i < nx/2)
							U[i][j][k] += dt*dd*(U[i+2][j][k] - 2*U[i+1][j][k] + U[i][j][k] +
																	 U[i][j+2][k] - 2*U[i][j+1][k] + U[i][j][k] +
																	 U[i][j][k] - 2*U[i][j][k-1] + U[i][j][k-2]);
						else 
							U[i][j][k] += dt*dd*(U[i][j][k] - 2*U[i-1][j][k] + U[i-2][j][k] +
																	 U[i][j+2][k] - 2*U[i][j+1][k] + U[i][j][k] +
																	 U[i][j][k] - 2*U[i][j][k-1] + U[i][j][k-2]);
					}
					else {
						if (i < nx/2)
							U[i][j][k] += dt*dd*(U[i+2][j][k] - 2*U[i+1][j][k] + U[i][j][k] +
																	 U[i][j][k] - 2*U[i][j-1][k] + U[i][j-2][k] +
																	 U[i][j][k] - 2*U[i][j][k-1] + U[i][j][k-2]);

						else 
							U[i][j][k] += dt*dd*(U[i][j][k] - 2*U[i-1][j][k] + U[i-2][j][k] +
																	 U[i][j][k] - 2*U[i][j-1][k] + U[i][j-2][k] +
																	 U[i][j][k] - 2*U[i][j][k-1] + U[i][j][k-2]);
					}
				}

				if (U[i][j][k] > max) 
					max = U[i][j][k];
				if (U[i][j][k] < min)
					min = U[i][j][k];

	//			if (j == (ny - 1) && k == (nz - 1))
					//printf("%2.2f ", (U[0][0][0]-min)/(double)(max-min));
						fprintf(stderr, "%f\t%g\n", x*FPS/1000., U[nx/2+1][ny/2+1][nz/2+1]);
			}
		}
	}
#endif

	glutPostRedisplay();
	glutTimerFunc(1000/FPS, timer, x+1);
}

int main(int argc, char **argv)
{
	GLInit(-2, +2, -2, +2, -2, +2, 11, 11, 11);
	glutInit(&argc, argv);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("Simple Polygon");
	glutDisplayFunc(display);
	glutSpecialFunc(keyboard);
	glutTimerFunc(1000/FPS, timer, 0);
	glutMainLoop();
}



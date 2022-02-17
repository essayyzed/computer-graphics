/* Compile code as: gcc hello.c -lGL -lglut */

#include <GL/glut.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define ERROR(ERROR_MSG) \033[1;31mERROR_MSG\033[0m

struct sim_state
{
	/* Dimension Variables */
	double size_x;
	double size_y;
	double size_z;
	double nx, ny, nz;
	double dx, dy, dz;
	double mat_k; // thermal conductivity W/(m K)
	double mat_c; // Heat capacity J/(Kg K)
	double mat_r; // material density Kg / m^3
	double fps;
	double u_initial;
	double src_power;
	double dt;
	double left, right, bottom, top, near, far;
};

struct sim_state sim;

float rotate_y = 0;
float rotate_x = 0;

double ***U;
double ***T;
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
		glVertex3f( points[n1][0]*sim.dx, points[n1][1]*sim.dy, points[n1][2]*sim.dz );
		glVertex3f( points[n2][0]*sim.dx, points[n2][1]*sim.dy, points[n2][2]*sim.dz );
		glVertex3f( points[n3][0]*sim.dx, points[n3][1]*sim.dy, points[n3][2]*sim.dz );
		glVertex3f( points[n4][0]*sim.dx, points[n4][1]*sim.dy, points[n4][2]*sim.dz );
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
	glTranslatef(sim.left, -sim.top, sim.near);
	for (k = 0; k < sim.nz; k++) {
		for (j = 0; j < sim.ny; j++) {
			for (i = 0; i < sim.nx; i++) {
				ratio = 2*(U[i][j][k] - min)/(double)(max-min);
				
				r = maxValue(0,ratio-1);
				b = maxValue(0,1-ratio);
				g = 1 - b - r;
			
				if (k == 0 || j == 0 || i == 0 || k == sim.nz-1 || j == sim.ny-1 || i == sim.nx-1) {
					glEnable(GL_BLEND);
					glDepthMask(GL_FALSE);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				}

				glPushMatrix();
					glutSolidCube(sim.dx/8.);
				glPopMatrix();

				// cube(r, b, g, (k+1)*1/(double)sim.dz);
					
				if (k == 0 || j == 0 || i == 0 || k == sim.nz-1 || j == sim.ny-1 || i == sim.nx-1) {
					glDepthMask(GL_TRUE);
					glDisable(GL_BLEND);
				}
				
				glTranslatef(sim.dx, 0, 0);
			}
			glTranslatef(-sim.dx*sim.nx, 0, 0);
			glTranslatef(0, sim.dy, 0);
		}
		glTranslatef(0, -sim.dy*sim.ny, 0);
		glTranslatef(0, 0, sim.dz);
	}
	glTranslatef(0, 0, -sim.dz*sim.nz);
}

void drawAxes()
{
		glPushMatrix();
		glTranslatef(-4, -4, 0);

    glLineWidth( 1 );
    glBegin(GL_LINES);
				glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-2, -2, 5);
        glVertex3f(-1, -2, 5);
		glEnd();
		glTranslatef(-1, -2, 5);
		glRotatef(90, 0, 1, 0);
		glutWireCone(0.25, 0.25, 5, 5);
		glRasterPos3f(0, 0, 0);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, "x");
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-4, -4, 0);
		glBegin(GL_LINES);
				glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-2, -2, 5);
				glVertex3f(-2, -1, 5);
		glEnd();
		glTranslatef(-2, -1, +5);
		glRotatef(-90, 1, 0, 0);
		glutWireCone(0.25, 0.25, 5, 5);
		glRasterPos3f(0, 0, 0);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, "y");
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-4, -4, 0);
		glBegin(GL_LINES);
				glColor3f(0.0f, 0.0f, 1.0f);
				glVertex3f(-2, -2, 5);
				glVertex3f(-2, -2, 4);
    glEnd();
		glTranslatef(-2, -2, 4);
		glRotatef(-90, 0, 0, 1);
		glutWireCone(0.25, 0.25, 5, 5);
		glPopMatrix();

		glPushMatrix();
		glLineWidth(1);
    glBegin(GL_LINES);
				glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-100, 0, 0);
        glVertex3f(+100, 0, 0);
				glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f( 0, -100, 0);
				glVertex3f( 0, +100, 0);
				glColor3f(0.0f, 0.0f, 1.0f);
				glVertex3f( 0,  0, -100);
				glVertex3f( 0,  0, +100);
    glEnd();
		glPopMatrix();
}

void display()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glOrtho(-sim.left*10.,sim.right*10.,-sim.bottom*5,sim.top*5.,-sim.near*5.,sim.far*5.);
	glOrtho(-7, 7, -7, 7, -70, 70);
	
	glRotatef( rotate_y, 1.0, 0.0, 0.0 );
	glRotatef( rotate_x, 0.0, 1.0, 0.0 );

	drawAxes();
	cubeMesh();

	glFlush();
	glutSwapBuffers();
}

void GLInit(struct sim_state *sim)
{
	sim->dx = (double)((sim->right-sim->left)/(double)(sim->nx));
	sim->dy = (double)((sim->top  -sim->bottom)/(double)(sim->ny));
	sim->dz = (double)((sim->far  -sim->near)/(double)(sim->nz));

	U = (double***)malloc(sim->nx*sizeof(double**));
	T = (double***)malloc(sim->nx*sizeof(double**));
  int i, j, k;
  for (i = 0; i < sim->nx ; i++) {
    U[i] = (double**)malloc(sim->ny*sizeof(double*));
    T[i] = (double**)malloc(sim->ny*sizeof(double*));
    for (j = 0; j < sim->ny; j++) {
      U[i][j] = (double*)malloc(sim->nz*sizeof(double));
      T[i][j] = (double*)malloc(sim->nz*sizeof(double));
    }
  }
	for (k = 0; k < sim->nz; k++) {
		for (j = 0; j < sim->ny; j++) {
			for (i = 0; i < sim->nx; i++) {
				U[i][j][k] = T[i][j][k] = sim->u_initial;
			}
		}
	}
}


void timer(int x)
{
	int i, j, k;

	//for (i = -4; i < 5; i++) {
	//	for (j = -4; j < 5; j++) {
			T[(int)(sim.nx/2)][(int)(sim.ny/2)][(int)(sim.nz/2)] = sim.src_power;
	//	}
	//}

	GLfloat dd;
	
	for (k = 0; k < sim.nz; k++) {
		for (j = 0; j < sim.ny; j++) {
			for (i = 0; i < sim.nx; i++) { 

				dd = sim.dt * sim.mat_k / sim.mat_c / sim.mat_r / sim.dx/sim.dx/sim.dy/sim.dy/sim.dz/sim.dz;
#if 1
				if (k == 0 || j == 0 || i == 0 || k == sim.nz-1 || j == sim.ny-1 || i == sim.nx-1) {
					U[i][j][k] = 0;
				} else  {
					U[i][j][k] = T[i][j][k] + dd*(T[i+1][j][k] - 2*T[i][j][k] + T[i-1][j][k] +
							                          T[i][j+1][k] - 2*T[i][j][k] + T[i][j-1][k] +
																				T[i][j][k+1] - 2*T[i][j][k] + T[i][j][k-1]);
					
					if (U[i][j][k] > max) 
						max = U[i][j][k];
					if (U[i][j][k] < min)
						min = U[i][j][k];
				}
#endif

#if 0
				if (k < sim.nz/2) {
					if (j < sim.ny/2) {
						if (i < sim.nx/2)
							U[i][j][k] = T[i][j][k] + dd*(T[i+2][j][k] - 2*T[i+1][j][k] + T[i][j][k] +
																	 T[i][j+2][k] - 2*T[i][j+1][k] + T[i][j][k] + 
																	 T[i][j][k+2] - 2*T[i][j][k+1] + T[i][j][k]);
						else 
							U[i][j][k] = T[i][j][k] +  dd*(T[i][j][k] - 2*T[i-1][j][k] + T[i-2][j][k] +
																	 T[i][j+2][k] - 2*T[i][j+1][k] + T[i][j][k] +
																	 T[i][j][k+2] - 2*T[i][j][k+1] + T[i][j][k]);
					}
					else {
						if (i < sim.nx/2)
							U[i][j][k] = T[i][j][k] + dd*(T[i+2][j][k] - 2*T[i+1][j][k] + T[i][j][k] +
																	 T[i][j][k] - 2*T[i][j-1][k] + T[i][j-2][k] +
																	 T[i][j][k+2] - 2*T[i][j][k+1] + T[i][j][k]);

						else 
							U[i][j][k] = T[i][j][k] + dd*(T[i][j][k] - 2*T[i-1][j][k] + T[i-2][j][k] +
																	 T[i][j][k] - 2*T[i][j-1][k] + T[i][j-2][k] +
																	 T[i][j][k+2] - 2*T[i][j][k+1] + T[i][j][k]);
					}
				}
				else {
					if (j < sim.ny/2) {
						if (i < sim.nx/2)
							U[i][j][k] = T[i][j][k] + dd*(T[i+2][j][k] - 2*T[i+1][j][k] + T[i][j][k] +
																	 T[i][j+2][k] - 2*T[i][j+1][k] + T[i][j][k] +
																	 T[i][j][k] - 2*T[i][j][k-1] + T[i][j][k-2]);
						else 
							U[i][j][k] = T[i][j][k] + dd*(T[i][j][k] - 2*T[i-1][j][k] + T[i-2][j][k] +
																	 T[i][j+2][k] - 2*T[i][j+1][k] + T[i][j][k] +
																	 T[i][j][k] - 2*T[i][j][k-1] + T[i][j][k-2]);
					}
					else {
						if (i < sim.nx/2)
							U[i][j][k] = T[i][j][k] + dd*(T[i+2][j][k] - 2*T[i+1][j][k] + T[i][j][k] +
																	 T[i][j][k] - 2*T[i][j-1][k] + T[i][j-2][k] +
																	 T[i][j][k] - 2*T[i][j][k-1] + T[i][j][k-2]);

						else 
							U[i][j][k] = T[i][j][k] + dd*(T[i][j][k] - 2*T[i-1][j][k] + T[i-2][j][k] +
																	 T[i][j][k] - 2*T[i][j-1][k] + T[i][j-2][k] +
																	 T[i][j][k] - 2*T[i][j][k-1] + T[i][j][k-2]);
					}
				}
#endif

			}
		}
	}
	for (k = 0; k < sim.nz; k++) {
		for (j = 0; j < sim.ny; j++) {
			for (i = 0; i < sim.nx; i++) { 
				if (k == 0 || k == sim.nz-1 || j == 0 || j == sim.ny-1 || i == 0 || i == sim.nx-1) {
					U[i][j][k] = 0;
				}
				T[i][j][k] = U[i][j][k];
			}
		}
	}



	if ( x % 1000 == 0) { //(int)(x * 1000./sim.fps) % 1000 == 0) {
		fprintf(stdout, "x: %2.2f \t ", x*sim.dt);
		for (i = 0; i < sim.nx/2; i++) {
			fprintf(stdout, "%g ", U[(int)(sim.nx/2+i)][(int)(sim.ny/2)][(int)(sim.nz/2)]);
			fprintf(stderr, "%g\t", U[(int)(sim.nx/2+i)][(int)(sim.ny/2)][(int)(sim.nz/2)]);
		}
		fprintf(stdout, "\n");
		fprintf(stderr, "\n");
	}

	glutPostRedisplay();
	glutTimerFunc(1000/sim.fps, timer, x+1);
}

void whiteWash()
{
	int i, j, k;

	for (k = 0; k < sim.nz; k++) {
		for (j = 0; j < sim.ny; j++) {
			for (i = 0; i < sim.nx; i++) {
				U[i][j][k] = 0;//rand()/(double)RAND_MAX;
			}
		}
	}
}

void fillOption(GLint selectedOption)
{
	switch(selectedOption)
	{
		case 1: whiteWash(); break;
	}
	glutPostRedisplay();
}

void removeSpaces(char *str)
{
	int count = 0; 
	for (int i = 0; str[i]; i++)
		if (str[i] != ' ')
			str[count++] = str[i];
  str[count] = '\0';
}

struct sim_state getValues()
{
	char infile[]="input";
	char *line, *linetmp;
	size_t len = 0;
	FILE *fd = fopen(infile, "r");
	char *category;
	char *variable;
	char *valuefull;
	char *value;
	char *units;

	struct sim_state tmp;
	
	if (fd == NULL) {
		printf("\033[1;31mFile 'input' not found. Exiting\033[0m\n");
	} else {
		ssize_t read;
		int count = 0;
		char *remain;
		while ((read = getline(&line, &len, fd)) != -1) {
			count++;
			if ((strcmp(line, "\n") != 0) && (line[0] != '#') ) {
				linetmp = calloc(sizeof(char),read);
				memcpy(linetmp, line, read-1);
				category = strtok_r(line, ":", &remain);
				removeSpaces(category);
				variable = strtok_r(remain, "=", &remain);
				removeSpaces(variable);
				value    = strtok_r(remain, "!", &remain);
				removeSpaces(value);
				units     = strtok_r(remain, "\n", &remain);
				if (units != NULL) {
					removeSpaces(units);
				}
				if (strcmp(variable, "system-size-x") == 0) { 
					tmp.size_x = atof(value);
					tmp.left   = -tmp.size_x/2.;
					tmp.right  =  tmp.size_x/2.;
				} else if (strcmp(variable, "system-size-y") == 0) {
					tmp.size_y = atof(value);
					tmp.bottom = -tmp.size_y/2.;
					tmp.top    =  tmp.size_y/2.;
				} else if (strcmp(variable, "system-size-z") == 0) {
					tmp.size_z = atof(value);
					tmp.near   = -tmp.size_z/2.;
					tmp.far    =  tmp.size_z/2.;
				} else if (strcmp(variable, "unit-cells-x") == 0) {
					tmp.nx = atof(value);
				} else if (strcmp(variable, "unit-cells-y") == 0) {
					tmp.ny = atof(value);
				} else if (strcmp(variable, "unit-cells-z") == 0) {
					tmp.nz = atof(value);
				} else if (strcmp(variable, "unit-cells") == 0) {
					tmp.nx = tmp.ny = tmp.nz = atof(value);
				} else if (strcmp(variable, "thermal-conductivity") == 0) {
					tmp.mat_k = atof(value);
				} else if (strcmp(variable, "heat-capacity") == 0) {
					tmp.mat_c = atof(value);
				} else if (strcmp(variable, "material-density") == 0) {
					tmp.mat_r = atof(value);
				} else if (strcmp(variable, "fps") == 0) {
					tmp.fps   = atof(value);
				} else if (strcmp(variable, "initial-heat") == 0) {
					tmp.u_initial = atof(value);
				} else if (strcmp(variable, "heat-source-power") == 0) {
					tmp.src_power = atof(value);
				} else if (strcmp(variable, "dt") == 0) {
					tmp.dt = atof(value);
				} else {
					printf("\033[1;31mUnrecognized Command '%s' on line %d\033[0m\n", linetmp, count);
				}
			}
		}
		fclose(fd);
	}

	return tmp;
}

int main(int argc, char **argv)
{
	sim = getValues();
	GLInit(&sim);

	printf("left: %f, right: %f, bottom: %f, top: %f, near: %f, far: %f\n", sim.left, sim.right, sim.bottom, sim.top, sim.near, sim.far);
	printf("nx: %f, ny: %f, nz: %f, dt: %f, dx: %g, dy: %g, dz: %g, k: %g k_full: %g\n", sim.nx, sim.ny, sim.nz, sim.dt, sim.dx, sim.dy, sim.dz, sim.mat_k / sim.mat_c / sim.mat_r, sim.dt*sim.mat_k/sim.mat_c/sim.mat_r/sim.dx/sim.dx/sim.dy/sim.dy/sim.dz/sim.dz);

	glutInit(&argc, argv);
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(300, 300);
	glutCreateWindow("Simple Polygon");
	glutDisplayFunc(display);
	glutCreateMenu(fillOption);
		glutAddMenuEntry("Restart", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutSpecialFunc(keyboard);
	glutTimerFunc(1000/sim.fps, timer, 0);
	
	glutMainLoop();
}



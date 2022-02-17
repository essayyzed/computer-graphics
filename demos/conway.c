#include <stdio.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

/* Compile Instructions 
 gcc square.c -lGLEW -lglut*/

int leftButton = 0;
int downX, downY;
float sphi=90.0, stheta=45.0;
float aspect = 5.0/4.0;
float xcam = 0, ycam = 0;
long xsize, ysize;
int n_x, n_y;
float dx, dy;

int win_x = 300;
int win_y = 300;

int n_x = 50;
int n_y = 50;

int **cells;
int **cellsb;

/* Timer */
float FPS = 25;
float T   = 10;
float t   = 0;
float dt;


void display()
{
	int i, j;
	for (j = 0; j < n_y; j++) {
		for (i = 0; i < n_x; i++) {
			if (cells[i][j] == 0) {
				glColor3f(1, 1, 1);
			} else {
				glColor3f(0,0,0);
			}
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glBegin(GL_POLYGON);  
				glVertex2f(-1+i*dx, 	-1+j*dy);
				glVertex2f(-1+i*dx+dx,  -1+j*dy);
				glVertex2f(-1+i*dx+dx,  -1+j*dy+dy);
				glVertex2f(-1+i*dx, 	-1+j*dy+dy);
				glVertex2f(-1+i*dx, 	-1+j*dy);
			glEnd();             
			glFlush();           
			glutSwapBuffers();
		}
	}
}

void timer()
{
	int i,j;
	t += dt;
	int liveN = 0;
	for (j = 0; j < n_y; j++) {
		for (i = 0; i < n_x; i++) {
			liveN = 0;
			
			if ((i == 0) && (j == 0)) {
		    	if (cells[i+1][j] == 1) liveN++;
				if (cells[i][j+1] == 1) liveN++;
				if (cells[i+1][j+1] == 1) liveN++;
		  	}
		  	else if ((i == n_x-1) && (j == 0)) {
				if (cells[i-1][j] == 1) liveN++;
				if (cells[i-1][j+1] == 1) liveN++;
				if (cells[i][j+1] == 1) liveN++;
		 	}
			else if (((i > 0) && (i < n_x)) && (j == 0)) {
				if (cells[i-1][j] == 1) liveN++;
				if (cells[i+1][j] == 1) liveN++;
				if (cells[i-1][j+1] == 1) liveN++;
				if (cells[i][j+1] == 1) liveN++;
				if (cells[i+1][j+1] == 1) liveN++;
			}
			else if ((i == 0) && (j == n_y-1)) {
			    if (cells[i+1][j] == 1) liveN++;
				if (cells[i][j-1] == 1) liveN++;
				if (cells[i+1][j-1] == 1) liveN++;
		  	}
			else if ((i == n_x-1) && (j == n_y-1)) {
				if (cells[i-1][j] == 1) liveN++;
				if (cells[i-1][j-1] == 1) liveN++;
				if (cells[i][j-1] == 1) liveN++;
		  	}
		  	else if (((i > 0) && (i < n_x)) && (j == n_y-1)) {
				if (cells[i-1][j] == 1) liveN++;
				if (cells[i+1][j] == 1) liveN++;
				if (cells[i-1][j-1] == 1) liveN++;
				if (cells[i+1][j-1] == 1) liveN++;
				if (cells[i][j-1] == 1) liveN++;
		  	}
		  	else if ((i == 0) && (j > 0 && j < n_y-1)) {
		   		if (cells[i][j+1] == 1) liveN++;
				if (cells[i][j-1] == 1) liveN++;
				if (cells[i+1][j+1] == 1) liveN++;
				if (cells[i+1][j-1] == 1) liveN++;
				if (cells[i+1][j] == 1) liveN++;
		 	}
		  	else if ((i == n_x-1) && (j > 0 && j < n_y-1)) {
				if (cells[i][j+1] == 1) liveN++;
				if (cells[i][j-1] == 1) liveN++;
				if (cells[i-1][j+1] == 1) liveN++;
				if (cells[i-1][j-1] == 1) liveN++;
				if (cells[i-1][j] == 1) liveN++;
		  	}
		  	else if (((i > 0) && (i < n_x)) && (j > 0 && j < n_y-1)) {
				if (cells[i-1][j-1] == 1) liveN++;
				if (cells[i][j-1] == 1) liveN++;
				if (cells[i+1][j-1] == 1) liveN++;
				if (cells[i-1][j] == 1) liveN++;
				if (cells[i+1][j] == 1) liveN++;
				if (cells[i-1][j+1] == 1) liveN++;
				if (cells[i][j+1] == 1) liveN++;
				if (cells[i+1][j+1] == 1) liveN++;
		  	}	

		  	if (cells[i][j] == 1) {
				if (liveN < 2 || liveN > 3) cellsb[i][j] = 0;
				if (liveN == 2 || liveN == 3) cellsb[i][j] = 1;
		  	}
		  	else {
				if (liveN == 3) cellsb[i][j] = 1;	
				else cellsb[i][j] = 0;
			}
		}
	}
	for (j = 0; j < n_y; j++) {
		for (i = 0; i < n_x; i++) {
			cells[i][j] = cellsb[i][j];
		}
	}

	glutPostRedisplay();
	if (t*1e-3 < T) 
		glutTimerFunc(dt, timer, 0);
}

int main(int argc, char **argv)
{
   	glutInit(&argc, argv);                // Initializes GLUT Toolkit
   	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE| GLUT_DEPTH);
   	glutInitWindowSize(win_x, win_y);         // Creates a Window with size/pos
   	glutInitWindowPosition(0, 0);
   	glutCreateWindow("Conway Game of Life");   
   	glutDisplayFunc(display);             // Register the call back routine
                                         // everytime the window updates
  
	int i, j;
	cells = malloc(sizeof(int*)*n_y);
	cellsb = malloc(sizeof(int*)*n_y);
	for (i = 0; i < n_x; i++) {
		cells[i] = malloc(sizeof(int)*n_x);
		cellsb[i] = malloc(sizeof(int)*n_x);
	}

	dx = 2./n_x;
	dy = 2./n_y;

	for (j = 0; j < n_y; j++) {
		for (i = 0; i < n_x; i++) {
			cells[i][j] = 0;
			//if (i == j) 
			//	cells[i][j] = 1;
		}
	}
	
	/* Toad */
	cells[4][23] = 1;
	cells[5][23] = 1;
	cells[6][23] = 1;
	cells[3][24] = 1;
	cells[4][24] = 1;
	cells[5][24] = 1;


	/* Switch Engine 
	.O.O..
	O.....
	.O..O.
	...OOO
	*/
	cells[10][10] = 1;
	cells[9][11] = 1;
	cells[10][12] = 1;
	cells[12][10] = 1;
	cells[13][12] = 1;
	cells[13][13] = 1;
	cells[12][13] = 1;
	cells[14][13] = 1;

	/* Spark Coil
	OO....OO
	O.O..O.O
	..O..O..
	O.O..O.O
	OO....OO*/
	cells[4][22] = 1;
	cells[5][22] = 1;
	cells[4][23] = 1;
	cells[6][23] = 1;
	cells[6][24] = 1;
	cells[4][25] = 1;
	cells[6][25] = 1;
	cells[4][26] = 1;
	cells[5][26] = 1;

	cells[10][22] = 1;
	cells[11][22] = 1;
	cells[9][23] = 1;
	cells[11][23] = 1;
	cells[9][24] = 1;
	cells[9][25] = 1;
	cells[11][25] = 1;
	cells[10][26] = 1;
	cells[11][26] = 1;

	/* Pentomino 
	..OO
	OOO.	
	*/
	cells[35][35] = 1;
	cells[36][35] = 1;
	cells[35][36] = 1;
	cells[34][36] = 1;
	cells[33][36] = 1;

	/* Stair step
	..OO
	.OO.
	OO..*/
	cells[35][10] = 1;
	cells[34][10] = 1;
	cells[34][11] = 1;
	cells[33][11] = 1;
	cells[33][12] = 1;
	cells[32][12] = 1;

	/* Space Ship
	OO.
	O.O
	.OO*/
	cells[10][35] = 1;
	cells[11][35] = 1;
	cells[10][36] = 1;
	cells[12][36] = 1;
	cells[11][37] = 1;
	cells[12][37] = 1;

	dt = 1000/FPS;
	glutTimerFunc(dt, timer, 0);
	glutMainLoop(); 
}


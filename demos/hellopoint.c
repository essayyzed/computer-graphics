#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#define POINTS_TOTAL 1

struct Point {
	float x[3];
};

struct Point points[POINTS_TOTAL];

/* Viewer state */
float sphi = 0, stheta = 0.0;
float sdepth = 10;
float zNear = 1.0, zFar = 100;
float aspect = 5.0 / 4.0;
float xcam = 0, ycam = 0;
long xsize, ysize;
int downX, downY, leftButton = 0, middleButton = 0, i, j;
GLfloat light0Position[] = { 0, 1, 0, 1.0 };
int displayMenu, mainMenu;
enum { FLATSHADED};
int displayMode = FLATSHADED;

/* Timer */
float FPS = 25.;
float T   = 5;
float t   = 0;
float dt;

void displayAxesLowerLeft()
{
	glViewport(20, 20, 60, 60);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    //gluPerspective(64.0f, aspect, zNear, zFar);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glEnable( GL_LINE_SMOOTH );
    glLineWidth( 2 );
    glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(25.0f,0.0f,0.0f);
	
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,25.0f,0.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,25.0f);
    glEnd();

	glViewport(0,0,xsize,ysize);
	glLineWidth( 1 );


	glBegin(GL_LINE_STRIP);
		glVertex3f(0.0f, 0.0f, -30.0f);
		glVertex3f(30.0f, 0.0f, -30.0f);
		glVertex3f(30.0f, 30.0f, -30.0f);
		glVertex3f(0.0f, 30.0f, -30.0f);
		glVertex3f(0.0f, 0.0f, -30.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(30.0f, 0.0f, 0.0f);
		glVertex3f(30.0f, 30.0f, 0.0f);
		glVertex3f(0.0f, 30.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(30.0f, 0.0f, 0.0f);
		glVertex3f(30.0f, 0.0f, -30.0f);
		glVertex3f(30.0f, 30.0f, -30.0f);
		glVertex3f(30.0f, 30.0f, 0.0f);
		glVertex3f(0.0f, 30.0f, 0.0f);
		glVertex3f(0.0f, 30.0f, -30.0f);
	glEnd();


    //Restore View
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glViewport(0, 0, xsize, ysize);
}

void DrawFlatShaded(void)
{
	int i;
	glEnable(GL_POLYGON_OFFSET_FILL);
	glColor3f(0.8f, 0.2f, 0.8f);
	glPointSize(16);
	glBegin(GL_POINTS);
	for (i = 0; i < POINTS_TOTAL ; ++i) {
		glVertex3fv(points[i].x);
	}
	glEnd();
	glDisable(GL_POLYGON_OFFSET_FILL);


	displayAxesLowerLeft();
}

void ReshapeCallback(int width, int height)
{
	xsize = width;
	ysize = height;
	aspect = (float)xsize / (float)ysize;
	glViewport(0, 0, xsize, ysize);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutPostRedisplay();
}

void SetDisplayMenu(int value)
{
	displayMode = value;

	switch (value) {
	case FLATSHADED:
		glShadeModel(GL_FLAT);
		glEnable(GL_LIGHTING);
		break;
	}
	glutPostRedisplay();
}

void SetMainMenu(int value)
{
	switch (value) {
	case 99:
		exit(0);
		break;
	}
}

void DisplayCallback(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(128.0, aspect, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-10.0f, -10.0f, -sdepth);
	glRotatef(-stheta, 1.0, 0.0, 0.0);
	glRotatef(sphi, 0.0, 0.0, 1.0);

	switch (displayMode) {

	case FLATSHADED:
		DrawFlatShaded();
		break;
	}

	glutSwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MouseCallback(int button, int state, int x, int y)
{

	downX = x;
	downY = y;

	leftButton = ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN));
	middleButton = ((button == GLUT_MIDDLE_BUTTON) && (state == GLUT_DOWN));

	glutPostRedisplay();
}

void MotionCallback(int x, int y)
{
	if (leftButton) {
		sphi += (float)(x - downX) / 4.0;
		stheta += (float)(downY - y) / 4.0;
	}			// rotate
	if (middleButton) {
		sdepth += (float)(downY - y) / 10.0;
	}			// scale

	downX = x;
	downY = y;

	glutPostRedisplay();
}

void InitMenu()
{
	displayMenu = glutCreateMenu(SetDisplayMenu);
	glutAddMenuEntry("Flat Shaded", FLATSHADED);
	mainMenu = glutCreateMenu(SetMainMenu);
	glutAddSubMenu("Display", displayMenu);
	glutAddMenuEntry("Exit", 99);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void timer()
{
	int i;
	t += dt;
	printf("%f\t%d %d %d\t", t*1e-3,(int)(points[0].x[0]), (int)(points[0].x[1]), (int)(points[0].x[2]));
	printf("%d %d %d\t", (int)(points[4].x[0]), (int)(points[4].x[1]), (int)(points[4].x[2]));
	printf("%d %d %d\n", (int)(points[9].x[0]), (int)(points[9].x[1]), (int)(points[9].x[2]));
	for (i = 0; i < POINTS_TOTAL; i++) {
		if (points[i].x[1] > 0) {
			points[i].x[1]--;
		}
	}
	glutPostRedisplay();
	if (t*1e-3 < T) 
		glutTimerFunc(dt, timer, 0);
}

void InitGL()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Modeling and Simulation");
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glDisable(GL_CULL_FACE);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
	glEnable(GL_LIGHT0);
	glutReshapeFunc(ReshapeCallback);
	glutDisplayFunc(DisplayCallback);
	glutMouseFunc(MouseCallback);
	glutMotionFunc(MotionCallback);

	dt = 1000/FPS;
	glutTimerFunc(dt, timer, 0);

	InitMenu();
}


void InitGeometry()
{
	int i;
	for (i = 0; i < POINTS_TOTAL; i++) {
		points[i].x[0] = rand()%30;
		points[i].x[1] = rand()%30;
		points[i].x[2] = -1*(rand()%30);
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	InitGL();
	InitGeometry();
	glutMainLoop();
}

#include <GL/glut.h>

#define SUN_RADIUS 0.4
#define EARTH_RADIUS 0.06
#define MOON_RADIUS 0.016

GLfloat EARTH_ORBIT_RADIUS = 0.9;
GLfloat year = 0.0;

void renderScene()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho( -1, 1, -1, 1, -100, 100 );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt
        (
        0.0, 0.0, -4.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
        );

    glColor3f(1.0, 1.0, 0.7);
    glutWireSphere(SUN_RADIUS, 50, 50);

    glPushMatrix();
    glRotatef(year, 0.0, 1.0, 0.0);
    glTranslatef(EARTH_ORBIT_RADIUS, 0.0, 0.0);
    glColor3f(0.0, 0.7, 1.0);
    glutWireSphere(EARTH_RADIUS, 10, 10);
    glPopMatrix();
}

void display()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(10.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderScene();
    glutSwapBuffers();
}

void idle()
{
    year += 0.2;
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Solar System");

    glutDisplayFunc(display);
    glutIdleFunc( idle );

    glutMainLoop();
}

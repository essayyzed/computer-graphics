/* Compile code as: gcc hello.c -lGL -lglut */

#include<GL/glut.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float rotate_y = 0;
float rotate_x = 0;
int width, height, nrChannels;
GLubyte *data;
GLuint texture_id;

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

GLfloat points[8][3] = {	{0, 0, 0}, {.5, 0, 0}, {.5, .5, 0}, {0, .5, 0}, 
													{0, 0, .5}, {.5, 0, .5}, {.5, .5, .5}, {0, .5, .5} };

void quad (GLint n1, GLint n2, GLint n3, GLint n4)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0);
		glVertex3fv( points[n1] );
		glTexCoord2f(1.0, 0.0);
		glVertex3fv( points[n2] );
		glTexCoord2f(1.0, 1.0);
		glVertex3fv( points[n3] );
		glTexCoord2f(0.0, 1.0);
		glVertex3fv( points[n4] );
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

GLfloat texCoords[] = {
    0.0f, 0.0f,
    0.5f, 0.0f,
    0.5f, 0.5f,
    0.0f, 0.5f
};


void display()
{
#if 0
	/* Lighting Part Starts */
	glEnable(GL_LIGHTING);
	
	GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat black[] = {0.0, 0.0, 0.0, 1.0};
	glLightfv(GL_LIGHT1, GL_AMBIENT, white);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);

	GLfloat light1Position[4] = {1.0, 1.0, 1.0, 10.0};
	glLightfv(GL_LIGHT1, GL_POSITION, light1Position);
	glEnable(GL_LIGHT1);

	glEnable(GL_FOG);
	GLfloat atmo[] ={0.8, 0.8, 1.0, 1.0};
	glFogfv(GL_FOG_COLOR, atmo);
	/* Lighting Part Ends */
#endif

	
	glRotatef( rotate_y, 1.0, 0.0, 0.0 );
	glRotatef( rotate_x, 0.0, 1.0, 0.0 );

	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//glColor3f(1.0, 0.0, 0.0);
	quad(0, 1, 2, 3);
	
	//glColor3f(0.0, 1.0, 0.0);
	quad(4, 5, 6, 7);

	//glColor3f(0.0, 0.0, 1.0);
	quad(2, 3, 7, 6);

	//glColor3f(1.0, 1.0, 0.0);
	quad(0, 1, 5, 4);

	//glColor3f(1.0, 0.0, 1.0);
	quad(1, 2, 6, 5);

	//glColor3f(0.0, 1.0, 1.0);
	quad(3, 7, 4, 0);

  glFlush();
	//glutSwapBuffers();	
}

void init()
{
	data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 1, GL_RGBA, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_BLEND);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("Simple Polygon");
	glutDisplayFunc(display);
	glutSpecialFunc(keyboard);
	init();
	glutMainLoop();
	stbi_image_free(data);
}



/* Compile code as: gcc hello.c -lGL -lglut */

#include<GL/glut.h>
#include<stdio.h>

float rotate_y = 0;
float rotate_x = 0;

int getFileSize(char *f)
{
	FILE *fptr = fopen(f, "r");
  if (fptr == NULL) {
		printf("Cannot open file \n");
    exit(0);
	}
	fseek(fptr, 0, SEEK_END);
	int size = ftell(fptr);
	fclose(fptr);
	return size;
}

void readFile(char *s, char *f)
{
	FILE *fptr = fopen(f, "r");
  if (fptr == NULL) {
		printf("Cannot open file \n");
    exit(0);
	}
	char ch;
	int i = 0;
	
	ch = fgetc(fptr);
	while (ch != EOF)
	{
		s[i++] = ch;
    ch = fgetc(fptr);
	}
	fclose(fptr);
}

void prepareShader()
{
	int fsize = getFileSize("nu_shader.vs");
	char *source = malloc(sizeof(char)*fsize);
	readFile(source, "nu_shader.vs");

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSourceARB(vs, 1, &source, &fsize);
	glCompileShaderARB(vs);
	GLint status;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
	if (status) {
		printf("compiled\n");
	}
	int program = glCreateProgram();
	glAttachShader(program, vs);
	glLinkProgram(program);
	glGetProgramiv(vs, GL_LINK_STATUS, &status);
	if (status) {
		printf("linked\n");
	}
	glUseProgram(program);
}

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

void display()
{
	glRotatef( rotate_y, 1.0, 0.0, 0.0 );
	glRotatef( rotate_x, 0.0, 1.0, 0.0 );

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_POLYGON);
		glColor3f(   1.0,  1.0, 1.0 );
		glVertex3f( -0.5, -0.5, 0.5 );
		glVertex3f(  0.5, -0.5, 0.5 );
		glVertex3f(  0.5,  0.5, 0.5 );
		glVertex3f( -0.5,  0.5, 0.5 );
	glEnd();

	glBegin(GL_POLYGON);
		glColor3f(   0.0,  1.0, 1.0 );
		glVertex3f( -0.5, -0.5, -0.5 );
		glVertex3f(  0.5, -0.5, -0.5 );
		glVertex3f(  0.5,  0.5, -0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
	glEnd();

	glBegin(GL_POLYGON);
		glColor3f(   0.0,  0.0, 1.0 );
		glVertex3f(  0.5, -0.5, 0.5 );
		glVertex3f(  0.5,  0.5, 0.5 );
		glVertex3f(  0.5,  0.5, -0.5 );
		glVertex3f(  0.5, -0.5, -0.5 );
	glEnd();

	glBegin(GL_POLYGON);
		glColor3f(   0.0,  0.0, 1.0 );
		glVertex3f( -0.5,  0.5, 0.5 );
		glVertex3f(  0.5,  0.5, 0.5 );
		glVertex3f(  0.5,  0.5, -0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
	glEnd();

	glFlush();
	glutSwapBuffers();	
	glFlush();
}



int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("Simple Polygon");
	glutDisplayFunc(display);
	glutSpecialFunc(keyboard);
	printf("%s\n", glGetString(GL_VERSION));
	prepareShader();
	glutMainLoop();
}



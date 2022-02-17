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

void ReshapeCallback(int width, int height) {
  xsize = width;
  ysize = height;
  aspect = (float)xsize/(float)ysize;
  glViewport(0, 0, xsize, ysize);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glutPostRedisplay();
}

void MouseCallback(int button, int state, int x, int y) {
  downX = x; downY = y;
  leftButton = ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN));
  glutPostRedisplay();
}
 
void MotionCallback(int x, int y) {
  if (leftButton){sphi+=(float)(x-downX)/4.0;stheta+=(float)(downY-y)/4.0;} // rotate
  downX = x;   downY = y;
  glutPostRedisplay();
}


void display()
{
	gluLookAt( -0.5f, -0.5f, -0.5f,  // eye
    		    0.0f, 0.0f, 0.0f,  // at
        		1.0f, -1.0f, 1.0f); // up
	glClear(GL_COLOR_BUFFER_BIT);   // Clear output buffer to black
	glColor3f(1.0, 0.0, 0.0);       // Set current drawing color to red
	
	glBegin(GL_LINES);            // begin drawing a polygon
		glVertex3f(0.0, 0.0, 0.0); 
		glVertex3f(0.5, 0.0, 0.0);

		glVertex3f(0.5, 0.0, 0.0);
		glVertex3f(0.5, 0.5, 0.0);
		
		glVertex3f(0.0, 0.0, 0.0); 
		glVertex3f(0.0, 0.5, 0.0); 

		glVertex3f(0.0, 0.5, 0.0); 
		glVertex3f(0.5, 0.5, 0.0); 

		glVertex3f(0.0, 0.0, 0.5); 
		glVertex3f(0.5, 0.0, 0.5);

		glVertex3f(0.5, 0.0, 0.5);
		glVertex3f(0.5, 0.5, 0.5);
		
		glVertex3f(0.0, 0.0, 0.5); 
		glVertex3f(0.0, 0.5, 0.5); 

		glVertex3f(0.0, 0.5, 0.5); 
		glVertex3f(0.5, 0.5, 0.5); 

		glVertex3f(0.0, 0.0, 0.0); 
		glVertex3f(0.0, 0.0, 0.5); 

		glVertex3f(0.0, 0.5, 0.0); 
		glVertex3f(0.0, 0.5, 0.5); 

		glVertex3f(0.5, 0.0, 0.0); 
		glVertex3f(0.5, 0.0, 0.5); 

		glVertex3f(0.5, 0.5, 0.0); 
		glVertex3f(0.5, 0.5, 0.5); 
	glEnd();                        // end drawing the polygon
	glFlush();                      // force OpenGL to empty the buffer
	glutSwapBuffers();
}

void reshape(int w, int h) {
    float ratio = (float)(w/(float)h);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, ratio, 1.0, 425.0);
}

int main(int argc, char **argv)
{
   glutInit(&argc, argv);                // Initializes GLUT Toolkit
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowSize(300, 300);         // Creates a Window with size/pos
   glutInitWindowPosition(300, 300);
   glutCreateWindow("Simple Polygon");   
//   glutReshapeFunc(reshape);
   glutDisplayFunc(display);             // Register the call back routine
                                         // everytime the window updates
   glutReshapeFunc(ReshapeCallback);
   glutMouseFunc(MouseCallback);
   glutMotionFunc(MotionCallback);
   glutMainLoop();             // Enter the toolkit loop which waits
                               // for interactive events and also
                               // calls the display routine everytime
                               // screen updates
}


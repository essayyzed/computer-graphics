/* Compile code as: gcc hello.c -lGL -lglut */

#include <GL/glut.h>                     // Glut already includes glu.h and gl.h
#include <GL/glu.h>
#include <GL/gl.h>

void display()
{
   glClearColor(0.0, 0.0, 0.0, 0.0);  // What color should window clear to
   glClear(GL_COLOR_BUFFER_BIT);   // Clear output buffer to window color
   glColor3f(1.0, 0.0, 0.0);       // Set current drawing color to red
   glBegin(GL_POLYGON);            // begin drawing a polygon
      glVertex2f(-0.5, -0.5);      // vertices of the polygon
      glVertex2f( 0.5, -0.5);
      glVertex2f( 0.5,  0.5);
      glVertex2f(-0.5,  0.5);	  
   glEnd();                        // end drawing the polygon
   glFlush();                      // force OpenGL to empty the buffer and render
}
int main(int argc, char **argv)
{
   glutInit(&argc, argv);                // Initializes GLUT Toolkit
   glutInitWindowSize(300, 300);         // Creates a Window with size/pos
   glutInitWindowPosition(300, 300);
   glutCreateWindow("Simple Polygon");   
   glutDisplayFunc(display);             // Register the call back routine
                                         // everytime the window updates
   glutMainLoop();      // Enter the toolkit loop which waits for 
                        // interactive events and also calls the display 
                        // routine everytime screen updates
}


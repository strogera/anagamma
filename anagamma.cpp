#include <GL/glut.h>  
#include <math.h>
#include <vector>
 

#define PI  3.14159265f

using std::vector;

// global variable
GLfloat angle1 = 0.0f;  // rotational angle of the shapes
GLfloat angle2 = 0.0f;  // rotational angle of the shapes
int refreshMills = 30; // refresh interval in milliseconds
vector<vector<float>> orbitVector;
 
/* Initialize OpenGL Graphics */
void initGL() {
   // Set "clearing" or background color
   glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Black and opaque
}
 
/* Called back when timer expired */
void Timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(refreshMills, Timer, 0); // next Timer call milliseconds later
}
 
void display() {
   glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer
   glMatrixMode(GL_MODELVIEW);     // To operate on Model-View matrix
   glLoadIdentity();               // Reset the model-view matrix
 
   float x, y;
   float radius=0.02f;
   float newxA=cos(angle1*PI/180.0f), newyA=sin(angle1*PI/180.0f),
	 newxB=cos(angle2*PI/180.0f), newyB=sin(angle2*PI/180.0f);
   float tx=cos(angle1*PI/180.0f)*0.9;
   float ty=sin(angle1*PI/180.0f)*0.9;
   glPushMatrix();                     // Save model-view matrix setting
   glBegin(GL_POLYGON);                  // Each set of 4 vertices form a quad
      glColor3f(0.0f, 1.0f, 1.0f);     
      x=tx+(float)radius*cos(359*PI/180.0f);
      y=ty+(float)radius*sin(359*PI/180.0f);
      for(int i=0; i<360; i++){
	      glVertex2f(x, y);
	      x=tx+(float)radius*cos(i*PI/180.0f);
	      y=ty+(float)radius*sin(i*PI/180.0f);
	      glVertex2f(x, y);
      }
   glEnd();
   glPopMatrix();                      // Restore the model-view matrix
   


   float radius2=0.02f;
   tx=cos(angle2*PI/180.0f);
   ty=sin(angle2*PI/180.0f);
   glPushMatrix();                     // Save model-view matrix setting
   glBegin(GL_POLYGON);                  // Each set of 4 vertices form a quad
      glColor3f(1.0f, 0.5f, 0.0f);     
      x=tx+(float)radius2*cos(359*PI/180.0f);
      y=ty+(float)radius2*sin(359*PI/180.0f);
      for(int i=0; i<360; i++){
	      glVertex2f(x, y);
	      x=tx+(float)radius*cos(i*PI/180.0f);
	      y=ty+(float)radius*sin(i*PI/180.0f);
	      glVertex2f(x, y);
      }
   glEnd();
   glPopMatrix();                      // Restore the model-view matrix
 

   vector<float> temp;
   temp.push_back((newxA+newxB)/2.0f);
   temp.push_back((newyA+newyB)/2.0f);  
   orbitVector.push_back(temp);
   glPushMatrix();                     // Save model-view matrix setting
   glBegin(GL_LINE_STRIP);
   for(vector<float> vec: orbitVector){
	      glColor3f(0.0f, 1.0f, 0.0f);    
	   glVertex2f(vec[0], vec[1]);
   }
	   glEnd();
   glPopMatrix();                      // Restore the model-view matrix
 
   glutSwapBuffers();   // Double buffered - swap the front and back buffers
 
   // Change the rotational angle after each display()
   angle1 += 8.0f;
   angle2 += 13.0f;
}
 
void reshape(GLsizei width, GLsizei height) {  
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;          
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping area to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();
   if (width >= height) {
     // aspect >= 1, set the height from -1 to 1, with larger width
      gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
   } else {
      // aspect < 1, set the width to -1 to 1, with larger height
     gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
   }
}
 
int main(int argc, char** argv) {
   glutInit(&argc, argv);          // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE);  // Enable double buffered mode
   glutInitWindowSize(640, 480);   // Set the window's initial width & height - non-square
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow("Venus Earth Test");  // Create window with the given title
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   glutTimerFunc(0, Timer, 0);     // First timer call immediately
   initGL();                       // Our own OpenGL initialization
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}

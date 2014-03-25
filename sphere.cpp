#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>



using namespace std;

struct point {
	float x;
	float y;
	float z;
	
	point(){
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	
	void draw(){
		glVertex3f (x, y, z); 
	}
};



void init (void){
		glClearColor (0.0, 0.0, 0.0, 1.0); 
		glMatrixMode(GL_PROJECTION); 
		glLoadIdentity(); 
		glOrtho(-400.0, 400.0, -300.0, 300.0, -2000.0, 2000.0); 

        
}

void handleKeypress (unsigned char key, int x, int y){
}

void processSpecialKeys(int key, int x, int y) {
}

void display(void){
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		point a;
		
		glRotatef(10,0,1,0);
        glRotatef(-10,1,0,0);
            
		glFlush ();
}

int main(int argc, char** argv){
        glutInit(&argc, argv);
        glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize (800, 600);
        glutInitWindowPosition (100, 100);
        glutCreateWindow ("sphere");
        glutKeyboardFunc(handleKeypress);
        glutSpecialFunc(processSpecialKeys);
		glutDisplayFunc(display); 
		init ();
        glutMainLoop();
        return 0;
}


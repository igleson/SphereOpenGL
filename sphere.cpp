#include <GL/glut.h>
#include <list>
#include <math.h>

using namespace std;

struct point {
	float x;
	float y;
	float z;
	
	point(int xPos, int yPos, int zPos){
		x = xPos;
		y = yPos;
		z = zPos;
	}
	
	point(){
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	
	void draw(){
		glVertex3f (x, y, z); 
	}
	
	void draw(point translation){
		glVertex3f (x + translation.x, y + translation.y, z + translation.z); 
	}
	
	void normalize(point referential, float length){
		float dx = x - referential.x;
		float dy = y - referential.y;
		float dz = z - referential.z;
		
		float distance = sqrt(pow(dx, 2)+pow(dy, 2)+pow(dz, 2));
		
		dx = dx * length / distance;
		dy = dy * length / distance;
		dz = dz * length / distance;
		
		x = referential.x + dx;
		y = referential.y + dy;
		z = referential.z + dz;
	}
};

point mediumPoint(point a, point b){
	point ret((a.x+b.x)/2,(a.y+b.y)/2,(a.z+b.z)/2);
	return ret;
}

struct triangle {
	
	point a;
	point b;
	point c;
	
	triangle(point aPos, point bPos, point cPos){
		a = aPos;
		b = bPos;
		c = cPos;
	}
	
	list<triangle> divide(triangle* self, int depth){
		list<triangle> ret;
		if(depth == 0){
			ret.push_back(*self);
		}else{
			point ab = mediumPoint(a,b);
			point bc = mediumPoint(b,c);
			point ca = mediumPoint(c,a);
			triangle t1(a,ab,ca);
			triangle t2(ab,b,bc);
			triangle t3(bc,c,ca);
			triangle t4(ab,bc,ca);
			list<triangle> l1 = t1.divide(&t1, depth-1);
			ret.splice(ret.end(), l1);
			l1 = t2.divide(&t2, depth-1);
			ret.splice(ret.end(), l1);
			l1 = t3.divide(&t3, depth-1);
			ret.splice(ret.end(), l1);
			l1 = t4.divide(&t4, depth-1);
			ret.splice(ret.end(), l1);	
		}
		return ret;
	}
	
	void normalize(point referential, float length){
		a.normalize(referential, length);
		b.normalize(referential, length);
		c.normalize(referential, length);
	}
	
	void draw(){
		glBegin(GL_LINE_LOOP);
			a.draw();
			b.draw();
			c.draw();
		glEnd();
	}
	
	void draw(point translation){
		glBegin(GL_LINE_LOOP);
			a.draw(translation);
			b.draw(translation);
			c.draw(translation);
		glEnd();
	}
};

void triangle2Sphere(list<triangle> triangles, point center, float radius, point realCenter){
		for (list<triangle>::iterator it = triangles.begin(); it != triangles.end(); it++){
			(*it).normalize(center, radius);
			(*it).draw(realCenter);
		}
}

struct sphere {

	point center;
	point realCenter;
	float radius;
	int amountPoints;
	
	sphere(point cen, float rad, int points){
		point zero;
		center = zero;
		radius = rad;
		realCenter = cen;
		amountPoints = points;
	}
	
	void draw(){
		point a1(center.x + radius, 0, 0);
		point b1(0, center.y + radius, 0);
		point c1(0, 0, center.z + radius);
		triangle t1(a1,b1,c1);
		triangle2Sphere(t1.divide(&t1,amountPoints), center, radius, realCenter);
				
		point a2(center.x - radius, 0, 0);
		point b2(0, center.x + radius, 0);
		point c2(0, 0, center.x + radius);
		triangle t2(a2,b2,c2);
		triangle2Sphere(t2.divide(&t2,amountPoints), center, radius, realCenter);
		
		point a3(center.x + radius, 0, 0);
		point b3(0, center.x - radius, 0);
		point c3(0, 0, center.x + radius);
		triangle t3(a3,b3,c3);
		triangle2Sphere(t3.divide(&t3,amountPoints), center, radius, realCenter);
        
        point a4(center.x -radius, 0, 0);
		point b4(0, center.x - radius, 0);
		point c4(0, 0, center.x + radius);
		triangle t4(a4,b4,c4);
		triangle2Sphere(t4.divide(&t4,amountPoints), center, radius, realCenter);
		
		point a5(center.x + radius, 0, 0);
		point b5(0, center.x + radius, 0);
		point c5(0, 0, center.x - radius);
		triangle t5(a5,b5,c5);
		triangle2Sphere(t5.divide(&t5,amountPoints), center, radius, realCenter);
		
		point a6(center.x - radius, 0, 0);
		point b6(0, center.x + radius, 0);
		point c6(0, 0, center.x - radius);
		triangle t6(a6,b6,c6);
		triangle2Sphere(t6.divide(&t6,amountPoints), center, radius, realCenter);
		
		point a7(center.x + radius, 0, 0);
		point b7(0, center.x - radius, 0);
		point c7(0, 0, center.x - radius);
		triangle t7(a7,b7,c7);
		triangle2Sphere(t7.divide(&t7,amountPoints), center, radius, realCenter);
        
        point a8(center.x - radius, 0, 0);
		point b8(0, center.x - radius, 0);
		point c8(0, 0, center.x - radius);
		triangle t8(a8,b8,c8);
		triangle2Sphere(t8.divide(&t8,amountPoints), center, radius, realCenter);
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

		glRotatef(10,0,1,0);
        glRotatef(-10,1,0,0);
		glColor3f (1, 1, 1);
		
		point center1(100, 0, 0);
		sphere s1(center1, 200, 4);
		s1.draw();
		
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
		init();
        glutMainLoop();
        return 0;
}

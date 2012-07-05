#include <GL/gl.h>
#include <GL/freeglut.h>
#include <math.h>

const int w = 800;
const int h = 600;
float pozycja=0.0;
float przyrost=0.01;


void uklad(){
    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0); //zielona os X
      glVertex3f(-5.0, 0.0, 0.0);
      glVertex3f(5.0, 0.0, 0.0);
      glColor3f(0.0, 0.0, 1.0); // niebieska os Y
      glVertex3f(0.0, -5.0, 0.0);
      glVertex3f(0.0, 5.0, 0.0);
      glColor3f(1.0, 1.0, 1.0); // czarna os Z
      glVertex3f(0.0, 0.0, -5.0);
      glVertex3f(0.0, 0.0, 5.0);
    glEnd();
}

void prostopadloscian(float zmienna_x, float zmienna_y, float zmienna_z){

	//dolna podstawa
      glColor3f(0.0, 0.0, 1.0);
	  glBegin(GL_QUADS);
	    glVertex3f(0.0, 0.0, 0.0);
	    glVertex3f(zmienna_x, 0.0, 0.0);
	    glVertex3f(zmienna_x, zmienna_y, 0.0);
	    glVertex3f(00, zmienna_y, 0.0);

	//gorna podstawa
	  glColor3f(0.0, 1.0, 0.0);
	    glVertex3f(0.0, 0.0, zmienna_z);
	    glVertex3f(zmienna_x, 0.0, zmienna_z);
	    glVertex3f(zmienna_x, zmienna_y, zmienna_z);
	    glVertex3f(0.0, zmienna_y, zmienna_z);

	//lewa sciana
	  glColor3f(0.0, 1.0, 1.0);
	    glVertex3f(0.0, 0.0, 0.0);
	    glVertex3f(0.0, 0.0, zmienna_z);
	    glVertex3f(0.0, zmienna_y, zmienna_z);
	    glVertex3f(0.0, zmienna_y, 0.0);

	//prawa sciana
	  glColor3f(1.0, 0.0, 0.0);
	    glVertex3f(zmienna_x, 0.0, 0.0);
	    glVertex3f(zmienna_x, 0.0, zmienna_z);
	    glVertex3f(zmienna_x, zmienna_y, zmienna_z);
	    glVertex3f(zmienna_x, zmienna_y, 0.0);

	//tylna sciana
	  glColor3f(1.0, 0.0, 1.0);
	    glVertex3f(0.0, zmienna_y, 0.0);
	    glVertex3f(zmienna_x, zmienna_y, 0.0);
	    glVertex3f(zmienna_x, zmienna_y, zmienna_z);
	    glVertex3f(0.0, zmienna_y, zmienna_z);

	//przednia sciana
	  glColor3f(1.0, 1.0, 0.0);
	    glVertex3f(0.0, 0.0, 0.0);
	    glVertex3f(zmienna_x, 0.0, 0.0);
	    glVertex3f(zmienna_x, 0.0, zmienna_z);
	    glVertex3f(0.0, 0.0, zmienna_z);
	  glEnd();
}

void wahadlo(){
	//dolna czesc wahadla
	glPushMatrix();
	  prostopadloscian(1.0, 0.5, 0.5);
	glPopMatrix();
	//srodkowa czesc wahadla
	glPushMatrix();
	  glTranslatef(0.15, 0.15, 0.5);
	  prostopadloscian(0.2, 0.2, 2.0);
	glPopMatrix();
	//gorna czesc wahadla
	glPushMatrix();
	  glTranslatef(-0.5, 0.15, 2.5);
	  prostopadloscian(1.5, 0.2, 0.2);
	glPopMatrix();
}

void drawScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	  uklad();
	  glPushMatrix();
	    //glLoadIdentity();
		glRotatef(45.0*sin(pozycja), 1.0, 0.0, 0.0);
	    glTranslatef(0.0, -0.25, -2.7);
	    wahadlo();
	  glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void init(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(60.0,1.0,1.0,20.0);
	gluLookAt(5.0,1.0,3.0, 0.0,0.0,0.0, 0.0,0.0,1.0);
	glMatrixMode(GL_MODELVIEW);
}

void anim()
{
    pozycja+=przyrost;
    glutPostRedisplay();
}

int main (int argc , char **argv) {
    glutInit(&argc , argv);
    glutInitDisplayMode (GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(w, h);
    glutCreateWindow ("wahadlo w GLUT");
    glutDisplayFunc(drawScene);
    glutIdleFunc(anim);
    init();
    glutMainLoop();
    return 0;
}

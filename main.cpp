
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib,"glaux.lib")
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>
#include <stdlib.h> 
#include <time.h>
#include <math.h>
#include <iostream>
#include <complex>
#include "gl/glut.h"
using namespace std;
double x, y;
double r, g, b;
class Complex {
private: double r, i;
public:
    Complex(double r, double i)
        { this->r = r; this->i = i; }
    Complex operator+(const Complex &c)
	{ return Complex(r + c.r,0.5+ i + c.i); }
	//  { return Complex(0.5 + r + c.r, 0.5 - i + c.i); }
	//  { return Complex(0.5 + r *r + c.r, -0.5 - i - c.i); }
	//	{ return Complex(r+ c.r, 0.5+0.5*i + c.i); }
    Complex operator*(const Complex &c) 
	{ return Complex(r * c.r - i * c.i, 2 * r * c.i); }
    double abs(){return r * r + i * i;} 
};
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();    
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); }
int k = 0;
void display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	r = 1; g = 1; b = 1;
	  glBegin(GL_POINTS);
	  glColor3f(r, g, b);
	  for (y = 0; y < 600; y++) //построение множества
      for (x = 0; x < 1000; x++)
      {
          //Complex z(-1.7433419053321,0.0000907687489);
		  //Complex z(-1.88488933694469,0.00000000081387);
		  //Complex z(−1.96680095, 0.00000478);
		  Complex z(0,0);
          int i = 0;
          while (i < 500 && z.abs() < 16){
              z = z * z + Complex((x - 600) / 180.0, (y - 400) / 180.0);
              i++;              
          	  if (i >=0 && i < 10){
					r = (128 - 4 * i*7) / 255;
					g = (255 - 8 * i*7) / 255;
					b = (8 * i*7) / 255;
			  }
			  if (i >=10 && i < 20)	{
					g = (228 - 4 * i*20) / 255;
					b = (255 - 8 * i*20) / 255;
					r = (8 * i*20) / 255;
			  } 
			  if (i >=20 && i < 400)	{
					b = (128 - 4 * i*2) / 255;
					r = (255 - 3 * i*2) / 255;
					g = (8 * i*2) / 255;
			  }
			  if (i >=400 && i < 500)	{
					g = (128 + 4 * i) / 255;
					b = (255 - 8 * i) / 255;
					r = (2 * i) / 255;
			  }
		  }
			glColor3f(r, g, b);
			glVertex2d(x, y); 
      }
  glEnd();
  glutSwapBuffers();
}

int main (int argc, char *argv[]){
      glutInit(&argc, argv);
      glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
      glutInitWindowSize(1000, 600);
      glutCreateWindow("Mandelbrot");
      glutDisplayFunc(display);
      glutReshapeFunc(reshape);
      glutMainLoop();
}

#include<GL/freeglut.h>
#include "cProstokat.h"

cProstokat::cProstokat(double a, double b, double x, double y, float R, float G, float B): a_(a), b_(b), x_(x),y_(y),R_(R),G_(G),B_(B) {

}

void cProstokat::rysuj() {
	glPushMatrix();

	glTranslated(x_, y_, 0.0);
	glRotated(0, 1.0, 0.0, 0.0);
	glRotated(0, 0.0, 1.0, 0.0);
	glRotated(0, 0.0, 0.0, 1.0);

	glColor3d(R_,G_,B_);

	glBegin(GL_POLYGON);
	{
		glVertex3d(-a_ / 2, b_ / 2, 0);
		glVertex3d(a_ / 2, b_ / 2, 0);
		glVertex3d(a_ / 2, -b_ / 2, 0);
		glVertex3d(-a_ / 2, -b_ / 2, 0);
	}
	glEnd();
	glPopMatrix();
}


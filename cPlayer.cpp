#include "cPlayer.h"
#include "cFizyka.h"
#include <GL/freeglut.h>
#include <cmath>


void cPlayer::rysuj()
{
	double angle, vectorX, vectorY, vectorX1, vectorY1;

	glPushMatrix();

	glTranslated(x_, y_, 0.0);
	glRotated(0, 1.0, 0.0, 0.0);
	glRotated(0, 0.0, 1.0, 0.0);
	glRotated(0, 0.0, 0.0, 1.0);

	glColor3d((rand()%100)/100, (rand()%100)/100, (rand()%100)/100);

	glBegin(GL_TRIANGLE_FAN);
	{
		for (int i = 0; i <= 360; i++)
		{
			// 180 - pi
			// i - degInRad
			float degInRad = i * 3.1415 / 180;
			glVertex2f(
				cos(degInRad)*r_,
				sin(degInRad)*r_
			);
		}
	}
	glEnd();
	glPopMatrix();
}

int cPlayer::kolizja(cFizyka & X)
{
	
	if (this->r_ + X.getR() - sqrt(pow(this->getX() - X.getX(), 2) + pow(this->getY() - X.getY(), 2)) > 0.0) {
		std::cout << "kolizja" << std::endl;
		return 1;
	}
	else return 0;
}

cPlayer::cPlayer() : cFizyka()
{
}


cPlayer::~cPlayer()
{
}
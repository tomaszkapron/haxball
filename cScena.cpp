#include "cScena.h"
#include <iostream>
#include <chrono>
#include <GL/freeglut.h>

#define  P1 obj[0]
#define  P2 obj[1]
#define  B obj[2]
#define  V 0.001

#define L 3
#define W 2.2

void timer_binding(int msec);
void key_binding(unsigned char key, int x, int y);
cScena::cScena() {
	obj.push_back(new cPlayer()); //player 1;
	obj.push_back(new cPlayer()); //plater 2;
	obj.push_back(new cPlayer()); //ball;
	P2->setX(-1);
	P1->setX(-0.4);
	P1->setY(-0.4);
	
}

void cScena::resize(int width, int height) {
	const float ar = (float)width / (float)height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void cScena::timer()
{
		//AKTUALIZACJE WSZYSTKICH OBIEKTÓW
	for (auto &el : obj) {
		el->aktualizuj(GetTickCount());
	}
		//ODBICIA OD BOKÓW
	if (B->getY() >= W) //gorna sciana
		B->dostosuj_predkosc(B->getV(), 270);
	if (B->getY() <= -W) //dolna sciana
		B->dostosuj_predkosc(B->getV(), 90);
	if (B->getX() >= L) //prawa sciana
		B->dostosuj_predkosc(B->getV(), 180);
	if (B->getX() <= -L) //lewa sciana
		B->dostosuj_predkosc(B->getV(), 0);
	if (P1->kolizja(*B))
		B->prowadz_pilke(*P1);
	if (P2->kolizja(*B))
		B->prowadz_pilke(*P2);
	glutPostRedisplay();
	glutTimerFunc(30, timer_binding, 0);
}


void cScena::display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	{
		for (auto &el: obj)
		{
			el->rysuj();
		}
	}

	glPopMatrix();

	glutSwapBuffers();
}

void cScena::set_callbacks() {
	glutReshapeFunc(resize_binding);
	glutDisplayFunc(display_binding);
	glutTimerFunc(40, timer_binding, 0);
	glutKeyboardFunc(key_binding);
}


void cScena::init(int argc, char **argv, const char *window_name) {

	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(40, 40);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutCreateWindow(window_name);

	// set white as the clear colour
	glClearColor(1, 1, 1, 1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	set_callbacks();

	// start GLUT event loop. It ends when user close the window.
	glutMainLoop();
}

cScena::~cScena() {
	
}

void cScena::key(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		P1->dostosuj_predkosc(V,180);
		break;
	case 'd':
		P1->dostosuj_predkosc(V, 0);
		break;
	case 'w':
		P1->dostosuj_predkosc(V, 90);
		break;
	case 's':
		P1->dostosuj_predkosc(V, 270);
		break;
	case 'p': {
		cPlayer *cf = dynamic_cast<cPlayer*>(B);
		if (P1->kolizja(*B))
			cf->strzal(*P1); }
		break;

	case '4':
		P2->dostosuj_predkosc(V, 180);
		break;
	case '6':
		P2->dostosuj_predkosc(V, 0);
		break;
	case '8':
		P2->dostosuj_predkosc(V, 90);
		break;
	case '5':
		P2->dostosuj_predkosc(V, 270);
		break;
	}
}
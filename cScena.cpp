#include "cScena.h"
#include "cProstokat.h"
#include <iostream>
#include <chrono>
#include <GL/freeglut.h>
#include <Windows.h>

#define  P1 obj[0] //Gracz Lewy
#define  P2 obj[1] //Gracz Prawy
#define  B obj[2] //Pi³ka
#define  S1 obj[3] //S³upek PG
#define  S2 obj[4] //S³upek PD
#define  S3 obj[5] //S³upek LG
#define  S4 obj[6] //S³upek LD
#define  V 0.001 //Prêdkoœæ podstawowa

#define L 2.7 //d³ugoœæ od œrodka do prawej krawêdzi odbicia 
#define W 2.2 //wysokoœæ od œrodka do górnej krawêdzi odbicia

void timer_binding(int msec); 
void key_binding(unsigned char key, int x, int y);

cScena::cScena() :goleLewy_(0), golePrawy_(0), czasMeczu_(180), bufferCzasu_(0) {
	obj.push_back(new cPlayer()); //player 1;
	obj.push_back(new cPlayer()); //plater 2;
	obj.push_back(new cPlayer()); //ball;
	obj.push_back(new cPlayer()); //s³upek1; LG
	obj.push_back(new cPlayer()); //s³upek2; LD
	obj.push_back(new cPlayer()); //s³upek3; PG
	obj.push_back(new cPlayer()); //s³upek4; PD

	S1->setPosition(L + 0.2, 2.3 - 1.5); //ustawia s³upek PG
	S1->setR(0.1);
	S2->setPosition(L + 0.2, -2.3 + 1.5); //ustawia s³upek PD
	S2->setR(0.1);
	S3->setPosition(-L - 0.2, 2.3 - 1.5); //ustawia s³upek LG
	S3->setR(0.1);
	S4->setPosition(-L - 0.2, -2.3 + 1.5); //ustawia s³upek LD
	S4->setR(0.1);

	B->setR(0.15);
	B->setColor(1, 1, 1);
	P1->setPosition(-1.5, 0);
	P2->setPosition(1.5, 0);
	P1->setColor(0.5, 0.5, 0.5);
	czas_ = GetTickCount();
}

void cScena::rysuj_boisko()
{
	cProstokat a(7, 2, 0, W + 1.2);
	a.rysuj();
	cProstokat b(7, 2, 0, -W-1.2);
	b.rysuj();
	cProstokat c(2, 5, L+1.5,0);
	c.rysuj();
	cProstokat d(2, 5,- L - 1.5, 0);
	d.rysuj();
	cProstokat e(2, 3, -L - 1.2, 2.3);
	e.rysuj();
	cProstokat f(2, 3, -L - 1.2, -2.3);
	f.rysuj();
	cProstokat g(2, 3, L + 1.2, 2.3);
	g.rysuj();
	cProstokat h(2, 3, L + 1.2, -2.3);
	h.rysuj();
	cProstokat i(0.05, 6, 0, 0);
	i.rysuj();
	cProstokat j(0.05, 2.5, -2, 0);
	j.rysuj();
	cProstokat k(2.05,0.05, -3, -1.25);
	k.rysuj();
	cProstokat l(2.05, 0.05, -3, 1.25);
	l.rysuj();
	cProstokat m(0.05, 2.5, 2, 0);
	m.rysuj();
	cProstokat n(2.05, 0.05, 3, -1.25);
	n.rysuj();
	cProstokat o(2.05, 0.05, 3, 1.25);
	o.rysuj();

	cProstokat q(7, 5, 0, 0,0.57,0.9,0.246);
	q.rysuj();
}

void cScena::timer()
{
		//AKTUALIZACJE WSZYSTKICH OBIEKTÓW I CZASU GRY
	aktualizujCzas(GetTickCount());
	for (auto &el : obj) {
		el->aktualizuj(GetTickCount());
	}
	//------------------------------------------
		//ODBICIA OD BOKÓW
	if (B->getY() >= W) { //gorna sciana
		B->setY(W);
		B->odbicieSciana(270);
	}
	if (B->getY() <= -W) { //dolna sciana
		B->setY(-W);
		B->odbicieSciana(90);
	}
	if (B->getX() >= L) { //prawa sciana
		if (B->getY() >= 2.3 - 1.5 || B->getY() <= -2.3 + 1.5) {
			B->setX(L);
			B->odbicieSciana(180);
		}
	}
	if (B->getX() <= -L) { //lewa sciana
		if (B->getY() >= 2.3 - 1.5 || B->getY() <= -2.3 + 1.5) {
			B->setX(-L);
			B->odbicieSciana(0);
		}
	}
	//------------------------------------------
		//ODBICIA PI£KI OD GRACZY
	if (P1->kolizja(*B)==1)
		B->prowadz_pilke(*P1);
	if (P2->kolizja(*B)==1)
		B->prowadz_pilke(*P2);
		//ODBICIE GRACZA OD GRACZA
	if (P1->kolizja(*P2) == 1)
		P2->prowadz_pilke(*P1);
	if (P2->kolizja(*P1) == 1)
		P1->prowadz_pilke(*P2);
		//ODBICIA OD S£UPKÓW
	if (S1->kolizja(*B) == 1)
		B->odbicieSlupek(*S1);
	if (S2->kolizja(*B) == 1)
		B->odbicieSlupek(*S2);
	if (S3->kolizja(*B) == 1)
		B->odbicieSlupek(*S3);
	if (S4->kolizja(*B) == 1)
		B->odbicieSlupek(*S4);
	//------------------------------------------
		//ZASADY GRY
	if (czyGol() == 1) {
		goleLewy_++;
		wynik();
		Sleep(2000);
		ustawPoGolu();
	}
	if (czyGol() == 2) {
		golePrawy_++;
		wynik();
		Sleep(2000);
		ustawPoGolu();
	}
	//------------------------------------------
		//Sterowanie
	if (GetAsyncKeyState(0x57)) { //W
		P1->dostosuj_predkosc(V, 90);
	}
	if (GetAsyncKeyState(0x53)) { //S
		P1->dostosuj_predkosc(V, 270);
	}
	if (GetAsyncKeyState(0x41)) { //A
		P1->dostosuj_predkosc(V, 180);
	}
	if (GetAsyncKeyState(0x44)) { //D
		P1->dostosuj_predkosc(V, 0);
	}

	if (GetAsyncKeyState(VK_UP)) { //W
		P2->dostosuj_predkosc(V, 90);
	}
	if (GetAsyncKeyState(VK_DOWN)) { //S
		P2->dostosuj_predkosc(V, 270);
	}
	if (GetAsyncKeyState(VK_LEFT)) { //A
		P2->dostosuj_predkosc(V, 180);
	}
	if (GetAsyncKeyState(VK_RIGHT)) { //D
		P2->dostosuj_predkosc(V, 0);
	}
	//-------------------------------------------
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
		rysuj_boisko();
	}
	glPopMatrix();
	glutSwapBuffers();
}

int cScena::czyGol(){
	if (B->getX() >= L+0.4) 
		return 1;
	
	if (B->getX() <= -L-0.4) 
		return 2;

	return 0;
}

void cScena::ustawPoGolu()
{
	P1->setPosition(-1.5,0);
	P2->setPosition(1.5, 0);
	B->setPosition(0, 0);
	cPlayer *cf = dynamic_cast<cPlayer*>(B);
	cf->ustaw_predkosc(0, 0);
	cf = dynamic_cast<cPlayer*>(P1);
	cf->ustaw_predkosc(0, 0);
	cf = dynamic_cast<cPlayer*>(P2);
	cf->ustaw_predkosc(0, 0);
}

void cScena::wynik()
{
	std::cout << goleLewy_ << " : " << golePrawy_ << std::endl;
}

void cScena::wygrana()
{
	if (goleLewy_ > golePrawy_)
		std::cout << "WYGRYWA GRACZ PO LEWEJ!" << std::endl;
	if(golePrawy_>goleLewy_)
		std::cout << "WYGRYWA GRACZ PO PRAWEJ!" << std::endl;
	if (golePrawy_ == goleLewy_)
		std::cout << "REMIS!" << std::endl;
}

void cScena::pokazCzas()
{
	int min, sek;
	min = floor(czasMeczu_/60);
	sek = czasMeczu_ % 60;
	std::cout << min << ":" << sek << std::endl;
}

void cScena::aktualizujCzas(int czasAktualny)
{
	float delta_t = czasAktualny - czas_;
	bufferCzasu_ += delta_t;
	czas_ += delta_t;
	if (bufferCzasu_ >= 1000) {
		czasMeczu_ -= bufferCzasu_ / 1000;
		bufferCzasu_ = 0;
		std::system("cls");
		wynik();
		pokazCzas();
		if (czasMeczu_ <= 0) {
			wygrana();
			Sleep(2000);
			czasMeczu_ = 180;
			goleLewy_ = 0;
			golePrawy_ = 0;
			ustawPoGolu();
		}
	}
}

void cScena::key(unsigned char key, int x, int y) {
	switch (key) {
	
	case 'p': {
		cPlayer *cf = dynamic_cast<cPlayer*>(B);
		if (P1->kolizja(*B)>1)
			cf->strzal(*P1); }
		break;

	
	case '0': {
		cPlayer *cf = dynamic_cast<cPlayer*>(B);
		if (P2->kolizja(*B) > 1)
			cf->strzal(*P2); }
		break;
	}
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

void cScena::set_callbacks() {
	glutReshapeFunc(resize_binding);
	glutDisplayFunc(display_binding);
	glutTimerFunc(40, timer_binding, 0);
	glutKeyboardFunc(key_binding);
}

void cScena::init(int argc, char **argv, const char *window_name) {
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(200, 40);
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
#include "cFizyka.h"
#include <GL/freeglut.h>

#ifndef __unix__
#include <windows.h>
#else
#include<chrono>
unsigned long long GetTickCount()
{
	using namespace std::chrono;
	return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}
#endif
#define  _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

void cFizyka::aktualizuj(int czas_aktualny)
{
	float delta_t = czas_aktualny - czas_;
	if (delta_t > 100) delta_t = 50;//dla przerwy dluzszej niz 1s nie przeprowadzana jest aktualizacja
	v_x_ = v_ * cos(alfa_v_ / 180.0*M_PI);
	v_y_ = v_ * sin(alfa_v_ / 180.0*M_PI);
		//zmiana po³o¿enia
	x_ = x_ + v_x_ * delta_t;
	y_ = y_ + v_y_ * delta_t;

		//zmiana predkosci
	v_x_ *= tarcie_;
	v_y_ *= tarcie_;
		//wypadkowa v
	v_ = sqrt(v_x_*v_x_ + v_y_ * v_y_);
		//kierunek predkosci
	alfa_v_ = atan2(v_y_, v_x_)*180.0 / M_PI;

	czas_ += delta_t;
}

void cFizyka::dostosuj_predkosc(float _v, float _alfa_v)
{
	v_x_ = v_ * cos(alfa_v_ / 180.0*M_PI);
	v_y_ = v_ * sin(alfa_v_ / 180.0*M_PI);
	if (_alfa_v == 0)
		v_x_ += _v;
	if (_alfa_v == 180)
		v_x_ -= _v;
	if (_alfa_v == 90)
		v_y_ += _v;
	if (_alfa_v == 270)
		v_y_ -= _v;
	v_ = sqrt(v_x_*v_x_ + v_y_ * v_y_);
	if (v_ > _v);
	v_ = _v;
	alfa_v_ = atan2(v_y_, v_x_)*180.0 / M_PI;
}

void cFizyka::prowadz_pilke(cFizyka& X)
{
	float kat,v;
	kat = atan2(this->getY()- X.getY(),this->getX()- X.getX())*180.0 / M_PI;
	//v = X.getV()*(this->getAlfaV()/ X.getAlfaV());
	v = 0.001;
	this->ustaw_predkosc(v,kat);
}

void cFizyka::reset()
{
	czas_ = GetTickCount();
}

cFizyka::cFizyka(float x, float y, float r) : x_(x), y_(y), r_(r)
{
	v_x_ = 0.0;
	v_y_ = 0.0;
	v_ = 0.0;
	alfa_v_ = 0.0;
	tarcie_ = 0.94;
	mass_ = 0.0;

	reset();
}


cFizyka::~cFizyka()
{
}

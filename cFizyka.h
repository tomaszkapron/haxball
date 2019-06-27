#pragma once
#define  _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
class cFizyka
{
protected:
	float r_; //promie� pi�karza i pi�ki
	float R_, G_, B_; //kolory obiekt�w

	int czas_; //czas_ ostatniej aktualizacji

	float x_, y_; //polozenie srodka masy
//---------------------------------------------------	
	float v_x_; //sk�adowa X pr�dko�ci
	float v_y_; //sk�adowa X pr�dko�ci
	float v_; //modu� wektora pr�dko�ci
	float alfa_v_;//kierunek wektora predkosci w [stopniach]
	float tarcie_;//sila tarcia
//---------------------------------------------------

public:
//---------------------------------------------------
		//GETERRY
	float getR() { return float(r_); }
	float getX() { return float(x_); }
	float getY() { return float(y_); }
	float getV() { return float(v_); }
	float getAlfaV() { return float(alfa_v_); }
	float getVx() { return float(v_x_); }
	float getVy() { return float(v_y_); }
//---------------------------------------------------
		//SETTERY
	void setR(float _r) { r_ = _r; }
	void setX(float _x) { x_ = _x; }
	void setY(float _y) { y_ = _y; }
	void setPosition(float _x, float _y) { y_ = _y; x_ = _x; }
	void ustaw_fizyka(float _t) { tarcie_ = _t; } //ustawia tarcie
	void ustaw_predkosc(float _v, float _alfa_v) { v_ = _v; alfa_v_ = _alfa_v; } //ustawia poczatkowa predkosc
	void setColor(float _R, float _G, float _B) { R_ = _R; G_ = _G; B_ = _B; }
//---------------------------------------------------
		//AKCJE
	void aktualizuj(int czas_aktualny);//zmienia polozenie obiektu na podstawie aktualnego czasu
	void odbicieSlupek(cFizyka& X); //zmienia k�t po odbiciu od s�upka
	void odbicieSciana(float _alfa_v); //zmienia k�t po odbiciu od �ciany
	void dostosuj_predkosc(float _v, float _alfa_v); //dodaje dodatkowy wektor pr�dko�ci (sterowanie)
	void prowadz_pilke(cFizyka& X); //nadaje pi�ce pr�dko�� i kierunek prowadz�cego pi�k�
	virtual int kolizja(cFizyka &X)=0; //(funkcja wirtualna) wykrywanie kolizji z innym obiektem (funkcja przekazuje 1 gdy jest kolizja 0 gdy brak)
	virtual void rysuj()=0; //wirtualna funkcja rysowania gracza
//---------------------------------------------------
	void reset(); //resetuje czas_

	cFizyka(float x=0, float y=0, float r=0.2, float R=0, float G=0, float B=0);//konstruktor z warto��iami domy�lnymi
	~cFizyka();
};


#pragma once
#define  _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
class cFizyka
{
protected:
	float r_; //promieñ pi³karza i pi³ki

	int czas_; //czas_ ostatniej aktualizacji
	float x_, y_; //polozenie srodka masy
	
	float v_x_;//predkosc
	float v_y_;
	
	float v_;
	float alfa_v_;//kierunek wektora predkosci w [stopniach]
	float tarcie_;//sila tarcia
	float mass_;//masa(do liczenia pêdu) ????
public:
	float getR() { return float(r_); }
	float getX() { return float(x_); }
	float getY() { return float(y_); }
	float getVx() { return float(v_x_); }
	float getVy() { return float(v_y_); }
	void setX(float _x) { x_ = _x; }
	void setY(float _y) { y_ = _y; }

	void aktualizuj(int czas_aktualny);//zmienia polozenie obiektu na podstawie aktualnego czasu
	
	void ustaw_predkosc(float _v, float _alfa_v) { v_ = _v; alfa_v_ = _alfa_v; } //ustawia poczatkowa predkosc
	void dostosuj_predkosc(float _v, float _alfa_v) {
		v_ = _v;  alfa_v_ = atan2(v_y_, v_x_)*180.0 / M_PI;
	}


	void ustaw_vX(float _v_x) { v_x_ = _v_x; }
	void ustaw_vY(float _v_y) { v_y_ = _v_y; }
	
	void ustaw_fizyka(float _t) { tarcie_ = _t; } //ustawia tarcie
	void ustaw_masa(float _m) {	mass_ = _m; } //ustawia mase

	virtual int kolizja(cFizyka &X)=0; //wykrywanie kolizji z innym obiektem (funkcja przekazuje 1 gdy jest kolizja 0 gdy brak)
	virtual void rysuj()=0;
	void reset(); //resetuje czas_

	cFizyka(float x=0, float y=0, float r=0.2);
	~cFizyka();
};


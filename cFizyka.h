#pragma once
class cFizyka
{
protected:
	float r_; //promieñ pi³karza i pi³ki

	int czas_; //czas_ ostatniej aktualizacji
	float x_, y_; //polozenie srodka masy
	float v_;//predkosc
	float alfa_v_;//kierunek wektora predkosci w [stopniach]
	float tarcie_;//sila tarcia
	float mass_;//masa(do liczenia pêdu) ????
public:
	float getX() { return float(x_); }
	float getY() { return float(y_); }
	void setX(float _x) { x_ = (int)_x; }
	void setY(float _y) { y_ = (int)_y; }

	void aktualizuj(int czas_aktualny);//zmienia polozenie obiektu na podstawie aktualnego czasu
	void ustaw_predkosc(float _v, float _alfa_v); //ustawia poczatkowa predkosc
	void ustaw_fizyka(float _t); //ustawia tarcie
	void ustaw_masa(float _m); //ustawia mase

	virtual int kolizja(cFizyka &X); //wykrywanie kolizji z innym obiektem (funkcja przekazuje 1 gdy jest kolizja 0 gdy brak)

	void reset(); //resetuje czas_

	cFizyka();
	~cFizyka();
};


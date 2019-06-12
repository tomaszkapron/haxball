#pragma once
#include "cFizyka.h"
#include <iostream>
class cPlayer : public cFizyka
{
	int numer_;//rysuje numer na "koszulce" gracza
public:
	virtual void rysuj();
	void strzal(cFizyka& X); //sprawdza czy obok gracza jest pilka, je¿eli tak, nadaje jej predkosc i kierunek w zaleznosci od polozenia + gdy przytrzymany klawisz strzalu podswietla gracza bia³ym kó³kiem
	virtual int kolizja(cFizyka & X);
	cPlayer();
	~cPlayer();
};


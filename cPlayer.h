#pragma once


class cPlayer : public cFizyka
{
	int numer_;//rysuje numer na "koszulce" gracza
public:
	void rysuj();
	void strzal(); //sprawdza czy obok gracza jest pilka, je¿eli tak, nadaje jej predkosc i kierunek w zaleznosci od polozenia + gdy przytrzymany klawisz strzalu podswietla gracza bia³ym kó³kiem
	
	cPlayer();
	~cPlayer();
};


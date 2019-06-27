#pragma once

#include "cPlayer.h"
#include <utility>
#include <vector>
#include <stdio.h>

//bindingi dla callback�w
void resize_binding(int width, int height);
void display_binding();
//void key_binding(unsigned char key, int x, int y);
//void timer_binding(int i);

class cScena
{
		//POLA ODPOWIEDZIALNE ZA CZAS MECZU
	int czasMeczu_; //pozosta�y czas do konca w sekundach
	int czas_; //czas ostatniej aktualizacji
	int bufferCzasu_; //�aduje si� do 1s, aby rzadziej od�wie�a� zegar 
		//LICZNIK WYNIKU
	int goleLewy_, golePrawy_; //przechowuj� ilo�� goli

	std::vector<cFizyka*> obj; //wektor obiekt�w aktywnych
public:
	cScena(); 
	~cScena();
	//---------------------------------------------------
		//LOGIKA GRY
	int czyGol(); //sprawdza czy pad�a bramka zwraca 
	void ustawPoGolu();//ustawia po golu pi�k� i zawodnik�w w odpowiednich miejscach
	void wynik(); //wy�wietlanie wyniku w konsoli
	void wygrana(); //sprawdza czy sko�czy� si� czas, og�asza zwyci�zce, ustawia gr� od nowa
	void pokazCzas(); //wy�wietlanie czasu w konsoli
	void aktualizujCzas(int czasAktualny); //Liczenie czasu gry
	//---------------------------------------------------
	void rysuj_boisko(); //rysuje boisko
	//---------------------------------------------------
		//CALLBACKS
	void key(unsigned char key, int x, int y);
	void resize(int width, int height);
	void timer();
	void display();
	//---------------------------------------------------
	void init(int argc, char *argv[], const char* window_name);
	void set_callbacks();
};


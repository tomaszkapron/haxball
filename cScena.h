#pragma once

#include "cPlayer.h"
#include <utility>
#include <vector>
#include <stdio.h>

//bindingi dla callbacków
void resize_binding(int width, int height);
void display_binding();
//void key_binding(unsigned char key, int x, int y);
//void timer_binding(int i);

class cScena
{
		//POLA ODPOWIEDZIALNE ZA CZAS MECZU
	int czasMeczu_; //pozosta³y czas do konca w sekundach
	int czas_; //czas ostatniej aktualizacji
	int bufferCzasu_; //³aduje siê do 1s, aby rzadziej odœwie¿aæ zegar 
		//LICZNIK WYNIKU
	int goleLewy_, golePrawy_; //przechowuj¹ iloœæ goli

	std::vector<cFizyka*> obj; //wektor obiektów aktywnych
public:
	cScena(); 
	~cScena();
	//---------------------------------------------------
		//LOGIKA GRY
	int czyGol(); //sprawdza czy pad³a bramka zwraca 
	void ustawPoGolu();//ustawia po golu pi³kê i zawodników w odpowiednich miejscach
	void wynik(); //wyœwietlanie wyniku w konsoli
	void wygrana(); //sprawdza czy skoñczy³ siê czas, og³asza zwyciêzce, ustawia grê od nowa
	void pokazCzas(); //wyœwietlanie czasu w konsoli
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


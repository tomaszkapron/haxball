#pragma once

#include "cPlayer.h"
#include <utility>
#include <vector>

//bindingi dla callbacków
void resize_binding(int width, int height);
void display_binding();
//void key_binding(unsigned char key, int x, int y);
//void timer_binding(int i);

class cScena
{
	int goleLewy_, golePrawy_;
	std::vector<cFizyka*> obj;
public:
	int czyGol(); //sprawdza czy pad³a bramka zwraca 
	void ustawPoGolu();//ustawia po golu pi³kê i zawodników w odpowiednich miejscach
	void wynik();
			//CALLBACKS
	void key(unsigned char key, int x, int y);
	void resize(int width, int height);
	void timer();
	void display();

	void init(int argc, char *argv[], const char* window_name);
	void set_callbacks();


	void rysuj_boisko();
	
	cScena();
	~cScena();
};


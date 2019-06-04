#include <iostream>

//#define NDEBUG
#include <GL/freeglut.h>
#include "cScena.h"

cScena scena;

void resize_binding(int width, int height) {
	scena.resize(width, height);
}

void display_binding() {
	scena.display();
}

void timer_binding(int msec) {
	scena.timer();
}

void key_binding(unsigned char key, int x, int y) {
	scena.key(key, x, y);
}


int main(int argc, char *argv[])
{
	scena.init(argc, argv, "Okno sceny");
	return 0;
}
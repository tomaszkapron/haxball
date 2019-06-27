#pragma once


class cProstokat {
	double a_, b_, x_, y_,R_,G_,B_;
public:
	cProstokat(double a=0, double b=0, double x=0, double y=0,
		float R=0.292968,float G= 0.18359375,float B= 0.03515625);
	virtual void rysuj();
	
};
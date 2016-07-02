#ifndef __dame_h
#define __dame_h

#include<string>
#include "convertfield.h"
#include<iostream>

class Dame
{
private:
	int position[2];
	
public:
	Dame(std::string, int);				// Konstruktor
	void zuege();
	int* get_position();				// Access Method
};



// Definitionen, werden später in koenig.cpp ausgelagert

Dame::Dame(std::string c, int b){
	this->position[0] = 8-b;
	this->position[1] = convertfield(c);
	std::cout << "Damenkonstruktor: " << this->position[0] << " " << this->position[1] << "\n";
}
int* Dame::get_position(){
	static int zurueck[2];
	zurueck[0]=position[0];
	zurueck[1]=position[1];
	return zurueck;
}
	
#endif
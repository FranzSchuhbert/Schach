#ifndef __turm_h
#define __turm_h

#include<string>
#include "convertfield.h"
#include<iostream>

class Turm
{
private:
	int position[2];
	
public:
	Turm(std::string, int);				// Konstruktor
	void zuege();
	int* get_position();				// Access Method
};



// Definitionen, werden später in koenig.cpp ausgelagert

Turm::Turm(std::string c, int b){
	this->position[0] = 8-b;
	this->position[1] = convertfield(c);
	std::cout << "Turmkonstruktor: " << this->position[0] << " " << this->position[1] << "\n";
}
int* Turm::get_position(){
	static int zurueck[2];
	zurueck[0]=position[0];
	zurueck[1]=position[1];
	return zurueck;
}
	
#endif
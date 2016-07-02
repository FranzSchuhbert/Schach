#ifndef __brett_h
#define __brett_h

#include<iostream>
#include<string>
#include<sstream>
#include "koenig.h"
#include "dame.h"
#include "turm.h"

class Brett
{
private:
	int position[8][8]={};
	int free[8][8]={};
	void emergencyStop (int i) const;
public:
	Brett(Koenig, Dame, Turm, Turm);
	void ausgabe();
	void ausgabe_free();
	
};

//______________________________________________________________________________
// Definitionen, werden später in brett.cpp ausgelagert

// Error exit
class BrettException : std::exception{};
void Brett::emergencyStop (int i) const{
	std::cout << std::endl << "+++ Error in class Brett; Error number: " << i << std::endl;
	throw new BrettException;
}

// Konstruktor
Brett::Brett(Koenig k, Dame d, Turm t1, Turm t2){
	int* pos;
	pos = k.get_position();
	free[pos[0]][pos[1]] = 1;
	pos = d.get_position();
	free[pos[0]][pos[1]] = 2;
	pos = t1.get_position();
	free[pos[0]][pos[1]] = 3;
	pos = t2.get_position();
	free[pos[0]][pos[1]] = 3;
	ausgabe();
}


// Memberfunktionen die auf private Variablen zugreifen
void Brett::ausgabe_free(){
	for (int i=0;i<8;i++){
		for (int j=0;j<8;j++){
			std::cout << free[i][j] << " ";
		}
		std::cout << "\n";
	}
}
void Brett::ausgabe(){
	std::cout << "    a   b   c   d   e   f   g   h   \n----------------------------------\n";
	for (int i=0;i<8;i++){
		std::string figure;
		std::ostringstream s;
		s << 8-i;
		std::cout << s.str() << "|  ";
		for (int j=0;j<8;j++){
			switch ( free[i][j] ){
			case 0 : figure = "0";				break;
			case 1 : figure = "K"; 				break;
			case 2 : figure = "D"; 				break;
			case 3 : figure = "T"; 				break;
			case 4 : figure = "L"; 				break;
			case 5 : figure = "S"; 				break;
			case 6 : figure = "B"; 				break;
			default : emergencyStop(1); 			break;
			}
			std::cout << figure << "   ";
		}
		std::cout << "\n |\n";
	}
}


#endif
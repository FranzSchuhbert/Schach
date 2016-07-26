#ifndef __klassen_h
#define __klassen_h

#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>


/*

TO DO:


- cout Operator überladen


*/




//========================================================================
// Globale Konstanten, Funktionen, Definitionen
const int size = 8;
const int anz = size * size;

char spch (int i) { return (char) (i % size + 'a'); }   // Spaltenname

enum Farbe { weiss, schwarz, neutral };
//========================================================================
// Indexklasse************************************************************
class Index
{
private:
  	
  	void emergencyStop (int i) const;
public:
	int i;
	int FeldFarbe;
	Index( int idx ) { 	this->i = idx;	this->FeldFarbe = ((int)(idx/size)+(int)(idx%size)) % 2;	}
};
// Klasse für Farbe des Schachbretts**************************************
int FeldFarbe (int idx)                                 // weiss/schwarz
{
    return (idx/size)+(idx%size) % 2;
}
//========================================================================
// Super und Subklassen für Spielsteine und leere Felder******************
class Feld
{
private:
    Index ind;
protected:
    Farbe f = neutral;
public:
    Feld (int i) : ind(i){}
    ~Feld() { delete &ind; }
    
    int getindex(){ return this->ind.i; }
    Farbe getfarbe(){ return this->f; }
    
    virtual char ch () { if (this->ind.FeldFarbe) return '_'; return ' '; }
    virtual int* pruefen( int start, int ende) {return nullptr;}
   
};

class Figur : public Feld
{
private:
	void emergencyStop(int) const;
public:
    Figur (int ix, Farbe ff) : Feld (ix) { this->f = ff; }
    virtual char ch () { return '?'; }
    virtual int* pruefen( int start, int ende ) { return nullptr; }
};

class Bauer : public Figur
{
private:
	void emergencyStop(int i) const;
public:
    Bauer (int idx, Farbe ff) : Figur (idx, ff) { }
    virtual char ch () { if (f == weiss) return 'B'; return 'b'; }
    virtual int* pruefen(int start, int ende){
    	    if ( start < 0 || start > 63 || ende < 0 || ende > 63 ){emergencyStop(0);}
    	    std::cout << "Ausgangsfigur ist Bauer" << std::endl;
    	    if ( this->f==weiss ){
    	    	    if ( start-ende==8 ) {
    	    	    	    static int zuege[2];
    	    	    	    zuege[0] = 1;
    	    	    	    std::cout << "Array size: " << zuege[0] << std::endl;
    	    	    	    zuege[1] = ende;
    	    	    	    return zuege; 
    	    	    }
    	    	    else if ( this->getindex()<56 && this->getindex()>47 && start-ende==16 ){
    	    	    	    static int zuege[3];
    	    	    	    zuege[0] = 2;
    	    	    	    std::cout << "Array size: " << zuege[0] << std::endl;
    	    	    	    zuege[1] = ende + 8;
    	    	    	    zuege[2] = ende;
    	    	    	    return zuege;
    	    	    }
    	    	    else { return nullptr; }
    	    }
    	    if ( this->f==schwarz ){
    	    	    if ( start-ende==-8 ) {
    	    	    	    static int zuege[2];
    	    	    	    zuege[0] = 1;
    	    	    	    std::cout << "Array size: " << zuege[0] << std::endl;
    	    	    	    zuege[1] = ende;
    	    	    	    return zuege; 
    	    	    }
    	    	    else if ( this->getindex()<16 && this->getindex()>7 && start-ende==-16 ){
    	    	    	    static int zuege[3];
    	    	    	    zuege[0] = 2;
    	    	    	    std::cout << "Array size: " << zuege[0] << std::endl;
    	    	    	    zuege[1] = ende - 8;
    	    	    	    zuege[2] = ende;
    	    	    	    return zuege;
    	    	    }
    	    	    else { return nullptr; }
    	    }
    	    else { return nullptr; }
    }
};

class Offizier : public Figur
{
private:
public:
    Offizier (int idx, Farbe ff) : Figur (idx, ff) { }
    virtual char ch () { return '#'; }
    virtual int* pruefen(int start, int ende){ return nullptr; }
};

class Turm : public Offizier
{
private:
	void emergencyStop(int i) const;
public:
    Turm (int idx, Farbe ff) : Offizier (idx, ff) { }
    virtual char ch () { if (f == weiss) return 'T'; return 't'; }
    virtual int* pruefen(int start, int ende){
    	    if ( start < 0 || start > 63 || ende < 0 || ende > 63 ){emergencyStop(0);}
    	    std::cout << "Ausgangsfigur ist Turm" << std::endl;
    	    int laenge = std::abs(start-ende);
    	    int test2 = laenge%8;
    	    int test3 = ende%8;
    	    int test4 = start%8;
    	    if ( test2 == 0 ){
    	    	int zwischenzug = std::abs(start-ende)/8;
    	    	int* zuege = new int[zwischenzug+1];
    	    	zuege[0] = zwischenzug;
    	    	std::cout << "Arraysize: " << zuege[0] << std::endl;
    	    	while ( zwischenzug > 0){
    	    		if ( start > ende){
    	    			zuege[zwischenzug] = start - 8 * zwischenzug;
    	    		}
    	    		else {
    	    			zuege[zwischenzug] = start + 8 * zwischenzug;
    	    		}
    	    		zwischenzug = zwischenzug - 1;
    	    	}
    	    return zuege;
    	    }
   	    else if ( laenge < 8 && start-ende>0 && test4 > laenge ){
    	       	   int* zuege = new int[laenge+1];
    	       	   zuege[0] = laenge;
    	       	   std::cout << "Arraysize: " << zuege[0] << std::endl;
    	       	   while ( laenge > 0){
    	       	   	   zuege[laenge] = start - laenge;
    	       	   	   laenge = laenge - 1;
    	       	   }
    	       	   return zuege;
    	    	   }
    	    else if ( laenge < 8 && start-ende<0 && test3 > laenge ){
    	    	   int* zuege = new int[laenge+1];
    	    	   zuege[0] = laenge;
    	    	   std::cout << "Arraysize: " << zuege[0] << std::endl;
    	    	   while ( laenge > 0){
    	    	  	   zuege[laenge] = start + laenge;
    	    	   	   laenge = laenge - 1;
    	    	   }
    	    	   return zuege;
    	    	}
    	    else {return nullptr; } 
    }
};

class Springer : public Offizier
{
private:
	void emergencyStop(int i) const;
public:
    Springer (int idx, Farbe ff) : Offizier (idx, ff) { }
    virtual char ch () { if (f == weiss) return 'S'; return 's'; }
    virtual int* pruefen(int start, int ende){
    	    if ( start < 0 || start > 63 || ende < 0 || ende > 63 ){emergencyStop(0);}
    	    std::cout << "Ausgangsfigur ist Springer" << std::endl;
    	    int test = start-ende;
    	    std::cout << std::endl << "start-ende: " << test << std::endl;
    	    static int zuege[2];
    	    zuege[0] = 1;
    	    std::cout << "Array size: " << zuege[0] << std::endl;
    	    switch ( test ){
    	    case -17: 	if ( (int)start%8 == 0 ) {emergencyStop(1);} zuege[1]=ende;return zuege; break;
    	    case -15: 	if ( (int)start%8 - 7 == 0) {emergencyStop(2);} zuege[1]=ende;return zuege; break;
    	    case -10: 	if ( (int)start%8 - 1 == 0) {emergencyStop(3);} zuege[1]=ende;return zuege; break;
    	    	    	if ( (int)start%8 == 0 ) {emergencyStop(4);} zuege[1]=ende;return zuege; break;
    	    case -6:	if ( (int)start%8 - 7 == 0 ) {emergencyStop(5);} zuege[1]=ende;return zuege; break;
    	    case 6:	if ( (int)start%8 - 6 == 0 ) {emergencyStop(6);} zuege[1]=ende;return zuege; break;
    	    case 10:	if ( (int)start%8 - 7 == 0 ) {emergencyStop(7);} zuege[1]=ende;return zuege; break;
    	    	    	if ( (int)start%8 - 6 == 0 ) {emergencyStop(8);} zuege[1]=ende;return zuege; break;
    	    case 15:	if ( (int)start%8 - 1 == 0 ) {emergencyStop(9);} zuege[1]=ende;return zuege; break;
    	    case 17:	if ( (int)start%8 - 7 == 0 ) {emergencyStop(10);} zuege[1]=ende; return zuege; break;
    	    default: return nullptr; break;
    	    }
    }
};

class Laeufer : public Offizier
{
private:
	void emergencyStop(int i) const;
public:
    Laeufer (int idx, Farbe ff) : Offizier (idx, ff) { }
    virtual char ch () { if (f == weiss) return 'L'; return 'l'; }
    virtual int* pruefen(int start, int ende){
    	    if ( start < 0 || start > 63 || ende < 0 || ende > 63 ){emergencyStop(0);}
    	    std::cout << "Ausgangsfigur ist Läufer" << std::endl;
    	    	int test1 = std::abs(start-ende)%7;
    	    	int test2 = std::abs(start-ende)%9;
    	    	if ( test1==0 ){
    	    		int zwischenzug = std::abs(start-ende)/7;
    	    		int* zuege = new int[zwischenzug+1];
    	    		zuege[0] = zwischenzug;
    	    		std::cout << "Arraysize: " << zuege[0] << std::endl;
    	    		while ( zwischenzug > 0){
    	    			if ( start > ende){
    	    				zuege[zwischenzug] = start - 7 * zwischenzug;
    	    			}
    	    			else {
    	    				zuege[zwischenzug] = start + 7 * zwischenzug;
    	    			}
    	    			zwischenzug = zwischenzug - 1;
    	    		}
    	    	return zuege; }
    	    	else if (test2==0){
    	    		int zwischenzug = std::abs(start-ende)/9;
    	    		int* zuege = new int[zwischenzug];
    	    		zuege[0] = zwischenzug;
    	    		std::cout << "Arraysize: " << zuege[0] << std::endl;
    	    		while ( zwischenzug > 0){
    	    			if ( start > ende){
    	    				zuege[zwischenzug] = start - 9 * zwischenzug;
    	    			}
    	    			else {
    	    				zuege[zwischenzug] = start + 9 * zwischenzug;
    	    			}
    	    			zwischenzug = zwischenzug -1;
    	    		}
    	    	return zuege; }
    	    	else { return nullptr; }
    }
};

class Dame : public Offizier
{
private:
	void emergencyStop(int i) const;
public:
    Dame (int idx, Farbe ff) : Offizier (idx, ff) { }
    virtual char ch () { if (f == weiss) return 'D'; return 'd'; }
    virtual int* pruefen(int start, int ende){
    	    if ( start < 0 || start > 63 || ende < 0 || ende > 63 ){emergencyStop(0);}
    	    std::cout << "Ausgangsfigur ist Dame" << std::endl;
    	  	int laenge = std::abs(start-ende);
    	    	int test1 = laenge%7;
    	    	int test2 = laenge%9;
    	    	int test3 = laenge%8;
    	    	int test4 = ende%8;
    	    	int test5 = start%8;
    	    	if ( test1==0 && test3!=0 ){
    	    		std::cout << "test1" << std::endl;
    	    		int zwischenzug = std::abs(start-ende)/7;
    	    		int* zuege = new int[zwischenzug+1];
    	    		zuege[0] = zwischenzug;
    	    		std::cout << "Arraysize: " << zuege[0] << std::endl;
    	    		while ( zwischenzug > 0){
    	    			if ( start > ende){
    	    				zuege[zwischenzug] = start - 7 * zwischenzug;
    	    			}
    	    			else {
    	    				zuege[zwischenzug] = start + 7 * zwischenzug;
    	    			}
    	    			zwischenzug = zwischenzug - 1;
    	    		}
    	    	return zuege; }
    	    	else if (test2==0){
    	    		std::cout << "test2" << std::endl;
    	    		int zwischenzug = std::abs(start-ende)/9;
    	    		int* zuege = new int[zwischenzug];
    	    		zuege[0] = zwischenzug;
    	    		std::cout << "Arraysize: " << zuege[0] << std::endl;
    	    		while ( zwischenzug > 0){
    	    			if ( start > ende){
    	    				zuege[zwischenzug] = start - 9 * zwischenzug;
    	    			}
    	    			else {
    	    				zuege[zwischenzug] = start + 9 * zwischenzug;
    	    			}
    	    			zwischenzug = zwischenzug -1;
    	    		}
    	    	return zuege; }   	 
    	    	else if ( test3 == 0 ){
    	    		std::cout << "test3" << std::endl;
    	    		int zwischenzug = std::abs(start-ende)/8;
    	    		int* zuege = new int[zwischenzug+1];
    	    		zuege[0] = zwischenzug;
    	    		std::cout << "Arraysize: " << zuege[0] << std::endl;
    	    		while ( zwischenzug > 0){
    	    			if ( start > ende){
    	    				zuege[zwischenzug] = start - 8 * zwischenzug;
    	    			}
    	   	 		else {
    	   	 			zuege[zwischenzug] = start + 8 * zwischenzug;
    	   	 		}
    	   	 		zwischenzug = zwischenzug - 1;
    	   	 	}
    	   	 	return zuege;
    	   	}
    	   	else if ( laenge < 8 && start-ende>0 && test5 > laenge ){
    	   		std::cout << "test4" << std::endl;
    	   		int* zuege = new int[laenge+1];
    	   		zuege[0] = laenge;
    	   		std::cout << "Arraysize: " << zuege[0] << std::endl;
    	   		while ( laenge > 0){
    	   			zuege[laenge] = start - laenge;
    	   			laenge = laenge - 1;
    	   		}
    	   		return zuege;
    		    	   }
    		else if ( laenge < 8 && start-ende<0 && test4 > laenge ){
    			std::cout << "test5" << std::endl;
    			int* zuege = new int[laenge+1];
    			zuege[0] = laenge;
    			std::cout << "Arraysize: " << zuege[0] << std::endl;
    			while ( laenge > 0){
    				zuege[laenge] = start + laenge;
    				laenge = laenge - 1;
    			}
    			return zuege;
    	    		}
    	    	else {return nullptr; } 
    }
};

class Koenig : public Offizier
{
private:
	void emergencyStop(int i) const;
public:
    Koenig (int idx, Farbe ff) : Offizier (idx, ff) { }
    virtual char ch () { if (f == weiss) return 'K'; return 'k'; }
    virtual int* pruefen(int start, int ende){
    	    if ( start < 0 || start > 63 || ende < 0 || ende > 63 ){emergencyStop(0);}
    	    std::cout << "Ausgangsfigur ist König" << std::endl;
    	    int test = start-ende;
    	    std::cout << "start-ende: " << test << std::endl;
    	    static int zuege[2];
    	    zuege[0] = 1;
    	    switch ( test ){
    	    case  9 : 
    	    case  8 :
    	    case  7 :
    	    case  1 :
    	    case -1 :
    	    case -7 :
    	    case -8 :
    	    case -9 : zuege[1]=ende; return zuege; break;
    	    default : return nullptr; break;
    	    }
    }
};


typedef Feld * pFeld;

//========================================================================
// Klasse für Spielbrett**************************************************

class Brett
{
private:
    pFeld b [anz];
    int* ptrpruefen;
    Feld * Offizier (int idx, Farbe f);
    void emergencyStop (int i) const;
public:
    Brett();
    void print ();
    void createFigure ( int idx, char fig){					// Funktion zum Erstellen einer Figur
    switch(fig){								// Verwendet zum Testen der Gültigkeit von Zügen
	case 'B':	b[idx] = new Bauer(idx, weiss); break;
	case 'b':	b[idx] = new Bauer(idx, schwarz); break;
	case 'T':	b[idx] = new Turm(idx, weiss); break;
	case 't':	b[idx] = new Turm(idx, schwarz); break;
	case 'S':	b[idx] = new Springer(idx, weiss); break;
	case 's':	b[idx] = new Springer(idx, schwarz); break;
	case 'L':	b[idx] = new Laeufer(idx, weiss); break;
	case 'l':	b[idx] = new Laeufer(idx, schwarz); break;
	case 'D':	b[idx] = new Dame(idx, weiss); break;
	case 'd':	b[idx] = new Dame(idx, schwarz); break;
	case 'K':	b[idx] = new Koenig(idx, weiss); break;
	case 'k':	b[idx] = new Koenig(idx, schwarz); break;
    }
    }
    void clearFigure ( int idx){
    	b[idx] = new Feld(idx);
    }
      
    void Zug( int start, int ende){						// Nimmt Array von Feldern die zwischen Start und Ziel liegen von jeweiligem Objekt auf
    		int * felder = b[start]->pruefen(start, ende);			// und prüft ob die Felder mit Figuren gleicher/gegnerischer Farbe belegt sind
    		if ( felder == nullptr || start-ende==0 || b[start]->getfarbe()==neutral ) { std::cout << std::endl << "@@@@@@@@@@@@   Ungültiger Zug, alle Figuren bleiben an ihrem Platz   @@@@@@@@@@@@@@" << std::endl; }
    		else {
    		std::cout << "Grösse: " << felder[0];
    		if ( felder != nullptr){
    		std::cout << std::endl << "Kein Nullptr" << std::endl;
    		int tester = 0;
    		int size = felder[0];
    		int x;
    		std::cout << "Size: " << size << std::endl;
    		for ( int m = size-1; m > 0; m--){
    			x = felder[m];
    			std::cout << "Feld wird geprüft: " << x <<  "  Feldcharakter: " << b[x]->ch() << " Arrayelement Nr. " << m << std::endl;
    			if ( b[x]->getfarbe() != neutral ){
    				tester = 1;
    			}
    		}
    		if ( b[felder[size]]->getfarbe()==b[start]->getfarbe() ) { std::cout << "setze tester auf 1" << std::endl; tester = 1; }
    		std::cout << "Tester: " << tester << std::endl;
    		if (tester==0){
    		b[ende] = b[start];
    		clearFigure (start);}
    		else{ std::cout << "@@@@@@@@@@@@   Ungültiger Zug, alle Figuren bleiben an ihrem Platz   @@@@@@@@@@@@@@" << std::endl;}}
    		else { emergencyStop(4); }}
    }
    
};


Feld * Brett::Offizier (int idx, Farbe f)
{
    Feld * p;
    if (idx%7 == 0) p = (Feld *) new Turm (idx, f);
    else if ( (idx%7 -1) % 5 == 0) p = (Feld *) new Springer (idx, f);
    else if ((idx%7-2) % 3 == 0) p = (Feld *) new Laeufer (idx, f);
    else if (idx%7 == 3) p = (Feld *) new Dame (idx, f);
    else if (idx%7 == 4) p = (Feld *) new Koenig (idx, f);
    else { std::cout << "Fehler"; exit (1); }
    return p;
}

Brett::Brett()
{
    int i;
    for (i = 0; i < anz; i++)
    {
        if (i < 8)
        {
            b [i] = Offizier (i, schwarz);
        }
        else if (i < 16)
        {
            b [i] = (Feld *) new Bauer (i, schwarz);
        }
        else if (i < 48)
        {
            b [i] = new Feld (i);
        }
        else if (i < 56)
        {
            b [i] = (Feld *) new Bauer (i, weiss);
        }
        else
        {
            b [i] = Offizier (i, weiss);
        }
    }
}

void Brett::print () // unschoen; besser mit cout << b;
{
    int i;
    std::cout << std::endl << "    ";
    for (i = 0; i < size; i++) std::cout << "  " << spch (i);
    std::cout << std::endl;
    for (i = 0; i < 3*size+4; i++) std::cout << "-";
    for (i = 0; i < anz; i++)
    {
        if (!(i % size))
        {
            std::cout << std::endl;
            std::cout.width (2);
            std::cout << size-i/size << ": ";
        }
        std::cout << "  " << (b [i] -> ch ());
    }
    std::cout << std::endl;
    for (i = 0; i < 3*size+4; i++) std::cout << "-";
    std::cout << std::endl << "    ";
    for (i = 0; i < size; i++) std::cout << "  " << spch (i);
    std::cout << std::endl << std::endl;
}


//========================================================================
// Klassen für Exceptions*************************************************
class IndexException : std::exception{};
void Index::emergencyStop (int i) const{
	std::cout << std::endl << "+++ Error in class Index; Error number: " << i << std::endl;
	throw new IndexException;
};

class BrettException : std::exception{};
void Brett::emergencyStop (int i) const{
	std::cout << std::endl << "+++ Error in class Brett; Error number: " << i << std::endl;
	throw new BrettException;
};

class FigurException : std::exception{};
void Figur::emergencyStop (int i) const{
	std::cout << std::endl << "+++ Error in class Figur; Error number: " << i << std::endl;
	throw new FigurException;
};

class SpringerException : std::exception{};
void Springer::emergencyStop (int i) const{
	std::cout << std::endl << "+++ Error in class Springer; Error number: " << i << std::endl;
	throw new SpringerException;
};

class KoenigException : std::exception{};
void Koenig::emergencyStop (int i) const{
	std::cout << std::endl << "+++ Error in class Koenig; Error number: " << i << std::endl;
	throw new KoenigException;
};

class DameException : std::exception{};
void Dame::emergencyStop (int i) const{
	std::cout << std::endl << "+++ Error in class Dame; Error number: " << i << std::endl;
	throw new DameException;
};

class LaeuferException : std::exception{};
void Laeufer::emergencyStop (int i) const{
	std::cout << std::endl << "+++ Error in class Laeufer; Error number: " << i << std::endl;
	throw new LaeuferException;
};

class TurmException : std::exception{};
void Turm::emergencyStop (int i) const{
	std::cout << std::endl << "+++ Error in class Turm; Error number: " << i << std::endl;
	throw new TurmException;
};

class BauerException : std::exception{};
void Bauer::emergencyStop (int i) const{
	std::cout << std::endl << "+++ Error in class Turm; Error number: " << i << std::endl;
	throw new BauerException;
};
#endif
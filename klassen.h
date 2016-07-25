#ifndef __klassen_h
#define __klassen_h

#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>


//========================================================================

const int size = 8;
const int anz = size * size;

//========================================================================


int zl (int i) { return size-i/size; }                  // Zeilennummer
int sp (int i) { return i % size + 1; }                 // Spaltennummer
char spch (int i) { return (char) (i % size + 'a'); }   // Spaltenname
int test ( int a, int b ) { if(b!=1){ if (a==1){ return 1;} else {return 0; }  } else return 1;}

//Selbstgeschriebene Indexklasse
class Index
{
private:
  	
  	void emergencyStop (int i) const;
public:
	int i;
	int FeldFarbe;
	Index( int idx ) { 	this->i = idx;	this->FeldFarbe = ((int)(idx/size)+(int)(idx%size)) % 2;	}
};


/*
class Zug
{
private:
	Index a, e;
public:
	Zug(int, int);
};

Zug::Zug(int start, int end, Brett b){
	b[end]		= b[start];
	b[start] 	= new Feld;
}
*/

int FeldFarbe (int idx)                                 // weiss/schwarz
{
    return (idx/size)+(idx%size) % 2;
}

//========================================================================

enum Farbe { weiss, schwarz };

class Feld
{
private:
    Index ind;
public:
    Feld (int i) : ind(i){}
    ~Feld() { delete &ind; }
    
    int getindex(){ return this->ind.i; }
    
    virtual char ch () { if (this->ind.FeldFarbe) return '_'; return ' '; }
    virtual int* pruefen( int start, int ende) {return nullptr;}
   
};

class Figur : public Feld
{
private:
	void emergencyStop(int) const;
protected:
    Farbe f;
public:
    Figur (int ix, Farbe ff) : Feld (ix) { this->f = ff; }
    virtual char ch () { return '?'; }
    virtual int* pruefen( int start, int ende ) { return nullptr; }
};

class Bauer : public Figur
{
private:
public:
    Bauer (int idx, Farbe ff) : Figur (idx, ff) { }
    virtual char ch () { if (f == weiss) return 'B'; return 'b'; }
    virtual int* pruefen(int start, int ende){
    	    if ( (start-ende)==8 || (start-ende)==16 ){ return nullptr; }
    	    else return 0;
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
public:
    Turm (int idx, Farbe ff) : Offizier (idx, ff) { }
    virtual char ch () { if (f == weiss) return 'T'; return 't'; }
};

class Springer : Offizier
{
private:
	void emergencyStop(int i) const;
public:
    Springer (int idx, Farbe ff) : Offizier (idx, ff) { }
    virtual char ch () { if (f == weiss) return 'S'; return 's'; }
    virtual int* pruefen(int start, int ende){
    	    std::cout << "Ausgangsfigur ist Springer" << std::endl;
    	    
    	    //***********************************************************************************************************
    	    int test = start-ende;
    	    std::cout << std::endl << "start-ende: " << test << std::endl;
    	    static int zuege[2];
    	    zuege[0] = sizeof(zuege)/sizeof(*zuege)-1;
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
    	    //***********************************************************************************************************
    }
};

class Laeufer : Offizier
{
private:
public:
    Laeufer (int idx, Farbe ff) : Offizier (idx, ff) { }
    virtual char ch () { if (f == weiss) return 'L'; return 'l'; }
    virtual int* pruefen(int start, int ende){
    	    std::cout << "Ausgangsfigur ist Läufer" << std::endl;
    	    if (ende>=0 && ende<64){
    	    	int test1 = (start-ende)%7;
    	    	int test2 = (start-ende)%9;
    	    	if ( test1==0 ){
    	    		int zwischenzug = (start-ende)/7;
    	    		int* zuege = new int[zwischenzug+1];
    	    		zuege[0] = zwischenzug;
    	    		std::cout << "Arraysize: " << zuege[0] << std::endl;
    	    		while ( zwischenzug > 0){
    	    			zuege[zwischenzug] = start - 7 * zwischenzug;
    	    			zwischenzug = zwischenzug - 1;
    	    		}
    	    	return zuege; }
    	    	else if (test2==0){
    	    		int zwischenzug = (start-ende)/9;
    	    		int* zuege = new int[zwischenzug];
    	    		while ( zwischenzug > 0){
    	    			zuege[zwischenzug-1] = start - 9 * zwischenzug;
    	    			zwischenzug = zwischenzug -1;
    	    		}
    	    	return zuege; }
    	    	else { return nullptr; }
    	    }	
    	    else { return nullptr; }
    	    return nullptr;
    }
};

class Dame : Offizier
{
private:
public:
    Dame (int idx, Farbe ff) : Offizier (idx, ff) { }
    virtual char ch () { if (f == weiss) return 'D'; return 'd'; }
};

class Koenig : Offizier
{
private:
public:
    Koenig (int idx, Farbe ff) : Offizier (idx, ff) { }
    virtual char ch () { if (f == weiss) return 'K'; return 'k'; }
};


typedef Feld * pFeld;

//========================================================================

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
    void createFigure ( int idx, char fig){
    switch(fig){
	case 'B':	b[idx] = new Bauer(idx, weiss); break;
    }
    }
    void clearFigure ( int idx){
    	b[idx] = new Feld(idx);
    }
      
    void Zug( int start, int ende){
    		int * felder = b[start]->pruefen(start, ende);
    		std::cout << "Grösse: " << felder[0];
    		if ( felder != nullptr){
    		std::cout << std::endl << "Kein Nullptr" << std::endl;
    		int tester = 0;
    		int size = felder[0];
    		int x;
    		std::cout << std::endl << "Size: " << size << std::endl;
    		for ( int m = size; m > 0; m--){
    			x = felder[m];
    			std::cout << std::endl << "Feld wird geprüft: " << felder[1] << std::endl;
    			std::cout << m << std::endl;
    			std::cout << " " << b[x]->getindex() << "  " << x <<  "  " << b[x]->ch() << std::endl;
    			if ( (b[x]->ch()!='_') && (b[x]->ch()!=' ') ){
    				tester = 1;
    			}
    		}
    		std::cout << std::endl << "Tester: " << tester << std::endl;
    		if (tester==0){
    	b[ende] = b[start];
    	clearFigure (start);}
    		else{ std::cout << "Ungültiger zug" << std::endl;}}
    	else if ( felder == nullptr ) { std::cout << std::endl << "Nullpointer!!" << std::endl; emergencyStop(3); }
    	else { emergencyStop(4); }
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
            std::cout << zl (i) << ": ";
        }
        std::cout << "  " << (b [i] -> ch ());
    }
    std::cout << std::endl;
    for (i = 0; i < 3*size+4; i++) std::cout << "-";
    std::cout << std::endl << "    ";
    for (i = 0; i < size; i++) std::cout << "  " << spch (i);
    std::cout << std::endl << std::endl;
}

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



#endif
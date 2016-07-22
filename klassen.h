#ifndef __klassen_h
#define __klassen_h

#include <cstdlib>
#include <iostream>
#include <string>


//========================================================================

const int size = 8;
const int anz = size * size;

//========================================================================


int zl (int i) { return size-i/size; }                  // Zeilennummer
int sp (int i) { return i % size + 1; }                 // Spaltennummer
char spch (int i) { return (char) (i % size + 'a'); }   // Spaltenname


//Selbstgeschriebene Indexklasse
class Index
{
private:
  	int i;
  	void emergencyStop (int i) const;
public:
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
    
    virtual char ch () { if (this->ind.FeldFarbe) return '_'; return ' '; }
    virtual int pruefen( int start, int ende) { return 2; }
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
    virtual int pruefen( int start, int ende ) { return 3; }
};

class Bauer : public Figur
{
private:
public:
    Bauer (int idx, Farbe ff) : Figur (idx, ff) { }
    virtual char ch () { if (f == weiss) return 'B'; return 'b'; }
    virtual int pruefen(int start, int ende){
    	    if ( (start-ende)==8 || (start-ende)==16 ){ return 1; }
    	    else return 0;
    }
};

class Offizier : public Figur
{
private:
public:
    Offizier (int idx, Farbe ff) : Figur (idx, ff) { }
    virtual char ch () { return '#'; }
    virtual int pruefen(int start, int ende){ return 4; }
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
public:
    Springer (int idx, Farbe ff) : Offizier (idx, ff) { }
    virtual char ch () { if (f == weiss) return 'S'; return 's'; }
    virtual int pruefen(int start, int ende){
    	    int test = start-ende;
    	    switch ( test ){
    	    case -17:
    	    case -15:
    	    case -10:
    	    case -6:
    	    case 6:
    	    case 10:
    	    case 15:
    	    case 17:
    	    	    return 1; break;
    	    default: return 0; break;
    	    }
    }
};

class Laeufer : Offizier
{
private:
public:
    Laeufer (int idx, Farbe ff) : Offizier (idx, ff) { }
    virtual char ch () { if (f == weiss) return 'L'; return 'l'; }
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
    
    //**************************************************************************************
    void Zug( int start, int ende){
    	if (b[start]->pruefen(start, ende) && (b[ende]->ch()=='_'||b[ende]->ch()==' ')  ){
    	b[ende] = b[start];
    	clearFigure (start);}
    	else { emergencyStop(2); }
    }
    //**************************************************************************************
    
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

#endif
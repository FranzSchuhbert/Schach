#ifndef __klassen_h
#define __klassen_h




//========================================================================

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

class Index
{
private:
  	int i;
  	int FeldFarbe;
public:
	Index( int idx) { 	this->i 	= idx;
				this->FeldFarbe = size-idx/size+idx%size+1;}
};
/*
class Zug
{
private:
    Index a, e;
public:
};
*/

int FeldFarbe (int idx)                                 // weiss/schwarz
{
    return (zl (idx) + sp (idx)) % 2;
}

//========================================================================

enum Farbe { weiss, schwarz };

class Feld
{
private:
    int idx;
    //*************************************************************************************************************
public:
    Feld (int i) { Index ind(i); }
    virtual char ch () { if (this->ind.FeldFarbe) return '_'; return ' '; }
};
//***************************************************************************************************************
class Figur : public Feld
{
protected:
    Farbe f;
public:
    Figur (int ix, Farbe ff) : Feld (ix) { this->f = ff; }
    virtual char ch () { return '?'; }
};

class Bauer : public Figur
{
private:
public:
    Bauer (int idx, Farbe ff) : Figur (idx, ff) { }
    virtual char ch () { if (f == weiss) return 'B'; return 'b'; }
};

class Offizier : public Figur
{
private:
public:
    Offizier (int idx, Farbe ff) : Figur (idx, ff) { }
    virtual char ch () { return '#'; }
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
    Feld * Offizier (int idx, Farbe f);
public:
    Brett ();
    void print ();
};

Feld * Brett :: Offizier (int idx, Farbe f)

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

Brett::Brett ()
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
}

#endif
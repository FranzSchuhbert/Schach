//========================================================================

#include <cstdlib>
#include <iostream>

using namespace std;

//========================================================================

const int size = 8;
const int anz = size * size;

//========================================================================

/*
class Index
{
private:
    int i;
public:
};

class Zug
{
private:
    Index a, e;
public:
};
*/

//========================================================================

// unschoen; besser eine eigene Klasse Index wie oben angedeutet

/*
 *  zl
 *     ---------------------------------
 *  8  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
 *     ---------------------------------
 *  7  | 8 | 9 | 10| 11|   |   |   |   |
 *     ---------------------------------
 *  6  |   |   |   |   |   |   |   |   |
 *     ---------------------------------
 *  5  |   |   |   |   |   |   |   |   |
 *     ---------------------------------
 *  4  |   |   |   |   |   |   |   |   |
 *     ---------------------------------
 *  3  |   |   |   |   |   |   |   |   |
 *     ---------------------------------
 *  2  |   |   |   |   |   |   |   |   |
 *     ---------------------------------
 *  1  |   |   |   |   |   |   |   |   |
 *     ---------------------------------
 *       1   2   3   4   5   6   7   8      sp
 *       a   b   c   d   e   f   g   h      spch
 *
 */

int zl (int i) { return size-i/size; }                  // Zeilennummer
int sp (int i) { return i % size + 1; }                 // Spaltennummer
char spch (int i) { return (char) (i % size + 'a'); }   // Spaltenname

int idx (int z, int s)                                  // Feldindex
{
    int i;
    i = size * (size-z) + s - 1;
    if (zl (i) != z) exit (1);
    if (sp (i) != s) exit (1);
    return i;
}

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
public:
    Feld (int i) { idx = i; }
    virtual char ch () { if (FeldFarbe (idx)) return '_'; return ' '; }
};

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
    Feld * Offizier (int idx, Farbe f, int i);
public:
    Brett ();
    void print ();
};

Feld * Brett :: Offizier (int idx, Farbe f, int i)

{
    Feld * p;
    if ((i-1) % 7 == 0) p = (Feld *) new Turm (idx, f);
    else if ((i-2) % 5 == 0) p = (Feld *) new Springer (idx, f);
    else if ((i-3) % 3 == 0) p = (Feld *) new Laeufer (idx, f);
    else if (i == 4) p = (Feld *) new Dame (idx, f);
    else if (i == 5) p = (Feld *) new Koenig (idx, f);
    else { cout << "Fehler"; exit (1); }
    return p;
}

Brett::Brett ()
{
    int i;
    for (i = 0; i < anz; i++)
    {
        if (i < 8)
        {
            b [i] = Offizier (i, schwarz, sp (i));
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
            b [i] = Offizier (i, weiss, sp (i));
        }
    }
}

void Brett::print () // unschoen; besser mit cout << b;
{
    int i;
    cout << endl << "    ";
    for (i = 0; i < size; i++) cout << "  " << spch (i);
    cout << endl;
    for (i = 0; i < 3*size+4; i++) cout << "-";
    for (i = 0; i < anz; i++)
    {
        if (!(i % size))
        {
            cout << endl;
            cout.width (2);
            cout << zl (i) << ": ";
        }
        cout << "  " << (b [i] -> ch ());
    }
    cout << endl;
    for (i = 0; i < 3*size+4; i++) cout << "-";
    cout << endl << "    ";
    for (i = 0; i < size; i++) cout << "  " << spch (i);
}

//========================================================================

int main ()

{
    Brett b;

    b.print (); // unschoen; besser mit cout << b;
    cout << endl;
    return 0;
}

//========================================================================


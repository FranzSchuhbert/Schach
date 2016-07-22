#include <iostream>
#include "klassen.h"


using namespace std;

int main ()

{
     Brett b;
    b.print (); // unschoen; besser mit cout << b;
    b.createFigure( 24, 'B');
    b.print();
    b.clearFigure(11);
    b.clearFigure(12);
    b.print();
    b.Zug(48, 32);
    b.print();
    b.Zug(57, 51);
    b.print();
}
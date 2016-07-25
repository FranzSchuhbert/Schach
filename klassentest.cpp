#include <iostream>
#include "klassen.h"


using namespace std;

int main ()

{
    Brett b;
    b.print (); // unschoen; besser mit cout << b;
    b.print();
    b.clearFigure(11);
    b.clearFigure(12);
    b.print();
    //b.Zug(48, 32);
    //b.print();
    //b.clearFigure(51);
    b.createFigure( 30, 't');
    b.print();
    b.Zug(58, 30);
    b.print();
    b.clearFigure(8);
    b.Zug(0, 32);
    b.print();
    b.Zug(30, 26);
    b.print();
    b.Zug(26, 53);
    b.print();
}


/*Schachbrett Nummern zum Züge testen:

0	1	2	3	4	5	6	7
8	9	10	11	12	13	14	15
16	17	18	19	20	21	22	23
24	25	26	27	28	29	30	31
32	33	34	35	36	37	38	39
40	41	42	43	44	45	46	47
48	49	50	51	52	53	54	55
56	57	58	59	60	61	62	63

*/
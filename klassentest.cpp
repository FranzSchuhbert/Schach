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
    //b.Zug(48, 32);
    //b.print();
    b.Zug(57, 40);
    b.print();
}


/*Schachbrett zum Züge testen:

0	1	2	3	4	5	6	7
8	9	10	11	12	13	14	15
16	17	18	19	20	21	22	23
24	25	26	27	28	29	30	31
32	33	34	35	36	37	38	39
40	41	42	43	44	45	46	47
48	49	50	51	52	53	54	55
56	57	58	59	60	61	62	63

*/
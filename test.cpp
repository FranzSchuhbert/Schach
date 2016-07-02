#include "brett.h"
#include "koenig.h"
#include "dame.h"
#include "turm.h"
#include<string>

using namespace std;

int main(){
	Koenig k( "h" , 8);
	Dame d( "e" , 1);
	Turm t1( "a", 1);
	Turm t2( "h", 1);
	Brett b(k, d, t1, t2);
	k.zuege();
}
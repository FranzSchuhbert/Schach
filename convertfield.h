#ifndef __converterfield_h
#define __converterfield_h

#include<string>


int convertfield(std::string test){
	int rueck;
	if (test=="a"){rueck=0;}
	else if (test=="b"){rueck=1;}
	else if (test=="c"){rueck=2;}
	else if (test=="d"){rueck=3;}
	else if (test=="e"){rueck=4;}
	else if (test=="f"){rueck=5;}
	else if (test=="g"){rueck=6;}
	else if (test=="h"){rueck=7;}
	else{ rueck = 10;}
	return rueck;
}
std::string convertback(int test){
	std::string rueck;
	if (test==0){rueck="a";}
	else if (test==1){rueck="b";}
	else if (test==2){rueck="c";}
	else if (test==3){rueck="d";}
	else if (test==4){rueck="e";}
	else if (test==5){rueck="f";}
	else if (test==6){rueck="g";}
	else if (test==7){rueck="h";}
	else{ rueck="X";}
	return rueck;
}



	
#endif
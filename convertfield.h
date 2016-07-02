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
	
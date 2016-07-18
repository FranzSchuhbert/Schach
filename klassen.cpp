#include "klassen.h"

class IndexException : std::exception{};
void Index::emergencyStop (int i) const{
	std::cout << std::endl << "+++ Error in class Index; Error number: " << i << std::endl;
	throw new IndexException;
}
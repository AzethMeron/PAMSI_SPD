#include <iostream>
#include <fstream>
#include "tester.hpp"
#include "spd.hpp"

using namespace std;

int main(int argc, char **argv)
{
	ifstream wejscie("data.txt");
	ostream& wyjscie = cout;
	ofstream logs("log.txt");
	
	if(!wejscie.good()) return -1;
	if(!logs.good()) return -2;
	
	// Tutaj stworzyc obiekt testara i wywolac Start(false)
	SPDTester Obiekt(wejscie,wyjscie,logs);
	Obiekt.Start(false);
	
	return 0;
}


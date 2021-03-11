#include <iostream>
#include <string>
#include "Stream.hpp"
#include "Loader.hpp"
#include "Generator.hpp"

int main()
{
	std::cout << "Wpraowdz nazwe pliku do zapisu" << std::endl;
	std::string filename;
	std::cin >> filename;
	ofstream file(filename);
	
	Loader LoadSets;
	Generator Gen(file);
	Gen.Start(LoadSets.main());
	
	return 0;
}

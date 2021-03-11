#include <iostream>
#include <fstream>
#include "lista.hpp"
#include "macierz.hpp"
#include "results.hpp"
#include "Tester.h"
#include "algorithms.hpp"

/* ************************************************************************************ */
// Jakub Grzana W4 AiR, 241530
// Przy tworzeniu programu wspolpracowalem z Ewa Zietek. Razem rozpracowywalismy algorytmy
// i pracowalismy nad implementacja. Same programy napisalismy jednak osobno i zaden
// element kodu nie zostal od drugiego skopiowany.
/* ************************************************************************************ */

template<typename InputDataType>
class GraphTester : public Tester<Results,InputDataType>
{
	protected:
		std::string algorytm;
		InputDataType readInput(std::istream& input)
		{
			InputDataType output;
			input >> output;
			return output;
		}
		Results runAlgorithm(const InputDataType& data)
		{
			if(algorytm == "dijkstra")
			{
				return Dijkstra(data);
			}
			else if(algorytm == "bellman")
			{
				return Bellman(data);
			}
			else
			{
				std::cerr << std::endl << "Nierozpoznany algorytm." << std::endl;
				exit(3);
			}
		}
	public:
		GraphTester(const std::string& temp)
		{
			algorytm = temp;
		}
};

int main(int argc, char **argv)
{
	if(argc != 3)
	{ std::cerr << "Zla liczba argumentow wywolania. Wymagane 2" << std::endl << "1 - reprezentacja., lista/macierz" << std::endl << "2 - algorytm, dijkstra/bellman" << std::endl; exit(1); }
	
	std::string reprezentacja = argv[1];
	std::string algorytm = argv[2];
	
	std::ifstream input;
	std::ofstream output, csv;
	
	std::cout << "Podaj nazwe pliku wejsciowego" << std::endl;
	std::string INPUT;
	std::cin >> INPUT;
	input.open(INPUT.c_str());
	if(input.is_open() == false) 
	{ std::cerr << "Blad otwarcia pliku do odczytu" << std::endl; exit(2); }
	
	std::cout << "Podaj nazwy plikow wyjsciowych (.csv)" << std::endl;
	std::string OUTPUT, CSV;
	std::cin >> OUTPUT >> CSV;
	output.open(OUTPUT.c_str());
	csv.open(CSV.c_str());	
		
	if(reprezentacja == "macierz")
	{
		GraphTester<GraphMatrix> temp(algorytm);
		temp.runTests(input,output,csv);
	}
	else if(reprezentacja == "lista")
	{
		GraphTester<GraphList> temp(algorytm);
		temp.runTests(input,output,csv);
	}
	
	return 0;
}


#ifndef GENERATOR_HPP
#define GENERATOR_HPP
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include "InformationSet.hpp"
#include "Stream.hpp"
#include "lista.hpp"

#define WAGE_MIN 1
#define WAGE_MAX 10
#define PERCENTAGE 100

inline int Loss(const int& min, const int& max)
{
	return ((rand()%(max-min+1))+min);
}

/* Klasa sluzaca do unikniecia sytuacji, gdzie jeden wierzcholek ma 10 krawedzi laczacych go z tym samym wierzcholkiem... albo 10 petli */
class LesserGenerator
{
	protected:
		std::vector<unsigned int> data; // kontener wypelniony indeksami. Warto wiedziec, ze data[i] moze byc rowne i, ale nie musi
	public:
		LesserGenerator(const unsigned int& size, const unsigned int& excluded) : data(size-1)
		{
			unsigned int j = 0;
			for(unsigned int i = 0; i < data.size(); i++)
			{
				if(j == excluded) j++;
				data[i] = j;
				j++;
			}
		}
		inline unsigned int size(void) const { return data.size(); }
		unsigned int LossAndRemove(void)
		{
			// Teoretycznie, dzieki wzorowi na liczbe krawedzi grafu ponizszy przypadek nie powinien zajsc. Oby tak bylo
			if(size() == 0)	{	std::cerr << std::endl << "Proba losowania z pustego zbioru" << std::endl; }
			// Wybieramy losowy index z kontenera data
			unsigned int index = Loss(0,size()-1);;
			unsigned int output = data[index];
			data[index] = data[size()-1];
			data.pop_back();
			return output;
		}
};

class Generator
{
	protected:
		ofstream& file;
		GraphList GenerateOne(const unsigned int& size, const unsigned int& density)
		{
			GraphList output;
			output.resize(size);
			// o gestosci: http://davinci.mimuw.edu.pl/matematyka/gestosc-grafu
			//unsigned int m = (density * size * (size - 1)) / 2; // liczba krawedzi *100
			//m /= size; // srednia liczba krawedzi na wierzcholek *100
			// ta dwojka na oko wydaje sie bledem
			// wtf
			unsigned int m = (density * (size - 1)); // srednia liczba krawedzi na wierzcholek *100
			unsigned int mtemp = 0; // zmienna do obliczania liczby krawedzi dla danego wierzcholka, by zachowac mozliwie jak najblizsza do zadeklarowanej gestosc
			for(unsigned int i = 0; i < output.size(); i++)
			{
				mtemp += m; 
				output[i].resize(int(mtemp/PERCENTAGE));
				mtemp = mtemp % PERCENTAGE;
				LesserGenerator index_bank(size,i);
				for(ListType& Wsk : output[i])
				{
					Wsk.vertex = index_bank.LossAndRemove();
					Wsk.wage = Loss(WAGE_MIN,WAGE_MAX);
				}
			}
			return output;
		}
	public:
		Generator(ofstream& temp) : file(temp)
		{	srand(time(NULL));	}
		void Start(const std::vector<InformationSet>& sets)
		{
			std::cout << std::endl;
			for(unsigned int i = 0; i < sets.size(); i++)
			{
				for(unsigned int j = 0; j < sets[i].times; j++)
				{
					std::cout << "Generowanie: Zestaw " << i << " Instancja " << j << " " << sets[i] << std::endl;
					GraphList temp = GenerateOne(sets[i].size,sets[i].density);
					std::cout << "Zapisywanie...";
					//file << " " << sets[i].density << " " << temp << "\n";
					file << temp << "\n";
				}
			}
		}
};

#endif

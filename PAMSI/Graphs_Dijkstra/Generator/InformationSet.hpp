#ifndef INFORMATIONSET_HPP
#define INFORMATIONSET_HPP

#include <iostream>

#define NUMBER_OF_SETS 100

struct InformationSet
{
	std::string representation;
	unsigned int size;
	unsigned int density;
	unsigned int times; // setowane na 100, ale zostawiam na wypadek gdyby trzeba bylo to jednak dodac
};

std::istream& operator >> (std::istream& stream, InformationSet& data)
{
	std::cout << std::endl << "Podaj liczbe wierzcholkow (int) Cokolwiek innego spowoduje rozpoczecie zapisywania " << std::endl;
	stream >> data.size;
	std::cout << std::endl << "Podaj gestosc (1-100) " << std::endl;
	stream >> data.density;
	data.times = NUMBER_OF_SETS;
	std::cout << std::endl;
	return stream;
}

std::ostream& operator << (std::ostream& stream, const InformationSet& data)
{
	stream << " " << "Rozmiar: " << data.size << " " << "Gestosc: " << data.density;
	return stream;
}

#endif

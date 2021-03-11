#ifndef LISTA_HPP
#define LISTA_HPP

#include <iostream>
#include <list>
#include <vector>

struct Amalgamate
{
	public:
		unsigned int vertex;
		unsigned int wage;
};

typedef Amalgamate ListType;

class GraphList
{
	private:
		
	protected:
		std::vector<std::list<ListType>> data;
	public:
		void resize(const unsigned int& size) { this->data.resize(size); }
		unsigned int size(void) const { return this->data.size(); }
		const std::list<ListType>& operator [] (const unsigned int& ind) const { return this->data[ind]; }
		      std::list<ListType>& operator [] (const unsigned int& ind)       { return this->data[ind]; }
};

std::istream& operator >> (std::istream& stream, GraphList& object)
{
	unsigned int size = 0;
	stream >> size;
	object.resize(size);
	for(unsigned int i = 0; i < object.size(); i++)
	{
		unsigned int edges = 0;
		stream >> edges;
		object[i].resize(edges);
		for(ListType& Wsk : object[i])
		{
			stream >> Wsk.vertex;
			stream >> Wsk.wage;
		}
	}
	return stream;
}

#endif

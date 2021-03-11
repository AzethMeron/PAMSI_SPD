#ifndef RESULTS_HPP
#define RESULTS_HPP

#include <iostream>
#include "vector"
#define INF 999999

struct ResultCell
{
	unsigned int d; // suma wag
	long int p; // poprzedni
	bool processed;
	
	ResultCell()
	{
		d = INF;
		p = -1;
		processed = false;
	}
};

class Results
{
	protected:
		std::vector<ResultCell> data;
	public:
		unsigned int size(void) const { return data.size(); }
		void resize(const unsigned int& size) { data.resize(size); data[0].d = 0; }
		ResultCell&       operator [] (const unsigned int& ind)       { return data[ind]; }
		const ResultCell& operator [] (const unsigned int& ind) const { return data[ind]; }
};

std::ostream& operator << (std::ostream& stream, Results results)
{
	stream << results.size() << std::endl;
	for(unsigned int i = 0; i < results.size(); i++)
	{
		stream << results[i].d << " ";
	}
	stream << std::endl;
	for(unsigned int i = 0; i < results.size(); i++)
	{
		stream << results[i].p << " ";
	}
	stream << std::endl;
	return stream;
}

#endif

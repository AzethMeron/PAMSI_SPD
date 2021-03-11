#ifndef MACIERZ_HPP
#define MACIERZ_HPP

#include <iostream>
#include <vector>

typedef unsigned int MatrixType;

class GraphMatrix
{
	private:
		
	protected:
		std::vector<std::vector<MatrixType>> data;
	public:
		void resize(const unsigned int& size) 
		{ 
			this->data.resize(size); 
			for(unsigned int i = 0; i < data.size(); i++)
			{
				data[i].resize(size);
				for(unsigned int j = 0; j < data[i].size(); j++)
				{
					data[i][j] = 0;
				}
			}
		}
		unsigned int size(void) const { return this->data.size(); }
		const std::vector<MatrixType>& operator [] (const unsigned int& ind) const { return this->data[ind]; }
		      std::vector<MatrixType>& operator [] (const unsigned int& ind)       { return this->data[ind]; }
};

std::istream& operator >> (std::istream& stream, GraphMatrix& object)
{
	unsigned int size = 0;
	stream >> size;
	object.resize(size);
	for(unsigned int i = 0; i < object.size(); i++)
	{
		unsigned int edges = 0;
		stream >> edges;
		
		for(unsigned int j = 0; j < edges; j++)
		{
			unsigned int column = 0, wage = 0;
			stream >> column;
			stream >> wage;
			object[i][column] = wage;
		}
	}
	return stream;
}

#endif

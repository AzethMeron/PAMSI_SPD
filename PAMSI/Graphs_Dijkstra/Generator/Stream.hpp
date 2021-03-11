#ifndef STREAM_HPP
#define STREAM_HPP

#include <iostream>
#include <fstream>
#include <string>

/*
	NIE RÓB TAKICH KLAS NIGDY WIECEJ. NIGDY	
*/

class ofstream
{
	public:
		std::ofstream stream;
		ofstream(const std::string& name)
		{
			stream.open(name.c_str());
			if(!stream.is_open())
			{
				std::cerr << std::endl << "Blad otwarcia pliku do zapisu. Nazwa: " << name << std::endl;	
			}
		}
		~ofstream()
		{
			stream.close();
		}
};

template<typename Type>
ofstream& operator << (ofstream& stream, const Type& data)
{
	stream.stream << data;
	return stream;
}

#endif

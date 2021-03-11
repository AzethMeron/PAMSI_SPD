#ifndef LOADER_HPP
#define LOADER_HPP

#include <iostream>
#include <vector>
#include "Stream.hpp"
#include "InformationSet.hpp"

class Loader
{
	protected:
		std::vector<InformationSet> data;
	public:
		void show_sets()
		{
			for(unsigned int i = 0; i < data.size(); i++)
			{
				std::cout << data[i] << std::endl;
			}
		}
		std::vector<InformationSet> main(void)
		{
			while(std::cin.good())
			{
				std::cout << std::endl << " GENERATOR GRAFOW " << std::endl;
				show_sets();
				InformationSet temp;
				std::cin >> temp;
				if(std::cin.good()) data.push_back(temp);
				std::cout << std::endl << std::endl;
			}
			return this->data;
		}			
};



#endif

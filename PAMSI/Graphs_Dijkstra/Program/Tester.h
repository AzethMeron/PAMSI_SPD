#ifndef tester_h
#define tester_h

#include <vector>
#include "Timer.h"

template<typename OutputDataType,typename InputDataType>
class Tester
{
	protected:
		virtual InputDataType readInput(std::istream& input) = 0;
		virtual OutputDataType runAlgorithm(const InputDataType& data) = 0;
	public:
		void runTests(std::istream& input, std::ostream& output, std::ostream& timesoutput)
		{
			Timer Time;
			while (true)
			{
				std::vector<double> time_set;
				for(int i = 0; i < 100; i++)
				{
					InputDataType temp_input = readInput(input);
					if (input.good() == false) break;
					Time.start();
					OutputDataType temp_output = runAlgorithm(temp_input);
					Time.stop();
					output << temp_output << std::endl; //if(i == 99)
					time_set.push_back(Time.show_results(i));
				}
				if (input.good() == false) break;
				Time.show_average_time(time_set,timesoutput);
			}
		}
};

#endif 

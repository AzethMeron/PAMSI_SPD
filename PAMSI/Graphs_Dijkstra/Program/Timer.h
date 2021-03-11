#ifndef timer_h
#define timer_h

#include <vector>
#include <chrono>
#include <iostream>

class Timer 
{
	private:
		double nanoseconds(void) const { return std::chrono::duration_cast<std::chrono::nanoseconds>(Stop - Start).count(); }
		double miliseconds(void) const { const double constant = 1e-6; return nanoseconds() * constant; }
	protected:
		std::chrono::high_resolution_clock::time_point Start;
		std::chrono::high_resolution_clock::time_point Stop;
	public:
		void start(void) { Start = std::chrono::high_resolution_clock::now(); }
		void stop(void) { Stop = std::chrono::high_resolution_clock::now(); }
		double show_results(const int& data_number) const
		{
			double output = miliseconds();
			return output;
		}
		void show_average_time(const std::vector<double>& time_set, std::ostream& timesoutput)
		{
			std::cout << std::endl << "******** Processing data finished ********" << std::endl;
			double output = 0;
			for(unsigned int i = 0; i < time_set.size(); i++)
			{
				output+=time_set[i];
			}
			output /= 100;
			std::cout << "Avarage time: " << output << " miliseconds" << std::endl;
			timesoutput << output << "; " ;
		}
};

#endif 

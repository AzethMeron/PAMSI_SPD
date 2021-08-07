
#include "Stat.hpp"

#include <chrono>
#include <vector>

//////////////////////////////////////////////////////////////////////////

void Timer::Start(void) 
{ 
	start = std::chrono::high_resolution_clock::now(); 
}

void Timer::Stop(void) 
{ 
	stop = std::chrono::high_resolution_clock::now(); 
}

double Timer::ns(void) const 
{ 
	return std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count(); 
}

double Timer::ms(void) const 
{ 
	const double constant = 1e-6; return ns() * constant; 
}

double Timer::s(void) const 
{ 
	const double constant = 1e-3; return ms() * constant; 
}

//////////////////////////////////////////////////////////////////////////
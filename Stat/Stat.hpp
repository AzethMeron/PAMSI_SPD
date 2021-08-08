#ifndef STAT_HPP
#define STAT_HPP

#include <chrono>
#include <vector>
#include <cmath>

//////////////////////////////////////////////////////////////////////////

class Timer
{
	protected:
		std::chrono::high_resolution_clock::time_point start;
		std::chrono::high_resolution_clock::time_point stop;
	public:
		void Start(void); 
		void Stop(void); 
		double ns(void) const; 
		double ms(void) const; 
		double s(void) const; 
};

//////////////////////////////////////////////////////////////////////////

// requirements for TYPE, there're some
// 		~TYPE();
// 		TYPE();
// 		TYPE(const TYPE&);
// 		TYPE(const TYPE&&);
// 		TYPE& operator = (const TYPE&);
// 		TYPE& operator = (const int&); 
// 		TYPE operator + (const TYPE&) const;
// 		TYPE operator / (const TYPE&) const;
// 		TYPE std::pow(TYPE, int);
// 		TYPE std::sqrt(TYPE);
// 		bool operator < (const TYPE&) const;
// 		std::ostream& operator << (std::ostream&, const TYPE&);
template<typename TYPE>
class DataSeries
{
	protected:
		std::vector<TYPE> dataseries;
		TYPE sum;
	public:
		// tools
		void Add(const TYPE& time);			// O(1)
		TYPE Average(void) const; 			// O(1)
		TYPE Variance(void) const;			// O(n)
		TYPE StandardDeviation(void) const;	// O(n)
		TYPE Median(void) const; 			// O(nlogn)
		DataSeries<TYPE> Sorted(void) const;// O(nlogn)
		DataSeries<TYPE> Reversed(void) const; // O(n)
		// getters 
		int Size(void) const;
		TYPE operator[] (const int& ind) const;
		// Constructors
		DataSeries();
};

typedef DataSeries<double> TimeSeries;

//////////////////////////////////////////////////////////////////////////

template<typename TYPE>
void DataSeries<TYPE>::Add(const TYPE& data)
{
	this->dataseries.push_back(data);
	this->sum = this->sum + data;
}

template<typename TYPE>
TYPE DataSeries<TYPE>::Average(void) const
{
	TYPE size = this->Size();
	return (this->sum / size );
}

template<typename TYPE>
TYPE DataSeries<TYPE>::Variance(void) const
{
	TYPE average = this->Average();
	TYPE variance = 0;
	for(int i = 0; i < this->Size(); ++i)
	{
		variance = variance + pow( (this->dataseries.at(i) - average), 2);
	}
	TYPE size = this->Size();
	variance = variance / size;
	return variance;
}

template<typename TYPE>
TYPE DataSeries<TYPE>::StandardDeviation(void) const
{
	return sqrt(this->Variance());
}

template<typename TYPE>
TYPE DataSeries<TYPE>::Median(void) const
{
	DataSeries<TYPE> sorted = this->Sorted();
	if(sorted.Size() == 0) throw -1;
	if(sorted.Size() % 2)
	{
		int index = floor(sorted.Size() / 2);
		return sorted[index];
	}
	else
	{
		int index = ceil(sorted.Size() / 2);
		TYPE size = 2;
		return (sorted[index-1] + sorted[index]) / size;
	}
}

template<typename TYPE>
DataSeries<TYPE> DataSeries<TYPE>::Sorted(void) const
{
	DataSeries<TYPE> sorted = *this;
	sort(sorted.dataseries.begin(), sorted.dataseries.end());
	return sorted;
}

template<typename TYPE>
DataSeries<TYPE> DataSeries<TYPE>::Reversed(void) const
{
	DataSeries<TYPE> reversed = *this;
	std::reverse(reversed.dataseries.begin(), reversed.dataseries.end());
	return reversed;
}

template<typename TYPE>
std::ostream& operator << (std::ostream& ostream, const DataSeries<TYPE>& series)
{
	for(int i = 0; i < series.Size(); ++i)
	{
		ostream << series[i] << ' ';
	}
	return ostream;
}

template<typename TYPE>
int DataSeries<TYPE>::Size(void) const
{
	return this->dataseries.size();
}

template<typename TYPE>
TYPE DataSeries<TYPE>::operator[] (const int& ind) const
{
	return this->dataseries.at(ind);
}

template<typename TYPE>
DataSeries<TYPE>::DataSeries() : dataseries()
{
	this->sum = 0;
}

//////////////////////////////////////////////////////////////////////////

#endif

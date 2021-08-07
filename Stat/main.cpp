#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <cmath>
#include "Stat.hpp"
using namespace std;

// sortujemy rosnąco


typedef int TYPE;
#define SIZE 100000
#define NUM 100

int loss(const int& min, const int& max)
{
	return (rand()%(max-min+1)+min);
}

int binarySearch(const vector<TYPE>& a, TYPE item,
                 int low, int high)
{
    if (high <= low)
        return (item > a[low]) ?
                (low + 1) : low;

    int mid = (low + high) / 2;

    if (item == a[mid])
        return mid + 1;

    if (item > a[mid])
        return binarySearch(a, item,
                            mid + 1, high);
    return binarySearch(a, item, low,
                        mid - 1);
}

vector<TYPE> insertion_sort(const vector<TYPE>& array)
{
	vector<TYPE> output;
	output.push_back(array.front());
	for(int i = 1; i < array.size(); ++i)
	{
		int index = binarySearch(output, array[i], 0, output.size()-1);
		output.insert(output.begin()+index, array[i]);
	}
	return output;
}

vector<vector<TYPE>> GenerateArrays(const int& size, const int& num, const int& min, const int& max)
{
	vector<vector<TYPE>> arrays(num);
	for(int i = 0; i < num; ++i)
	{
		arrays.at(i).resize(size);
		for(int j = 0; j < size; ++j)
		{
			arrays.at(i).at(j) = loss(min,max);
		}
	}
	return arrays;
}

int main()
{
	srand(time(NULL));
	vector<vector<TYPE>> arrays = GenerateArrays(SIZE, NUM, -SIZE, SIZE);

	TimeSeries time_insert;
	TimeSeries time_sort;
	for(int i = 0; i < arrays.size(); ++i)
	{
		{ vector<TYPE> array = arrays.at(i);
		Timer clock;
		clock.Start();
		sort(array.begin(), array.end());
		clock.Stop();
		time_sort.Add(clock.ms()); }

		{  Timer clock;
		clock.Start();
		vector<TYPE> array = insertion_sort(arrays.at(i));
		clock.Stop();
		time_insert.Add(clock.ms());
		}
	}

	cout << "========== RESULTS BUILT-IN ==========" << endl
	 << "Average: " << time_sort.Average() << " ms" << endl
	 << "Standard deviation: " << time_sort.StandardDeviation() << " ms" << endl
	 << endl;

	cout << "========== RESULTS INSERT ==========" << endl
	 << "Average: " << time_insert.Average() << " ms" << endl
	 << "Standard deviation: " << time_insert.StandardDeviation() << " ms" << endl
	 << endl;

	return 0;
}

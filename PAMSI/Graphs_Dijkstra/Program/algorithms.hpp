#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <vector>
#include "macierz.hpp"
#include "lista.hpp"
#include "results.hpp"

/* ************************************************************************ */

Results Dijkstra(const GraphList& input)
{
	Results output;
	output.resize(input.size());
	unsigned int testified = 0;
	while(true)
	{
		/* SZUKAMY NAJMNIEJSZEJ WAGI */
		bool control = false;
		unsigned int wage = INF;
		for(unsigned int i = 0; i < output.size(); i++)
		{
			if(output[i].processed == false)
			{
				if(control == false) // ratuje program kiedy wierzcholek jest izolowany
				{
					wage = output[i].d;
					testified = i;
				}
				
				control = true;
				
				if(wage > output[i].d)
				{
					wage = output[i].d;
					testified = i;
				}
			}
		}
		/* JESLI KONIEC, TO BREAK */
		if(control == false) break;
		/* PRZENOSIMY ZE ZBIORU DO ZBIORU */
		output[testified].processed = true;
		/* SPRAWDZAMY SASIADOW */
		for(const ListType& Wsk : input[testified])
		{
			if(output[Wsk.vertex].d > Wsk.wage + output[testified].d)
			{
				output[Wsk.vertex].d = Wsk.wage + output[testified].d;
				output[Wsk.vertex].p = testified;
			}
		}
	}
	return output;
}

/* ************************************************************************ */

Results Dijkstra(const GraphMatrix& input)
{
	Results output;
	output.resize(input.size());
	unsigned int testified = 0;
	while(true)
	{
		/* SZUKAMY NAJMNIEJSZEJ WAGI */
		bool control = false;
		unsigned int wage = INF;
		for(unsigned int i = 0; i < output.size(); i++)
		{
			if(output[i].processed == false)
			{
				if(control == false) // ratuje program kiedy wierzcholek jest izolowany
				{
					wage = output[i].d;
					testified = i;
				}
				
				control = true;
				
				if(wage > output[i].d)
				{
					wage = output[i].d;
					testified = i;
				}
			}
		}
		/* JESLI KONIEC, TO BREAK */
		if(control == false) break;
		/* PRZENOSIMY ZE ZBIORU DO ZBIORU */
		output[testified].processed = true;
		/* SPRAWDZAMY SASIADOW */
		for(unsigned int j = 0; j < input[testified].size(); j++)
		{
			if(input[testified][j] != 0)
			{
				if(output[j].d > output[testified].d + input[testified][j])
				{
					output[j].d = output[testified].d + input[testified][j];
					output[j].p = testified;
				}
			}
		}
	}
	return output;
}

/* ************************************************************************ */

Results Bellman(const GraphList& input)
{
	Results output;
	output.resize(input.size());
	/* GLOWNA PETLA ITERACYJNA */
	for(unsigned int i = 0; i < input.size()-1; i++) 
	{
		bool control = false;
		/* SPRAWDZAMY SASIADOW WSZYSTKICH WIERZCHOLKOW */
		for(unsigned int j = 0; j < input.size(); j++)
		{
			for(const ListType& Wsk : input[j])
			{
				/* POROWNANIE JAK U DIJKSTRY */
				if(output[Wsk.vertex].d > output[j].d + Wsk.wage)
				{
					control = true;
					output[Wsk.vertex].d = output[j].d + Wsk.wage;
					output[Wsk.vertex].p = j;
				}
			}
		}
		/* JESLI NIE NASTAPILA ZMIANA, BREAK */
		if(control == false) break;
	}
	return output;
}

/* ************************************************************************ */

Results Bellman(const GraphMatrix& input)
{
	Results output;
	output.resize(input.size());
	/* GLOWNA PETLA ITERACYJNA */
	for(unsigned int i = 0; i < input.size()-1; i++) 
	{
		bool control = false;
		/* SPRAWDZAMY SASIADOW WSZYSTKICH WIERZCHOLKOW */
		for(unsigned int j = 0; j < input.size(); j++)
		{
			for(unsigned int z = 0; z < input[j].size(); z++)
			{
				if(input[j][z] != 0)
				{
					/* POROWNANIE JAK U DIJKSTRY */
					if(output[z].d > output[j].d + input[j][z])
					{
						control = true;
						output[z].d = output[j].d + input[j][z];
						output[z].p = j;
					}
				}
			}
		}
		/* JESLI NIE NASTAPILA ZMIANA, BREAK */
		if(control == false) break;
	}
	return output;
}

/* ************************************************************************ */

#endif

#ifndef PRZERWANIA_HPP
#define PRZERWANIA_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include "kopiec.hpp"
#include "Struktury.hpp"

using namespace std;

namespace Schrage
{
	Output Przerwania(const vector<Element>& wejscie)
	{
		// Inicjalizacja wyjscia
		Output wyjscie;
		wyjscie.dlugosc = 0;
			
		// Referencje - dla zachowania zgodnosci kodu z pseudokodem
		int& Cmax = wyjscie.dlugosc; // Minimalny czas wykonywania
		vector<int>& Pi = wyjscie.permutacja;
		// Zmienne lokalne
		int t = 0; // Chwila czasowa
		Element l; l.R = 999999; l.P = 999999; l.Q = 999999; l.index = -1;
		// Kopce
		Heap<Element> kopiec_r(min_r, wejscie); // N
		Heap<Element> kopiec_q(max_q); // G
		// Dobra, jednak zmodyfikowalem, poniewaz uzywam elmentow zamiast indeksow
		// Generalnie: e to element, nie index, a zbiory G, N zawieraja elementy zamiast indeksow
		// N przerobilem na kopiec_r, G na kopiec_q
		while(kopiec_r.size() || kopiec_q.size())
		{
			label:
			while(kopiec_r.size() && kopiec_r.front().R <= t)
			{
				Element e = kopiec_r.front();
				kopiec_r.pop();
				kopiec_q.push(e);
				if(e.Q > l.Q)
				{
					l.P = t - e.R;
					t = e.R;
					if(l.P > 0)
					{
						kopiec_q.push(l);
					}
				}
			}
			if(!kopiec_q.size())
			{
				t = kopiec_r.front().R;
				goto label;
			}
			
			Element e = kopiec_q.front();
			kopiec_q.pop();		
			
			Pi.push_back(e.index);
			l = e;
			t = t + e.P;
			Cmax = max(Cmax,t+e.Q);
		}
							
		return wyjscie;
	}
}

#endif

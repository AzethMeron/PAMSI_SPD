#ifndef BEZ_PRZERWAN_HPP
#define BEZ_PRZERWAN_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include "kopiec.hpp"
#include "Struktury.hpp"

using namespace std;

namespace Schrage
{
	Output BezPrzerwan(const vector<Element>& wejscie)
	{
		// Inicjalizacja wyjscia
		Output wyjscie;
		wyjscie.dlugosc = 0;
		wyjscie.permutacja.resize(wejscie.size());
			
		// Referencje - dla zachowania zgodnosci kodu z pseudokodem
		int& Cmax = wyjscie.dlugosc; // Minimalny czas wykonywania
		vector<int>& Pi = wyjscie.permutacja;
		// Zmienne lokalne
		int t = 0; // Chwila czasowa
		int k = 0; // Pozycja w permutacji
		// Kopce
		Heap<Element> kopiec_r(min_r, wejscie);
		Heap<Element> kopiec_q(max_q);
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
			}
			if(!kopiec_q.size())
			{
				//t = N[min_r(N)].R;
				t = kopiec_r.front().R;
				goto label;
			}
			
			Element e = kopiec_q.front();
			kopiec_q.pop();		
			
			Pi[k] = e.index;
			t = t + e.P;
			Cmax = max(Cmax,t+e.Q);
			++k;
		}
							
		return wyjscie;
	}
}

#endif

#ifndef SPD_HPP
#define SPD_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include "tester.hpp"

using namespace std;

struct Element 
{
	int R;
	int P;
	int Q;
	int index;
};

class Output
{
	public:
		int dlugosc;
		vector<int> permutacja;
};

inline int min_r(const vector<Element>& zestaw)
{
	int min = 999999;
	int ind = -1;
	
	for(unsigned int i = 0; i < zestaw.size(); ++i)
	{
		if(min > zestaw[i].R)
		{
			min = zestaw[i].R;
			ind = i;
		}
	}
	
	return ind;
}

inline int max_q(const vector<Element>& zestaw)
{
	int max = -1;
	int ind = -1;
	
	for(unsigned int i = 0; i < zestaw.size(); ++i)
	{
		if(max < zestaw[i].Q)
		{
			max = zestaw[i].Q;
			ind = i;
		}
	}
	
	return ind;
}

Output Schrage(const vector<Element>& wejscie)
{
	// Inicjalizacja wyjscia
	Output wyjscie;
	wyjscie.dlugosc = 0;
		
	// Referencje - dla zachowania zgodnosci kodu z pseudokodem
	int& Cmax = wyjscie.dlugosc; // Minimalny czas wykonywania
	vector<int>& Pi = wyjscie.permutacja;
	vector<Element> N = wejscie; // Zbior zadan nieuszeregowanych
	// Zmienne lokalne
	int t = 0; // Chwila czasowa
	Element l; l.R = 999999; l.P = 999999; l.Q = 999999; l.index = -1;
	vector<Element> G; // Zbior zadan gotowych do realizacji
		
	// Dobra, jednak zmodyfikowalem, poniewaz uzywam elmentow zamiast indeksow
	// Generalnie: e to element, nie index, a zbiory G, N zawieraja elementy zamiast indeksow
	while(G.size() || N.size())
	{
		label:
		while(N.size() && N[min_r(N)].R <= t)
		{
			int e_ind = min_r(N);
			Element e = N[e_ind];
			swap(N[e_ind],N.back());
			N.pop_back();
			G.push_back(e);
			if(e.Q > l.Q)
			{
				l.P = t - e.R;
				t = e.R;
				if(l.P > 0)
				{
					G.push_back(l);
				}
			}
		}
		if(!G.size())
		{
			t = N[min_r(N)].R;
			goto label;
		}
		
		int e_ind = max_q(G);
		Element e = G[e_ind];
		swap(G[e_ind],G.back());
		G.pop_back();				
		
		Pi.push_back(e.index);
		l = e;
		t = t + e.P;
		Cmax = max(Cmax,t+e.Q);
	}
						
	return wyjscie;
}

class SPDTester : public Tester<vector<Element>,Output>
{
	protected:
		vector<Element> WczytajPojedynczeWejscie(istream& wejscie) override
		{
			unsigned int liczba_elementow = 0;
			wejscie >> liczba_elementow;
			vector<Element> wyjscie(liczba_elementow);
			for(unsigned int i = 0; i < wyjscie.size(); ++i)
			{
				wejscie >> wyjscie[i].R;
				wejscie >> wyjscie[i].P;
				wejscie >> wyjscie[i].Q;
				wyjscie[i].index = i;
			}
			return wyjscie;
		}
	public:
		Output Algorytm(vector<Element>& wejscie, ostream& logs, const int& index)
		{
			//logs << wejscie.size() << endl;	for(unsigned int i = 0; i < wejscie.size(); ++i)	{ logs << wejscie[i].R << ' ' << wejscie[i].P << ' ' << wejscie[i].Q << endl; }
			return Schrage((const vector<Element>&)wejscie);
		}
		
		void WyswietlWynik(ostream& wyjscie,const Output& wynik, const int& index, const double& ms)
		{
			wyjscie << "Zakonczono przetwarzanie zestawu: " << index << endl;
			wyjscie << "Dlugosc uszeregowania: " << wynik.dlugosc << endl;
			wyjscie << "Czas pracy algorytmu: " << ms << " [ms]" << endl;
			wyjscie << "Permutacja:";
			for(unsigned int i = 0; i < wynik.permutacja.size(); ++i)
			{
				wyjscie << ' ' << (wynik.permutacja[i]+1);
			}
		}
		
		SPDTester(std::istream& we, std::ostream& wy, std::ostream& lo) : Tester(we, wy, lo) {}
};

#endif

#ifndef SPD_HPP
#define SPD_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include "tester.hpp"
#include "Schrage/BezPrzerwan.hpp"
#include "Schrage/Przerwania.hpp"

using namespace std;

int C(const vector<Element>& dane, const vector<int>& X)
{
	int m = 0;
	int c = 0;
	for(unsigned int i = 0; i < dane.size(); ++i)
	{
		int j = X[i];
		m = max(m,dane[j].R) + dane[j].P;
		c = max(m+dane[j].Q,c);
	}
	return c;
}

int C(const vector<Element>& dane, const vector<int>& X, unsigned int l, unsigned int r)
{
	int m = 0;
	int c = 0;
	for(unsigned int i = l; i <= r; ++i)
	{
		int j = X[i];
		m = max(m,dane[j].R) + dane[j].P;
		c = max(m+dane[j].Q,c);
	}
	return c;
}

// Dla Carliera: suma r/p
int CCCP(const vector<Element>& dane, const vector<int>& X, int l, int r)
{
	int length = 0;
	for(int i = l; i <= r; ++i)
	{
		const Element& dowiazanie = dane[X[i]];
		length = max(length,dowiazanie.R) + dowiazanie.P;
	}
	return length;
}

// zwraca index w permutacji - przetestowane, dziala
int FindB(const vector<Element>& dane, const vector<int>& Cp, int cmax)
{
	int b = -1;
	for(int j = (int)Cp.size()-1; j >= 0; --j)
	{
		int tmp = CCCP(dane,Cp,0,j) + dane[Cp[j]].Q;
		if(cmax == tmp)
		{
			b = j;
			break;
		}
	}
	return b;
}

// zwraca index w permutacji
int FindA(const vector<Element>& dane, const vector<int>& X, int b)
{
	int length = 0;
	int marker = 0;
	for(int i = 0; i < b; ++i)
	{
		const Element& dowiazanie = dane[X[i]];
		if(length < dowiazanie.R) { marker = i; }
		length = max(length,dowiazanie.R) + dowiazanie.P;
	}
	return marker;
}

// zwraca index w permutacji
int FindC(const vector<Element>& dane, const vector<int>& X, int a, int b)
{
	int c = -1;
	for(int i = b; i >= a; --i)
	{
		if(dane[X[i]].Q < dane[X[b]].Q)	
		{
			c = i;
			break;
		}
	}
	return c;
}

// Wejscie - tablica R,P,Q,index
// logs, index - sluza wylacznie do debugowania
// Wartosc zwracana jest poprzez parametr UB
// Oparte o pseudokod Dominika Zelaznego: http://dominik.zelazny.staff.iiar.pwr.wroc.pl/materialy/Algorytm_Carlier.pdf
void Carlier(vector<Element> wejscie, ostream& logs, const int& index, Output& UB)
{	
	// Tymczasowe
	Output U;
	Output LB;
	
	// Schrage - na dobry poczatek
	U = Schrage::BezPrzerwan(wejscie);
	if(U.dlugosc < UB.dlugosc) 	UB = U;
	vector<int>& Cp = U.permutacja; // Dowiazanie, dla czytelnosci
	int cmax = C(wejscie,Cp);
	
	// Blok i zadanie referencyjne
	int b = FindB(wejscie,Cp,cmax);
	int a = FindA(wejscie,Cp,b);
	int c = FindC(wejscie,Cp,a,b);
	if(c==-1) { return; } // Wyjdz jesli brak zadania referencyjnego
	
	int r1 = 999999, q1 = 999999, p1 = 0;
	for(int i = c+1; i <= b; ++i)
	{
		if(r1 > wejscie[Cp[i]].R)
		{	r1 = wejscie[Cp[i]].R;	}
		if(q1 > wejscie[Cp[i]].Q)
		{	q1 = wejscie[Cp[i]].Q;	}
		p1 += wejscie[Cp[i]].P;
	}
	
	int zmagazynowane_r = wejscie[Cp[c]].R;
	wejscie[Cp[c]].R = max(wejscie[Cp[c]].R,r1+p1);
	LB = Schrage::Przerwania(wejscie);
	if(LB.dlugosc < UB.dlugosc)
	{
		Carlier(wejscie,logs,index,UB);
	}
	wejscie[Cp[c]].R = zmagazynowane_r;
	
	int zmagazynowane_q = wejscie[Cp[c]].Q;
	wejscie[Cp[c]].Q = max(wejscie[Cp[c]].Q,q1+p1);
	LB = Schrage::Przerwania(wejscie);
	if(LB.dlugosc < UB.dlugosc)
	{
		Carlier(wejscie,logs,index,UB);
	}
	wejscie[Cp[c]].Q = zmagazynowane_q;
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
			Output wyjscie;
			wyjscie.dlugosc = 999999;
			Carlier(wejscie, logs, index, wyjscie);
			return wyjscie;
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

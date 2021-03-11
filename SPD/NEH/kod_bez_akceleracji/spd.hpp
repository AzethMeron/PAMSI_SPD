#ifndef SPD_HPP
#define SPD_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include "tester.hpp"

using namespace std;

// DLA TESTERA:
// typ wejsciowy: vector<Zadanie<float>> 
// typ wyjsciowy: Uszeregowanie<float>
// float mozna zmienic na unsigned int, int, cokolwiek
// Przy wczytywaniu struktury Zadanie: wymaga się aby dodać "wirtualną" maszynę na początku, o ct i cr = 0.

/* ***************************************************************************** */

template<typename Typ>
struct Maszyna
{
	Typ ct; // czas trwania
	Typ cr; // czas rozpoczęcia? Nie wiem czy to potrzebne
	Maszyna() : ct(0), cr(0) {}
};

template<typename Typ>
struct Zadanie
{
	public:
		// Pola
		vector<Maszyna<Typ>> Maszyny; // Maszyny powinnismy zwiekszyc o 1. Tzn. numerujemy od 1, maszyna 0 jest fikcyjna i ma cr,ct = 0
		unsigned int index;
		// Generic
		inline Maszyna<Typ>  operator [] (const int& ind) const { return Maszyny[ind]; }
		inline Maszyna<Typ>& operator [] (const int& ind)       { return Maszyny[ind]; }
		inline unsigned int size(void) const { return Maszyny.size(); }
		inline void resize(const unsigned int& new_size) { Maszyny.resize(new_size); }
		// Metody własne
		inline Typ Waga(void) const 
		{
			Typ wynik = 0;
			for(unsigned int i = 0; i < size(); ++i)
			{
				wynik += Maszyny[i].ct;
			}
			return wynik;
		}
		Zadanie(const unsigned int& new_size, const unsigned int& ind) : Maszyny(new_size), index(ind)	{ }
};

template<typename Typ>
istream& operator >> (istream& wejscie, Zadanie<Typ>& zad)
{
	for(unsigned int i = 0; i < zad.size(); ++i)
	{
		wejscie >> zad[i].ct;
		zad[i].cr = 0;
	}
	return wejscie;
}

template<typename Typ>
ostream& operator << (ostream& wyjscie, const Zadanie<Typ>& zad)
{
	wyjscie << "Zadanie" << endl;
	for(unsigned int i = 0; i < zad.size(); ++i)
	{
		wyjscie << "Maszyna " << i << ' ' << zad[i].ct << ' ' << zad[i].cr << endl;
	}
	wyjscie << endl;
	return wyjscie;
}

/* ***************************************************************************** */

template<typename Typ>
class Uszeregowanie
{
	protected:
		vector<Zadanie<Typ>> zadania;
	public:
		// Generic
		inline unsigned int size(void) const { return zadania.size(); }
		const Zadanie<Typ>& operator [] (const unsigned int& ind) const { return zadania[ind]; }
		// Metody własne
		void Wprowadz_do_szeregu(const Zadanie<Typ>& zad) 
		{
			if(zadania.size() == 0) { zadania.push_back(zad); }
			else
			{
				Typ cmax = 9999999;
				Uszeregowanie& temp = *this;
				Uszeregowanie optymalne;
				for(unsigned int i = 0; i < zadania.size()+1; ++i)
				{
					if(i < zadania.size()) { temp.zadania.insert(temp.zadania.begin()+i, zad); }
					else { temp.zadania.push_back(zad); }
					auto iterator = temp.zadania.begin() + i;
					Typ temp_czas = temp.Cmax();
					if(cmax > temp_czas)
					{
						optymalne = temp;
						cmax = temp_czas;
					}
					temp.zadania.erase(iterator);
				}
				*this = optymalne;
			}
		}
		Typ Cmax(void)
		{
			Typ wynik = 0; 
			// i - numer zadania
			// j - maszyna
			
			// wyjatek: pierwsze zadanie
			for(unsigned int j = 1; j < zadania[0].size(); ++j)
			{
				if(zadania[0][j].cr != zadania[0][j-1].cr + zadania[0][j-1].ct)
					zadania[0][j].cr = zadania[0][j-1].cr + zadania[0][j-1].ct;
				Typ tmp1 = zadania[0][j].cr + zadania[0][j].ct;
				if(wynik != max(wynik,tmp1))
					wynik = max(wynik,tmp1);
			}
			
			// czesc glowna
			for (unsigned int i = 1; i < zadania.size(); ++i)
			{
				for(unsigned int j = 1; j < zadania[i].size(); ++j)
				{
					Typ tmp1 = zadania[i][j-1].cr + zadania[i][j-1].ct;
					Typ tmp2 = zadania[i-1][j].cr + zadania[i-1][j].ct;
					if(zadania[i][j].cr != max(tmp1,tmp2))
						zadania[i][j].cr = max(tmp1,tmp2);
					if(wynik != max(wynik,zadania[i][j].cr+zadania[i][j].ct))
						wynik = max(wynik,zadania[i][j].cr+zadania[i][j].ct);
				}
			}
			return wynik;
		}
};

template<typename Typ>
inline bool PorownajWagi(const Zadanie<Typ>& zad1, const Zadanie<Typ>& zad2)
{
	return zad1.Waga() > zad2.Waga();
}

template<typename Typ>
Uszeregowanie<Typ> Uszereguj(std::vector<Zadanie<Typ>> zadania)
{
	Uszeregowanie<Typ> wynik;
	stable_sort(zadania.begin(),zadania.end(),PorownajWagi<Typ>);
	for(unsigned int i = 0; i < zadania.size(); ++i)
	{
		wynik.Wprowadz_do_szeregu(zadania[i]);
	}
	return wynik;
}

template<typename Typ>
class SPDTester : public Tester <vector<Zadanie<Typ>>,Uszeregowanie<Typ>>
{
	protected:
		vector<Zadanie<Typ>> WczytajPojedynczeWejscie(std::istream& wejscie) override
		{ 
			int rozmiar = 0; int maszyny = 0;
			wejscie >> rozmiar >> maszyny; maszyny++;
			vector<Zadanie<Typ>> wynik;
			for(int i = 0; i < rozmiar; ++i)
			{
				Zadanie<Typ> tmp(maszyny,i);
				tmp[0].cr = 0; tmp[0].ct = 0;
				for(int j = 1; j < maszyny; ++j)
				{
					wejscie >> tmp[j].ct;
				}
				wynik.push_back(tmp);
			}
			return wynik;			
		}
		Uszeregowanie<Typ> Algorytm(const vector<Zadanie<Typ>>& wejscie,std::ostream& logs,const int& index) override
		{
			return Uszereguj(wejscie);
		}
		void WyswietlWynik(std::ostream& wyjscie,Uszeregowanie<Typ>& wynik,const int& index,const double& ms) override
		{
			wyjscie << "Ukonczono przetwarzanie zestawu: " << index << std::endl;
			wyjscie << "Czas pracy: " << ms << " [ms]" << std::endl;
			wyjscie << "Wynik: " << wynik.Cmax() <<std::endl;
			wyjscie << "Uszeregowanie: ";
			for(unsigned int i = 0; i < wynik.size(); ++i)
			{
				wyjscie << wynik[i].index+1 << ' ';
			}
			wyjscie << std::endl;
		}
	public:
		SPDTester(std::istream& we, std::ostream& wy, std::ostream& lo) : Tester<vector<Zadanie<Typ>>,Uszeregowanie<Typ>>(we, wy, lo) {}
};

#endif

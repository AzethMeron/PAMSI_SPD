#ifndef SPD_HPP
#define SPD_HPP

#include <vector>
#include <algorithm>

class SPDTester : public Tester <std::vector<int>,std::vector<int>>
{
	protected:
		std::vector<int> WczytajPojedynczeWejscie(std::istream& wejscie) override
		{
			int liczba;
			wejscie >> liczba;
			std::vector<int> wynik(liczba);
			for(int i = 0; i < liczba; i++)
			{
				wejscie >> wynik[i];
			}
			return wynik;
		}
		std::vector<int> Algorytm(std::vector<int>& data, std::ostream& logs, const int& index) override
		{
			std::vector<int> wynik = data;
			std::stable_sort(wynik.begin(),wynik.end());
			logs << "Zestaw " << index << std::endl;
			return wynik;
		}
		void WyswietlWynik(std::ostream& wyjscie,const std::vector<int>& data,const int& index,const double& czas) override
		{
			wyjscie << "Ukonczono sortowanie zestawu: " << index << std::endl;
			wyjscie << "Czas sortowania: " << czas << " [ms]" << std::endl;
			for(unsigned int i = 0; i < data.size(); i++)
			{
				wyjscie << data[i] << ' ';
			}
			wyjscie << std::endl;
		}
	public:
		SPDTester(std::istream& we, std::ostream& wy, std::ostream& lo) : Tester(we, wy, lo) {}
};

#endif

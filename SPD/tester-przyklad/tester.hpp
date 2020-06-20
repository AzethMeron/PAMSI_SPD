#ifndef TESTER_HPP
#define TESTER_HPP

#include <iostream>
#include <list>
#include <string>
#include <chrono>

#define TEMPLATE_ARGS_LONG typename TypWejsciowy,typename TypWyjsciowy
#define TEMPLATE_ARGS TypWejsciowy,TypWyjsciowy

/* ******************************************************************************************************** */

/* Wykorzystane konstruktory/operatory, należy je przeciążyć:
 * 
 * 		TypWejsciowy() - chyba
 * 		TypWejsciowy(const TypWejsciowy&)
 *		TypWejsciowy(const TypWejsciowy&&)
 * 
 * 		TypWyjsciowy() - chyba
 * 		TypWyjsciowy(const TypWyjsciowy&)
 * 		TypWyjsciowy(const TypWyjsciowy&&)
 */
 
 
 
 /* Ogólna zasada działania
  * Należy utworzyć klasę dziedziczącą po szablonie Tester<>. Najlepszy jest szablon dziedziczący po szablonie, ale mniejsza
  * 	class Klasa : public Tester<A,B>
  * Następnie należy przeciążyć kilka metod: WczytajPojedynczeWejscie, WczytajPojedynczeWejscie, WyswietlWynik
  * Oraz napisać kontruktor trójargumentowy: Klasa(std::istream& we, std::ostream& wy, std::ostream& lo) : Tester(we, wy, lo) {}
  * Ostatecznie trzeba utworzyć obiekt tej klasy i wywołać metode Start podając argument true/false 
  * 	Klasa obiekt;
  * 	obiekt.Start(false);
  * Gotowe
  */
  
  
 
/* Klasa jest abstrakcyjna, nie można stworzyć jej obiektu. Można natomiast po niej dziedziczyć:
 * 
 * class Klasa : public Tester<TypWejsciowy,TypWyjsciowy>
 *	 	A - klasa określająca typ wejściowy
 *	 	B - klasa określająca typ wyjściowy
 * 
 * Klasa ma kilka abstrakcyjnych metod. Należy je przeciążyć, używając słowa kluczowego override.
 * Pamiętajcie przy tym o zachowaniu tego samego poziomu ochrony: protected!
 * 	protected:
 *  	TypWyjsciowy Algorytm(TypWejsciowy&,ostream&,const int&) override 
 * 		{}
 * Oprócz tego należy napisać konstruktor trójargumentowy:
 * 	public: Klasa(std::istream& we, std::ostream& wy, std::ostream& lo) : Tester(we, wy, lo) {}
 *	 	we - std::istream&, strumień z którego wczytywane będą dane. Można tu wpisać obiekt ifstream&
 *	 	wy - std::ostream&, strumień na którym wypisywane są normalne komunikaty. Typowo: std::cout
 * 		lo - std::ostream&, strumień na który wypisywane są komunikaty z Algorytmu. Pozwala to śledzić prace Algorytmu.
 */
 
 
 
/* Wyjaśnienie argumentów funkcji:
 * 	Algorytm:
 * 		TypWejsciowy& - pojedyńcze wczytane wejście
 * 		std::ostream& LoG - strumień prowadzący na logi
 * 		const int& - liczba porządkowa, numerowana od 1, na liście wszystkich wczytanych elementów
 * 
 * 	WyswietlWynik:
 * 		std::ostream& - strumień wyściowy
 * 		const TypWyjsciowy& - wynik pracy Algorytmu
 * 		const int& - liczba porządkowa, numerowana od 1, na liście wszystkich wczytanych elementów
 * 		const double& - czas wykonywania algorytmu (w milisekundach)
 * 
 * 	WczytajPojedynczeWejscie
 * 		std::istream& - strumień z którego wczytujemy dane. Początek strumienia znajduje się zaraz po ciągu "data.XXX"
 * 
 * 	Start
 * 		bool pauza = true - program jest pauzowany w pewnych momentach i wymaga wpisania czegokolwiek w terminalu, by kontynuować prace
 * 		bool pauza = false - program nie jest pauzowany
 */

template<TEMPLATE_ARGS_LONG>
class Tester
{
	private:
		std::list<TypWejsciowy> Wczytaj();
		std::istream& wejscie;
		std::ostream& wyjscie;
		std::ostream& logs;
	protected:
		virtual TypWejsciowy WczytajPojedynczeWejscie(std::istream&) = 0;
		virtual TypWyjsciowy Algorytm(TypWejsciowy&,std::ostream&,const int&) = 0;
		virtual void WyswietlWynik(std::ostream&,const TypWyjsciowy&,const int&,const double&) = 0;
	public:
		void Start(bool pauza);
		Tester(std::istream& we, std::ostream& wy, std::ostream& lo) : wejscie(we), wyjscie(wy), logs(lo) {}
};

/* ******************************************************************************************************** */

class Timer 
{
	protected:
		std::chrono::high_resolution_clock::time_point start;
		std::chrono::high_resolution_clock::time_point stop;
	public:
		void Start(void) { start = std::chrono::high_resolution_clock::now(); }
		void Stop(void) { stop = std::chrono::high_resolution_clock::now(); }
		double ns(void) const { return std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count(); }
		double ms(void) const { const double constant = 1e-6; return ns() * constant; }
};

/* ******************************************************************************************************** */

template<TEMPLATE_ARGS_LONG>
std::list<TypWejsciowy> Tester<TEMPLATE_ARGS>::Wczytaj()
{
	std::list<TypWejsciowy> ListaZestawow;
	for(unsigned int index = 0; true; index++)
	{
		// Tworzenie nagłówka do znalezienia
		char tmp_wyraz_magiczny[17];
		sprintf(tmp_wyraz_magiczny,"data.%03u", index);
		const std::string Naglowek = tmp_wyraz_magiczny;
		
		// Szukanie nagłówka
		std::string tmp_szukacz = "";
		while(tmp_szukacz != Naglowek)
		{
			wejscie >> tmp_szukacz;
			if(wejscie.eof()) break;
		}
		if(wejscie.eof()) break;
			
		// Wczytywanie danych
		TypWejsciowy tmp_obiekt = WczytajPojedynczeWejscie(wejscie);
		ListaZestawow.push_back(tmp_obiekt);
	}
	return ListaZestawow;
}

template<TEMPLATE_ARGS_LONG>
void Tester<TEMPLATE_ARGS>::Start(bool pauza)
{
	// Wczytywanie
	wyjscie << "Wczytywanie..." <<std::endl;
	std::list<TypWejsciowy> Lista = Wczytaj();
	wyjscie << "Zakończono wczytywanie" << std::endl;
	wyjscie << "Wczytano zestawow: " << Lista.size() <<std::endl;
	wyjscie << std::endl;
	if(pauza) { std::string tmp_pauza; std::cin >> tmp_pauza; }
	
	// Przetwarzanie
	int index = 1;
	for(TypWejsciowy& Wsk : Lista)
	{
		Timer zegarek;
		zegarek.Start();
		TypWyjsciowy tmp_Wyjscie = Algorytm(Wsk,logs,index);
		zegarek.Stop();
		
		WyswietlWynik(wyjscie,tmp_Wyjscie,index,zegarek.ms());
		wyjscie << std::endl << std::endl;
		++index;
	}
	
	if(pauza) { std::string tmp_pauza; std::cin >> tmp_pauza; }
}

#endif

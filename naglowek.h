#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <windows.h>

// ZMIENNE GLOBALNE
int etap = 1;
bool fiftyFiftyB = true;
bool zmianaPytaniaB = true;
bool przyjacielB = true;

using namespace std;

class Pytanie {
public:
	int poprawna;
	string tresc, odpA, odpB, odpC, odpD;

	Pytanie() {
		tresc = "default";
		odpA = "default";
		odpB = "default";
		odpC = "default";
		odpD = "default";
		poprawna = 0;
	}

	Pytanie(string tr, string oA, string oB, string oC, string oD, int po) {
		tresc = tr;
		odpA = oA;
		odpB = oB;
		odpC = oC;
		odpD = oD;
		poprawna = po;
	}

	~Pytanie() {}

	void mieszajOdpowiedzi() {
		// Zapamietujemy poprawna odpowiedz
		string temp;
		if (char(poprawna) == 'A') temp = odpA;
		else if (char(poprawna) == 'B') temp = odpB;
		else if (char(poprawna) == 'C') temp = odpC;
		else temp = odpD;
		// Mieszamy odpowiedzi
		string temp2;
		srand(time(0));
		int losowanie = rand();
		if (losowanie % 3 == 0) {
			temp2 = odpA;
			odpA = odpC;
			odpC = temp2;
		}
		else if (losowanie % 3 == 1) {
			temp2 = odpB;
			odpB = odpD;
			odpD = temp2;
		}
		// Odnajdujemy poprawna odpowiedz i zapisujemy z powrotem do wlasciwej zmiennej
		if (temp == odpA) poprawna = 65;
		else if (temp == odpB) poprawna = 66;
		else if (temp == odpC) poprawna = 67;
		else poprawna = 68;
	}

	void wyswietlPytanie() {
		cout << "\n" << tresc << endl;
		cout << "A) " << odpA.erase(0, 1) << endl;
		cout << "B) " << odpB.erase(0, 1) << endl;
		cout << "C) " << odpC.erase(0, 1) << endl;
		cout << "D) " << odpD.erase(0, 1) << endl;
	}

	bool sprawdzenie(char odpowiedz) {
		if (odpowiedz == char(poprawna)) return true;
		return false;
	}

	void fiftyFifty() {
		// Zapamietujemy poprawna odpowiedz
		string temp;
		if (char(poprawna) == 'A') temp = odpA;
		else if (char(poprawna) == 'B') temp = odpB;
		else if (char(poprawna) == 'C') temp = odpC;
		else temp = odpD;
		// Losujemy dwie bledne odpowiedzi
		string wylosowana1, wylosowana2;
		int wylosowanych = 0, losowanie;
		srand(time(0));
		// Losowanie pierwszej
		while (wylosowanych < 1) {
			losowanie = rand();
			// Dla kazdej odpowiedzi sprawdzamy czy nie jest to odpowiedz prawidlowa
			if (losowanie % 4 == 0) {
				if (odpA != temp) {
					wylosowana1 = "A";
					wylosowanych++;
				}
			}
			else if (losowanie % 4 == 1) {
				if (odpB != temp) {
					wylosowana1 = "B";
					wylosowanych++;
				}
			}
			else if (losowanie % 4 == 2) {
				if (odpC != temp) {
					wylosowana1 = "C";
					wylosowanych++;
				}
			}
			else {
				if (odpD != temp) {
					wylosowana1 = "D";
					wylosowanych++;
				}
			}
		}
		// W drugim losowaniu upewniamy sie ze nie wylosujemy dwa razy tej samej odpowiedzi
		while (wylosowanych < 2) {
			losowanie = rand();
			if (losowanie % 4 == 0) {
				if (odpA != temp && wylosowana1 != "A") {
					wylosowana2 = "A";
					wylosowanych++;
				}
			}
			else if (losowanie % 4 == 1) {
				if (odpB != temp && wylosowana1 != "B") {
					wylosowana2 = "B";
					wylosowanych++;
				}
			}
			else if (losowanie % 4 == 2) {
				if (odpC != temp && wylosowana1 != "C") {
					wylosowana2 = "C";
					wylosowanych++;
				}
			}
			else {
				if (odpD != temp && wylosowana1 != "D") {
					wylosowana2 = "D";
					wylosowanych++;
				}
			}
		}
		cout << "2 bledne odpowiedzi to: " << wylosowana1 << " oraz " << wylosowana2 << endl;
		// Wylaczamy kolo ratunkowe
		fiftyFiftyB = false;
	}

	void nadpisz(string tr, string oA, string oB, string oC, string oD, int po) {
		// Nadpisanie danych
		tresc = tr;
		odpA = oA;
		odpB = oB;
		odpC = oC;
		odpD = oD;
		poprawna = po;
		// Wyswietlenie nowego pytania
		cout << "\nNowe pytanie:";
		wyswietlPytanie();
		// Wylaczamy kolo ratunkowe
		zmianaPytaniaB = false;
	}

	void przyjaciel() {
		// Zapamietujemy poprawna odpowiedz
		string temp, wylosowana;
		if (char(poprawna) == 'A') temp = odpA;
		else if (char(poprawna) == 'B') temp = odpB;
		else if (char(poprawna) == 'C') temp = odpC;
		else temp = odpD;
		// Losowo wybieramy jedna bledna odpowiedz miedzy ktora przyjaciel bedzie sie wachal
		bool znaleziono = false;
		int losowanie;
		srand(time(0));
		while (!znaleziono) {
			losowanie = rand();
			if (losowanie % 4 == 0) {
				if (odpA != temp) {
					wylosowana = "A";
					znaleziono = true;
				}
			}
			else if (losowanie % 4 == 1) {
				if (odpB != temp) {
					wylosowana = "B";
					znaleziono = true;
				}
			}
			else if (losowanie % 4 == 2) {
				if (odpC != temp) {
					wylosowana = "C";
					znaleziono = true;
				}
			}
			else {
				if (odpD != temp) {
					wylosowana = "D";
					znaleziono = true;
				}
			}
		}
		cout << "Przyjaciel mowi ze poprawna jest odpowiedz " << char(poprawna) << " lub " << wylosowana << endl;
		// Wylaczamy kolo ratunkowe
		przyjacielB = false;
	}

};

class Portfel {
public:
	int stan, nastepnaSuma, bezpiecznaSuma;

	Portfel() {
		stan = 0;
		nastepnaSuma = 0;
		bezpiecznaSuma = 0;
	}

	Portfel(int su, int nS, int bS) {
		stan = su;
		nastepnaSuma = nS;
		bezpiecznaSuma = bS;
	}

	~Portfel() {}

	void wyswietlStan() {
		// Chcemy wyswietlic wszystko w jednym wierszu z odstepami
		cout << "Stan konta: " << stan << " zl";
		cout << setw(23) << "Grasz o " << nastepnaSuma << " zl";
		cout << setw(33) << "Gwarantowana suma: " << bezpiecznaSuma << " zl" << endl;
	}

	void zmienStan(int aktualnyEtap) {
		// Dla kazdego etapu wszystkie wartosciw portfelu sa inne
		switch (aktualnyEtap) {
		case 1:
			stan = 0;
			nastepnaSuma = 1000;
			bezpiecznaSuma = 0;
			break;
		case 2:
			stan = 1000;
			nastepnaSuma = 5000;
			bezpiecznaSuma = 0;
			break;
		case 3:
			stan = 5000;
			nastepnaSuma = 15000;
			bezpiecznaSuma = 5000;
			break;
		case 4:
			stan = 15000;
			nastepnaSuma = 40000;
			bezpiecznaSuma = 5000;
			break;
		case 5:
			stan = 40000;
			nastepnaSuma = 70000;
			bezpiecznaSuma = 5000;
			break;
		case 6:
			stan = 70000;
			nastepnaSuma = 125000;
			bezpiecznaSuma = 70000;
			break;
		case 7:
			stan = 125000;
			nastepnaSuma = 250000;
			bezpiecznaSuma = 70000;
			break;
		case 8:
			stan = 250000;
			nastepnaSuma = 500000;
			bezpiecznaSuma = 70000;
			break;
		case 9:
			stan = 500000;
			nastepnaSuma = 1000000;
			bezpiecznaSuma = 70000;
			break;
		default:
			stan = 0;
			nastepnaSuma = 0;
			bezpiecznaSuma = 0;
			break;
		}
	}
};
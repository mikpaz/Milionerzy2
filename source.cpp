#include "naglowek.h"

void odczytPliku(string&, string&, string&, string&, string&, int&, int&);
char pobierzZnak();
void koniecGry(Portfel, bool);
bool wczytajOdpowiedz(Pytanie, Portfel, int&, int);
void zmianaPytania(Pytanie&, int);
void pokazKolaRatunkowe();


int main()
{
	// Tworzymy portfel, jego stan w tym momencie jest nieistotny, poniewaz przed rozegraniem etapy bedzie on aktualizowany
	Portfel portfel1(0, 0, 0);
	// Kazdy etap to jedno wykonanie petli
	for (int i = 0; i < 9; i++) {
		// Imersja
		if (etap > 1) Sleep(1500);
		system("CLS");
		// Na poczatku aktualizujemy stan portfela do etapu na kotrym jest gracz i wyswietlamy portfel
		portfel1.zmienStan(etap);
		portfel1.wyswietlStan();
		// Pozioma linia
		for (int k = 0; k < 100; k++) cout << "=";
		// Pokazujemy dostepne kola ratunkwoe lub ich brak
		if (fiftyFiftyB == false && zmianaPytaniaB == false && przyjacielB == false) cout << "\nBrak dostepnych kol ratunkowych\n";
		else {
			cout << "\nDostepne kola ratunkowe:\n";
			pokazKolaRatunkowe();
		}
		// Pozioma linia
		for (int k = 0; k < 100; k++) cout << "=";
		// Zmienne potrzebne do odczytania danych z pliku
		string pytanie, odpA, odpB, odpC, odpD;
		int poprawna, nrPytania;
		// Odczyt losowego pytania z pliku aktualnego etapu
		odczytPliku(pytanie, odpA, odpB, odpC, odpD, poprawna, nrPytania);
		// Utworzenie obiektu, wymieszanie odpowiedzi i wyswietlenie pytania
		Pytanie pytanie1(pytanie, odpA, odpB, odpC, odpD, poprawna);
		pytanie1.mieszajOdpowiedzi();
		pytanie1.wyswietlPytanie();
		// Pozioma linia
		for (int k = 0; k < 100; k++) cout << "=";
		// Pobranie odpowiedzi od gracza
		cout << "\nWpisz poprawna odpowiedz, numer kola ratunkowego lub R aby zrezygnowac: ";
		if (!wczytajOdpowiedz(pytanie1, portfel1, etap, nrPytania)) return 0;
	}

	return 0;
}

void odczytPliku(string& pytanie, string& odpA, string& odpB, string& odpC, string& odpD, int& poprawna, int& nrPytania) {
	// Nazwa otwieranego pliku to numer etapu wiec tworzymy zmienna 'nazwa'
	string nazwa = "pytania/etap" + to_string(etap) + ".txt";
	// Otwieramy plik
	ifstream plik(nazwa);
	// Losujemy pytanie z przedzialu 0 - 6 (7 pytan do wyboru)
	srand(time(0));
	nrPytania = (rand() % 6);
	// Zmienne potrzebne do odczytu wierszy w pliku
	string wiersz;
	// Otwieramy plik
	if (plik.is_open()) {
		int licznikWierszy = 0;
		while (getline(plik, wiersz)) {
			// Liczymy wiersze 
			licznikWierszy++;
			// W momencie napotkania wylosowanego pytania zapisujemy je
			if (licznikWierszy == 1 + (5 * nrPytania)) {
				pytanie = wiersz;
			}
			// A nastepnie zapisujemy odpowiedzi jednoczesnie ustalajac ktora jest prawidlowa
			else if (licznikWierszy == 2 + (5 * nrPytania)) {
				odpA = wiersz;
				if (odpA[0] == '*') poprawna = 65;
			}
			else if (licznikWierszy == 3 + (5 * nrPytania)) {
				odpB = wiersz;
				if (odpB[0] == '*') poprawna = 66;
			}
			else if (licznikWierszy == 4 + (5 * nrPytania)) {
				odpC = wiersz;
				if (odpC[0] == '*') poprawna = 67;
			}
			else if (licznikWierszy == 5 + (5 * nrPytania)) {
				odpD = wiersz;
				if (odpD[0] == '*') poprawna = 68;
			}
		}
	}
	plik.close();
	return;
}

char pobierzZnak() {
	// Wczytujemy znak i zamieniamy na wielka litere dla ulatwienia walidacji
	char znak;
	cin >> znak;
	znak = toupper(znak);
	// Dopuszczamy tylko wybrane znaki (odpowiedz, kolo ratunkowe, rezygnacja)
	while (znak != 'A' && znak != 'B' && znak != 'C' && znak != 'D' && znak != 'R' && znak != '1' && znak != '2' && znak != '3') {
		cout << "Wpisz poprawnie: ";
		cin >> znak; 
		znak = toupper(znak);
	}
	// Funkcja zwraca poprawny znak
	return znak;
}

void koniecGry(Portfel portfel1, bool rezygnacja) {
	cout << "Koniec gry!\n";
	// Jesli gracz rezygnuje dobrowolnie to wygrywa cala wygrana kwote
	if (rezygnacja) cout << "Wygrales: " << portfel1.stan << " zl.";
	// Jesli przegrywa poprzez podanie zlej odpowiedzi to wygrywa ostatnia sume gwarantowana
	else cout << "Wygrales: " << portfel1.bezpiecznaSuma << " zl.";
}

bool wczytajOdpowiedz(Pytanie pytanie1, Portfel portfel1, int& etap, int aktualnePytanie) {
	// Wczytanie odpowiedzi gracza
	char odpowiedz = pobierzZnak();
	// Sprawdzenie odpowiedzi
	if (odpowiedz == 'A' || odpowiedz == 'B' || odpowiedz == 'C' || odpowiedz == 'D') {
		// Jesli odpowiedz jest poprawna
		if (pytanie1.sprawdzenie(odpowiedz)) {
			// Sprawdzamy czy gracz nie zostal Milionerem
			if (etap == 9) {
				cout << "Gratulacje! Zostales Milionerem!";
				return true;
			}
			// Jesli nie, to informujemy o odpowiedzi i przechodzimy do nastepnego etapu
			else {
				cout << "Dobrze, nastepny etap\n";
				etap++;
				return true;
			}
		}
		// Jesli jest bledna to konczymy gre
		else {
			cout << "Bledna odpowiedz! ";
			koniecGry(portfel1, false);
			return false;
		}
	}
	// Uzycie kola ratunkowego
	else if (odpowiedz == '1') {
		// Kolo moze zostac uzyte tylko raz
		if (!fiftyFiftyB) {
			cout << "Juz uzyles to kolo ratunkowe\n";
			if (!wczytajOdpowiedz(pytanie1, portfel1, etap, aktualnePytanie)) return false;
			return true;
		}
		else {
			pytanie1.fiftyFifty();
			cout << "Podaj odpowiedz: ";
			if (!wczytajOdpowiedz(pytanie1, portfel1, etap, aktualnePytanie)) return false;
			return true;
		}
	}
	else if (odpowiedz == '2') {
		// Kolo moze zostac uzyte tylko raz
		if (!przyjacielB) {
			cout << "Juz uzyles to kolo ratunkowe\n";
			if (!wczytajOdpowiedz(pytanie1, portfel1, etap, aktualnePytanie)) return false;
			return true;
		}
		else {
			pytanie1.przyjaciel();
			cout << "Podaj odpowiedz: ";
			if (!wczytajOdpowiedz(pytanie1, portfel1, etap, aktualnePytanie)) return false;
			return true;
		}
	}
	else if (odpowiedz == '3') {
		// Kolo moze zostac uzyte tylko raz
		if (!zmianaPytaniaB) {
			cout << "Juz uzyles to kolo ratunkowe\n";
			if (!wczytajOdpowiedz(pytanie1, portfel1, etap, aktualnePytanie)) return false;
			return true;
		}
		else {
			zmianaPytania(pytanie1, aktualnePytanie);
			cout << "Podaj odpowiedz: ";
			if (!wczytajOdpowiedz(pytanie1, portfel1, etap, aktualnePytanie)) return false;
			return true;
		}
	}
	// Zakonczenie gry - rezygnacja
	else {
		cout << "Rezygnujesz. ";
		koniecGry(portfel1, true);
		return false;
	}
}

void zmianaPytania(Pytanie& pytanie1, int aktualnePytanie) {
	// Zmienne do ktorych zapisujemy nowo wylosowane pytanie z pliku
	string nowePytanie, NodpA, NodpB, NodpD, NodpC;
	int nPoprawna;
	// Nazwa otwieranego pliku to numer etapu wiec tworzymy zmienna 'nazwa'
	string nazwa = "pytania/etap" + to_string(etap) + ".txt";
	// Otwieramy plik
	ifstream plik(nazwa);
	// Losujemy pytanie z przedzialu 0 - 6 (7 pytan do wyboru)
	srand(time(0));
	int nrPytania = (rand() % 6);
	// I upewniamy sie ze nie jest to pytanie takie samo jak aktualnie wyswietlane
	while (nrPytania == aktualnePytanie) {
		nrPytania = (rand() % 6);
	}
	// Zmienne potrzebne do odczytu wierszy w pliku
	string wiersz;
	// Otwieramy plik
	if (plik.is_open()) {
		int licznikWierszy = 0;
		while (getline(plik, wiersz)) {
			// Liczymy wiersze 
			licznikWierszy++;
			// W momencie napotkania wylosowanego pytania sczytujemy wszystkie potrzebne wiersze
			if (licznikWierszy == 1 + (5 * nrPytania)) {
				nowePytanie = wiersz;
			}
			else if (licznikWierszy == 2 + (5 * nrPytania)) {
				NodpA = wiersz;
				if (NodpA[0] == '*') nPoprawna = 65;
			}
			else if (licznikWierszy == 3 + (5 * nrPytania)) {
				NodpB = wiersz;
				if (NodpB[0] == '*') nPoprawna = 66;
			}
			else if (licznikWierszy == 4 + (5 * nrPytania)) {
				NodpC = wiersz;
				if (NodpC[0] == '*') nPoprawna = 67;
			}
			else if (licznikWierszy == 5 + (5 * nrPytania)) {
				NodpD = wiersz;
				if (NodpD[0] == '*') nPoprawna = 68;
			}
		}
	}
	plik.close();
	// Nadpisujemy dane w obiekcie
	pytanie1.nadpisz(nowePytanie, NodpA, NodpB, NodpC, NodpD, nPoprawna);
}

void pokazKolaRatunkowe() {
	// Sprawdzamy czy kolo zostalo nie zostalo wykorzystane
	if (fiftyFiftyB) cout << "[1] 50:50\n";
	if (przyjacielB) cout << "[2] Telefon do przyjaciela\n";
	if (zmianaPytaniaB) cout << "[3] Zamiana pytania\n";
	
}
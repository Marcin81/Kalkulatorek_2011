/***************************************************************************
 *            Kalkulator9.cc
 *
 *  Sat May 21 12:41:02 2005
 *  Copyright  2005  Marcin Brysz
 *  bryszmarcin@o2.pl
 ****************************************************************************/
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Repeat_Button.H>
#include <FL/Fl_Tooltip.H>
#include <FL/Enumerations.H>
#include <FL/fl_ask.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_File_Icon.H> // dodaj
#include <sstream>
#include <cmath>
using namespace std;
// bez hex ,dec, bin, modulo bo dziala tylko dla liczb calkowitych!
double poprzedni = 0.00;
Fl_Output *okno = 0;
void (*Operator)( double ); // Wskaźnik do funkcji void nazwa(double);
void Plus( double );
void Minus( double );
void Dziel( double );
void Mnoz( double );
void Pierwiastek( double);
void Procent( double );
inline void Wynik( double ) {}; // "Virtualna", Funkcja uzywana tylko do wskaźnika do niej
	// Nigdy nie zostaje wywołana, służy jako sygnalizacja
void callback_Obsluga(Fl_Widget *w, void *data);
void callback_Liczba(Fl_Widget *w, void *data);
void callback_Rownosc(Fl_Widget *w, void *data);
void callback_Kasuj(Fl_Widget *w, void *data);

void callback_ObslugaMinus(Fl_Widget *w, void *data);
void callback_ObslugaDziel(Fl_Widget *w, void *data);
void callback_ObslugaPlus(Fl_Widget *w, void *data);
void callback_ObslugaMnoz(Fl_Widget *w, void *data);
void callback_Kropka(Fl_Widget *w, void *data);
void callback_ObslugaZnak(Fl_Widget *w, void *data);
void callback_1LiczbaZero(Fl_Widget *w, void *data);

void callback_Sin(Fl_Widget *w, void *data);
void callback_Sinh(Fl_Widget *w, void *data);
void callback_Cos(Fl_Widget *w, void *data);
void callback_Cosh(Fl_Widget *w, void *data);
void callback_Tan(Fl_Widget *w, void *data);
void callback_CTan(Fl_Widget *w, void *data);
void callback_Tanh(Fl_Widget *w, void *data);
void callback_Bezwzgledna(Fl_Widget *w, void *data);
void callback_Pot2(Fl_Widget *w, void *data);
void callback_pot3(Fl_Widget *w, void *data);
void callback_Sin(Fl_Widget *w, void *data);
void callback_Sinh(Fl_Widget *w, void *data);
void callback_Cos(Fl_Widget *w, void *data);
void callback_Cosh(Fl_Widget *w, void *data);
void callback_Tan(Fl_Widget *w, void *data);
void callback_CTan(Fl_Widget *w, void *data);
void callback_Tanh(Fl_Widget *w, void *data);
void callback_Bezwzgledna(Fl_Widget *w, void *data);
void callback_Pot2(Fl_Widget *w, void *data);
void callback_pot3(Fl_Widget *w, void *data);
void callback_Pierwiastek(Fl_Widget *w, void *data);
void callback_Procent(Fl_Widget *w, void *data);

void Sinus( double );
void Cosinus( double );
void Sinush( double );
void Cosinush( double );
void Tangens( double );
void Tangensh( double );
void Cotangens( double );
void Bezwzgledna( double );
void Potega2( double );
void Potega3( double );

inline void wspolne();
inline void wyswietl();

bool klej = false;
bool stop = false;
bool kropka = false;
// Na strzalkach mogę sie przesunąć z Fl_Ouput na inne przyciski
int main() {
	Operator = Plus;
	Fl::scheme("plastic"); // Pobiera shchemat z gnomelub kde,
	//i ustawia elementy windget na styl plastic
	//! Fl_File_Icon::load_system_icons(); // Błąd linkera, nei moze znależć definicji
	Fl_Window *window = new Fl_Window(370,240, "Kalkulator");
	// Pierwszy stworzone w oknie okno lub cokolwiek innego jest domyslnie zaznaczone
	Fl_Repeat_Button *wynik = new Fl_Repeat_Button(180, 200, 30, 30, "=");
	okno = new Fl_Output(10, 10, 200, 30);
	okno->value("");
	// Jeszcze dodaj ikone
	//window->color(fl_rgb_color(0,200,255));

	Fl_Repeat_Button *siedem = new Fl_Repeat_Button(10, 80, 30, 30, "7");
	Fl_Repeat_Button *osiem = new Fl_Repeat_Button(50, 80, 30, 30, "8");
	Fl_Repeat_Button *dziewiec = new Fl_Repeat_Button(90, 80, 30, 30, "9");
	
	Fl_Repeat_Button *cztery = new Fl_Repeat_Button(10, 120, 30, 30, "4");
	Fl_Repeat_Button *piec = new Fl_Repeat_Button(50, 120, 30, 30, "5");
	Fl_Repeat_Button *szesc = new Fl_Repeat_Button(90, 120, 30, 30, "6");
	
	Fl_Repeat_Button *jeden = new Fl_Repeat_Button(10, 160, 30, 30, "1");
	Fl_Repeat_Button *dwa = new Fl_Repeat_Button(50, 160, 30, 30, "2");
	Fl_Repeat_Button *trzy = new Fl_Repeat_Button(90, 160, 30, 30, "3");
	
	Fl_Repeat_Button *zero = new Fl_Repeat_Button(10, 200, 70, 30, "0");
	zero->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
	Fl_Repeat_Button *kropka = new Fl_Repeat_Button(90, 200, 30, 30, ".");
	Fl_Repeat_Button *kasuj = new Fl_Repeat_Button(140, 80, 30, 30, "C");
	Fl_Repeat_Button *procent = new Fl_Repeat_Button(140, 200, 30, 30, "%");

	Fl_Repeat_Button *plus = new Fl_Repeat_Button(140, 120, 30, 30, "+");
	Fl_Repeat_Button *minus = new Fl_Repeat_Button(180, 120, 30, 30, "-");
	Fl_Repeat_Button *mnozenie = new Fl_Repeat_Button(140, 160, 30, 30, "*");
	Fl_Repeat_Button *dzielenie = new Fl_Repeat_Button(180, 160, 30, 30, "/");
	Fl_Repeat_Button *znak = new Fl_Repeat_Button(180, 80, 30, 30, "+/-");

	znak->callback(callback_ObslugaZnak, okno);
	plus->callback(callback_ObslugaPlus, okno); // Potrzebny wskaxnik do Fl_Float_Input
	minus->callback(callback_ObslugaMinus, okno);
	mnozenie->callback(callback_ObslugaMnoz, okno);
	dzielenie->callback(callback_ObslugaDziel, okno);

	// Wypukłe palstikowe klawisze (są w deche)
	// Funkcje zwrotne:
	// Na początku moze być 0.
	zero->callback(callback_1LiczbaZero);
	
	jeden->callback(callback_Liczba);
	dwa->callback(callback_Liczba);
	trzy->callback(callback_Liczba);
	cztery->callback(callback_Liczba);
	piec->callback(callback_Liczba);
	szesc->callback(callback_Liczba);
	siedem->callback(callback_Liczba);
	osiem->callback(callback_Liczba);
	dziewiec->callback(callback_Liczba);
	kropka->callback(callback_Kropka);

	kasuj->callback(callback_Kasuj);
	wynik->callback(callback_Rownosc);
	kasuj->shortcut(FL_Delete);
	// Skróty kalwiszowe:
	zero->shortcut('0');
	jeden->shortcut('1');
	dwa->shortcut('2');
	trzy->shortcut('3');
	cztery->shortcut('4');
	piec->shortcut('5');
	szesc->shortcut('6');
	siedem->shortcut('7');
	osiem->shortcut('8');
	dziewiec->shortcut('9');

	plus->shortcut('+');
	minus->shortcut('-');
	dzielenie->shortcut('/');
	mnozenie->shortcut('*');
	wynik->shortcut(FL_Enter | FL_KP_Enter);
	znak->shortcut(FL_Insert); // zmiana + -
	kropka->shortcut('.');

	kasuj->tooltip("Klawisz\ndelete");
	znak->tooltip("Klawisz\ninsert");
	wynik->tooltip("Klawisz\nenter");
	// kolory klawiszy:
	// Użyj CYAN YELLOW RED

	zero->color(FL_CYAN);
	zero->selection_color(FL_CYAN);
	jeden->color(FL_CYAN);
	jeden->selection_color(FL_CYAN);
	dwa->color(FL_CYAN);
	dwa->selection_color(FL_CYAN);
	trzy->color(FL_CYAN);
	trzy->selection_color(FL_CYAN);
	cztery->color(FL_CYAN);
	cztery->selection_color(FL_CYAN);
	piec->color(FL_CYAN);
	piec->selection_color(FL_CYAN);
	szesc->color(FL_CYAN);
	szesc->selection_color(FL_CYAN);
	siedem->color(FL_CYAN);
	siedem->selection_color(FL_CYAN);
	osiem->color(FL_CYAN);
	osiem->selection_color(FL_CYAN);
	dziewiec->color(FL_CYAN);
	dziewiec->selection_color(FL_CYAN);
	kropka->color(FL_CYAN);
	kropka->selection_color(FL_CYAN);
	Fl_Color kolor = FL_DARK_CYAN;
	
	kasuj->color(kolor);
	kasuj->selection_color(kolor);
	wynik->color(kolor);
	wynik->selection_color(kolor);
	znak->color(kolor);
	znak->selection_color(kolor);
	plus->color(kolor);
	plus->selection_color(kolor);
	minus->color(kolor);
	minus->selection_color(kolor);
	mnozenie->color(kolor);
	mnozenie->selection_color(kolor);
	dzielenie->color(kolor);
	dzielenie->selection_color(kolor);

	procent->color(kolor);
	procent->selection_color(kolor);
//	procent->box(FL_PLASTIC_UP_BOX);
	procent->callback(callback_Procent);
	procent->shortcut(FL_Page_Up);
	procent->tooltip("Klawisz\nPage Up");

	Fl_Repeat_Button *sinus = new Fl_Repeat_Button(225, 80, 40, 30, "sin");
	Fl_Repeat_Button *cosinus = new Fl_Repeat_Button(225, 120, 40, 30, "cos");
	Fl_Repeat_Button *tangens = new Fl_Repeat_Button(225, 160, 40, 30, "tan");
	Fl_Repeat_Button *cotangens = new Fl_Repeat_Button(225, 200, 40, 30, "ctan");
	Fl_Repeat_Button *sinush = new Fl_Repeat_Button(270, 80, 40, 30, "sinh");
	Fl_Repeat_Button *cosinush = new Fl_Repeat_Button(270, 120, 40, 30, "cosh");
	Fl_Repeat_Button *tangensh = new Fl_Repeat_Button(270, 160, 40, 30, "tanh");

	Fl_Repeat_Button *wart = new Fl_Repeat_Button(315, 80, 40, 30, "fabs");
	Fl_Repeat_Button *pierw = new Fl_Repeat_Button(315, 120, 40, 30, "sqrt");
	Fl_Repeat_Button *pot2 = new Fl_Repeat_Button(315, 160, 40, 30, "^2");
	Fl_Repeat_Button *pot3 = new Fl_Repeat_Button(315, 200, 40, 30, "^3");
	wart->tooltip("Wartosc\nbezwzgledna");
	pierw->tooltip("Pierwiastek\nkwadratowy");
	pot2->tooltip("Podnies\ndo II potegi");
	pot3->tooltip("Podnies\ndo III potegi");

	kolor = FL_CYAN;

	wart->color(kolor);
	wart->selection_color(kolor);
	pierw->color(kolor);
	pierw->selection_color(kolor);

	pot2->color(kolor);
	pot2->selection_color(kolor);
	pot3->color(kolor);
	pot3->selection_color(kolor);


	sinus->color(kolor);
	sinus->selection_color(kolor);
	cosinus->color(kolor);
	cosinus->selection_color(kolor);

	tangens->color(kolor);
	tangens->selection_color(kolor);
	cotangens->color(kolor);
	cotangens->selection_color(kolor);

	tangensh->color(kolor);
	tangensh->selection_color(kolor);
	sinush->color(kolor);
	sinush->selection_color(kolor);
	cosinush->color(kolor);
	cosinush->selection_color(kolor);

// Dodatkowe funkcje zwrotne:
	pierw->callback(callback_Pierwiastek);
	sinus->callback(callback_Sin);
	sinush->callback(callback_Sinh);
	cosinus->callback(callback_Cos);
	cosinush->callback(callback_Cosh);
	tangens->callback(callback_Tan);
	cotangens->callback(callback_CTan);
	tangensh->callback(callback_Tanh);
	wart->callback(callback_Bezwzgledna);
	pot2->callback(callback_Pot2);
	pot3->callback(callback_pot3);

  window->end();
  window->show();
  return Fl::run();
}

void Plus( double wynik ) {
	poprzedni += wynik;
	// Wyświetl:
	wyswietl();
}

void Minus( double wynik ) {
	poprzedni -= wynik;
	wyswietl();
}

void Dziel( double wynik ) {
	if(wynik == 0.00) {
		poprzedni = wynik;
		okno->value("");
		fl_message("Blad dzielenia przez zero!");
		return;
	}
	poprzedni /= wynik;
	wyswietl();
}

void Mnoz( double wynik ) {
	poprzedni *= wynik;
	wyswietl();
}

void Procent( double wynik ) {
	if(Operator == Procent || Operator == Wynik) return; // Nie wyciągaj kilka razy pierwiastka
		// lub dla operatora == (ktorego nie ma)
	// Niestety nawet z rzutowaniem nie działa switch, case ...
 	 if(Operator == Plus)
		poprzedni += (poprzedni * (wynik / 100));
	 else if(Operator == Minus)
		poprzedni = (-(wynik / 100) * poprzedni) + poprzedni;
	 else if(Operator == Dziel)
		poprzedni /= (wynik / 100);
	 else if(Operator == Mnoz)
		poprzedni *= (wynik / 100);
	else poprzedni = wynik / 100;

	Operator = Procent;
	wyswietl();
	stop = true; // Blokowanie =
	klej = false;
	kropka = false;
}


void callback_ObslugaPlus(Fl_Widget *w, void *data) {
	Operator = Plus;
	wspolne();
}

void Sinus( double wynik ) {
	poprzedni = sin(wynik);
	wyswietl();
}


void Cosinus( double wynik ) {
	poprzedni = cos(wynik);
	wyswietl();
}


void Sinush( double wynik ) {
	poprzedni = sinh(wynik);
	wyswietl();
}


void Cosinush( double wynik ) {
	poprzedni = cosh(wynik);
	wyswietl();
}


void Tangens( double wynik ) {
	poprzedni = tan(wynik);
	wyswietl();
}

void Tangensh( double wynik ) {
	poprzedni = tanh(wynik);
	wyswietl();
}


void Cotangens( double wynik ) {
	poprzedni = 1 / tan(wynik);
	wyswietl();
}


void Bezwzgledna( double wynik ) {
	poprzedni = fabs(wynik);
	wyswietl();
}


void Potega2( double wynik ) {
	poprzedni = pow(wynik,2);
	wyswietl();
}

void Pierwiastek( double wynik ) {
	if(wynik < 0) {
		fl_message("Liczba nie moze byc ujemna.");
		return;
	}
	poprzedni = sqrt(wynik);
	wyswietl();
}

void Potega3( double wynik ) {
	poprzedni = pow(wynik,3);
	wyswietl();
}

void callback_ObslugaMnoz(Fl_Widget *w, void *data) {
	Operator = Mnoz;
	wspolne();
}

void callback_Procent(Fl_Widget *w, void *data) {
	Procent(atof(okno->value()));
}

void callback_ObslugaDziel(Fl_Widget *w, void *data) {
	Operator = Dziel;
	wspolne();
}

void callback_ObslugaMinus(Fl_Widget *w, void *data) {
	// Zmiana znaku
	Operator = Minus;
	wspolne();
}

void callback_Sin(Fl_Widget *w, void *data) {
	Operator = Sinus;
	wspolne();
	stop = true;
	Sinus(poprzedni);
}


void callback_Pierwiastek(Fl_Widget *w, void *data) {
	Operator = Pierwiastek;
	wspolne();// poprzedni = atof(okno->value())
	stop = true;
	Pierwiastek(poprzedni);
}

void callback_Sinh(Fl_Widget *w, void *data) {
	Operator = Sinush;
	wspolne();
	stop = true;
	Sinush(poprzedni);
}

void callback_Cos(Fl_Widget *w, void *data) {
	Operator = Cosinus;
	wspolne();
	stop = true;
	Cosinus(poprzedni);
}

void callback_Cosh(Fl_Widget *w, void *data) {
	Operator = Cosinush;
	wspolne();
	stop = true;
	Cosinush(poprzedni);
}


void callback_Tan(Fl_Widget *w, void *data) {
	Operator = Tangens;
	wspolne();
	stop = true;
	Tangens(poprzedni);
}

void callback_CTan(Fl_Widget *w, void *data) {
	Operator = Cotangens;
	wspolne();
	stop = true;
	Cotangens(poprzedni);
}

void callback_Tanh(Fl_Widget *w, void *data) {
	Operator = Tangensh;
	wspolne();
	stop = true;
	Tangensh(poprzedni);
}

void callback_Bezwzgledna(Fl_Widget *w, void *data) {
	Operator = Bezwzgledna;
	wspolne();
	stop = true;
	Bezwzgledna(poprzedni);
}

void callback_Pot2(Fl_Widget *w, void *data) {
	Operator = Potega2;
	wspolne();
	stop = true;
	Potega2(poprzedni);
}

void callback_pot3(Fl_Widget *w, void *data) {
	Operator = Potega3;
	wspolne();
	stop = true;
	Potega3(poprzedni);
}

void callback_ObslugaZnak(Fl_Widget *w, void *data) {
	// Sprawdź 1 znak
	std::string s(okno->value());
	if(!s.empty() && s[0] != '-') {
		s.insert(0, "-", 1);
		okno->value(s.c_str());
	} else { // wytnij
		s.erase(s.begin(), s.begin() + 1);
		okno->value(s.c_str());		
	}
}

void callback_Liczba(Fl_Widget *w, void *data) {

	if(!klej) okno->value("");

	std::string s(okno->value());
	s += w->label();// Label jest Napisem na przycisku np. 7
	okno->value(s.c_str());
	klej = true;
	stop = false;
}

void callback_1LiczbaZero(Fl_Widget *w, void *data) {
	if(!klej) okno->value("");
	std::string s(okno->value());
	klej = true;
	stop = false;
	// Jak 1 liczba to 0 to po niej MUSI być kropka
	if(s.empty()) { // nic nie ma a wciśniemy 0
		okno->value("0."); // następna nie może być kropka
		kropka = true; // Jest już wstawiona
		// to w sumie zapewnie ze nie dokleje 2 kropki
		return;
	}
	s += w->label();
	okno->value(s.c_str());


}

void callback_Kropka(Fl_Widget *w, void *data) {
	if(klej && !kropka){ // Nie bylo jeszcze kropki
	std::string s(okno->value());
	s += w->label();
	okno->value(s.c_str());
	kropka = true; // nastepna kropka dla nie klej
	}
		
}


void callback_Rownosc(Fl_Widget *w, void *data) {
	if(!stop)
		Operator(atof(okno->value()));
	Operator = Wynik;// Virtualny w praktyce funkcja nigdy nie używana
	// Wskaźnik do niej jest za to wykorzysttywany jako sygnalizator
	stop = true;
	kropka = false;
}

void callback_Kasuj(Fl_Widget *w, void *data) {
	poprzedni = 0.00;
	okno->value("");
}

void wspolne() {
	klej = false;
	kropka = false;
	poprzedni = atof(okno->value());
}

void wyswietl() {
	// Wyświetl:
	std::ostringstream os;
	os << poprzedni;
	okno->value(os.str().c_str());
}

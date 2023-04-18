#pragma once

typedef int TElem;

class IteratorLP;
//referire a clasei Nod
class Nod;
typedef Nod* Pnod;
class Nod
{ 
public:
	friend class Lista;
	Nod(TElem e, Pnod urm, Pnod prec);
	TElem element();
	Pnod urmator();
	Pnod precedent();
private:
	TElem e;
	//cele doua legaturi -lista dublu inlantuita;
	Pnod urm, prec;
};
class Lista {
private:
	friend class IteratorLP;
	

	//primul si ultimul element din lista
	Pnod primul;
	Pnod ultimul;
	
public:

		// constructor
		Lista ();

		// returnare dimensiune
		int dim() const;

		// verifica daca lista e vida
		bool vida() const;

		// prima pozitie din lista
		IteratorLP prim() const;

		// returnare element de pe pozitia curenta
		//arunca exceptie daca poz nu e valid
		TElem element(IteratorLP poz) const;

		// modifica element de pe pozitia poz si returneaza vechea valoare
		//arunca exceptie daca poz nu e valid
		TElem modifica(IteratorLP poz, TElem e);

		// adaugare element la inceput
		void adaugaInceput(TElem e);		

		// adaugare element la sfarsit
		void adaugaSfarsit(TElem e);

		// adaugare element dupa o pozitie poz
		//dupa adaugare poz este pozitionat pe elementul adaugat
		//arunca exceptie daca poz nu e valid
		void adauga(IteratorLP& poz, TElem e);

		// sterge element de pe o pozitie poz si returneaza elementul sters
		//dupa stergere poz este pozitionat pe elementul de dupa cel sters
		//arunca exceptia daca poz nu e valid
		TElem sterge(IteratorLP& poz);

		// cauta element si returneaza prima pozitie pe care apare (sau iterator invalid)
		IteratorLP cauta(TElem e) const;

		//destructor

		~Lista();
};

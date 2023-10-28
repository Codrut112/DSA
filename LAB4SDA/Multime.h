#pragma once
#include <exception>
#define NULL_TELEM -80000
#define STERS -80001
typedef int TElem;

class IteratorMultime;

class Multime {
	friend class IteratorMultime;

    private:
		int m,DIM;//m-numarul de locatii din tabela de dispersie,DIM-numarul de elemente
		//tabela de elemente
		TElem* e;
		//functie de dispersie 
		int d(TElem e, int i) const;
		void redispersare();
		//returneaza urmatorul element prim dupa x
		int next_prim(int x);
		
    public:
 		//constructorul implicit
		Multime();

		//adauga un element in multime
		//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
		bool adauga(TElem e);

		//sterge un element din multime
		//returneaza adevarat daca elementul a existat si a fost sters
		bool sterge(TElem e);

		//verifica daca un element se afla in multime
		bool cauta(TElem elem) const;


		//intoarce numarul de elemente din multime;
		int dim() const;

		//verifica daca multimea e vida;
		bool vida() const;

		//returneaza un iterator pe multime
		IteratorMultime iterator() const;

		// returnează diferența dintre valoarea maximă și cea minimă (presupunem valori întregi) 
        // dacă mulțimea este vidă, se returnează -1 
        int diferențaMaxMin() const;

		// destructorul multimii
		~Multime();
};





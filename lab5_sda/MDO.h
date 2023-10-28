#pragma once
#define NULL_key -2000
#include <vector>

typedef int TCheie;
typedef int TValoare;

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

using namespace std;

class IteratorMDO;

typedef bool(*Relatie)(TCheie, TCheie);
class Nod;
typedef Nod* Pnod;
class Nod
{
public:
	friend class MDO;
	Nod(TElem e, Pnod st, Pnod dr, Pnod parinte) : e{ e }, st{ st }, dr{ dr }, parinte{ parinte } {};
	TElem element()const ;
	Pnod stanga()const;
	Pnod dreapta()const;

private:
	TElem e;

	Pnod st, dr,parinte;
	
};

class MDO {
	friend class IteratorMDO;
	
    private:
		Pnod rad;
		Relatie r;
		int DIM;

		bool sterge_recursiv(Pnod nod, TCheie c, TValoare v);
		void destructor(Pnod nod);

    public:
		

	// constructorul implicit al MultiDictionarului Ordonat
	MDO(Relatie r);

	// adauga o pereche (cheie, valoare) in MDO
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MDO 
	int dim() const;

	//verifica daca MultiDictionarul Ordonat e vid 
	bool vid() const;

	// se returneaza iterator pe MDO
	// iteratorul va returna perechile in ordine in raport cu relatia de ordine
	IteratorMDO iterator() const;

	// elimină o cheie împreună cu toate valorile sale 
    // returneaza un vector cu valorile care au fost anterior asociate acestei chei (și au fost eliminate) 
	vector<TValoare> stergeValoriPentruCheie(TCheie cheie);
	
	// destructorul 	
	~MDO();

};

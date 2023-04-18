#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>

using namespace std;
//complexitate: theta(n_elm)
void Colectie::redim_elm() {
	//alocam un spatiu de capacitate dubla 
	TElem* e_nou=new TElem[2*cp_elm];
	
	cp_elm = 2 * cp_elm;
	
	//copiem vechile valori in noua zona de memorie
	for (int i = 0; i < n_elm; i++)
		e_nou[i] = e[i];

	//stergem vechiul vector
	delete[] e;
	
	//vectorul indica spre noua zona
	e = e_nou;

}

//complexitate: theta(n_poz)
void Colectie::redim_poz() {
	//alocam un spatiu de capacitate dubla 
	int* poz_nou = new int[2 * cp_poz];
	
	cp_poz = 2 * cp_poz;
	
	//copiem vechile valori in noua zona de memorie
	for (int i = 0; i < n_poz; i++)
		poz_nou[i] = poz[i];


	//dealocam
	delete[] poz;

	poz = poz_nou;



}

//complexitate: theta(1)
Colectie::Colectie() {
	
	//setam capacitatea
	this->cp_poz = 1;
	this->cp_elm = 1;

	//alocam spatiu de memorare pentru vector
	e= new TElem[cp_elm];
	poz = new int[cp_poz];

	//setam numarul de elemente
	this->n_elm = 0;
	this->n_poz = 0;


}

//complexitate: O(n_poz)
void Colectie::adauga(TElem elem) {

	bool gasit = cauta(elem);
	if (gasit)
	{
		if (n_poz == cp_poz)redim_poz();
		int i = 0;
		while (e[i] != elem)i++;
		poz[n_poz] = i;
		n_poz++;
	}
	else {
		if (n_elm == cp_elm)redim_elm();
		if (n_poz == cp_poz)redim_poz();
	
		e[n_elm] = elem;
		poz[n_poz] = n_elm;
		n_elm++;
		n_poz++;}
}

//complexitate O(n_poz)
bool Colectie::sterge(TElem elem) {
	if (n_elm == 0)return false;
	

	
		int nr_ap = 0, ap;
	for (int i = 0; i < n_poz; i++)
		if (e[poz[i]] == elem)
		{
			
			nr_ap++; ap = i;
		}

	if (nr_ap == 0)
		return false;

	if (nr_ap == 1)
	{
		for (int i = poz[ap]; i < n_elm - 1; i++)
			e[i] = e[i + 1];
		n_elm--;
		for (int i = 0; i < n_poz; i++)
			if (poz[i] > poz[ap])
				poz[i]--;
		for (int i = ap; i < n_poz - 1; i++)
			poz[i] = poz[i + 1];
		n_poz--;
		return true;
	}

	if (nr_ap > 1) {
		for (int i = ap; i < n_poz - 1; i++)
			poz[i] = poz[i + 1];
		n_poz--; 
		return true;
	}




	
}

//complexitate: O(n_elm)
bool Colectie::cauta(TElem elem) const {
	for (int i = 0; i < n_elm; i++)
		if (e[i] == elem)
			return true;
	return false;
}

//complexitate theta(n_poz)
int Colectie::nrAparitii(TElem elem) const {
	int nr_ap=0;

	for (int i = 0; i < n_poz; i++)
		if (e[poz[i]] == elem)
			nr_ap++;

	return nr_ap;
}

//complexitate theta(1)
int Colectie::dim() const {
	return n_poz;
	
}

//complexitate theta(1)
bool Colectie::vida() const {
	return n_poz == 0;
	
}
//complexitate theta(1)
IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}

//complexitate theta(1)
Colectie::~Colectie() {
	delete[] this->e;	
	delete[] this->poz;
}

//complexitate theta(1)
void Colectie::goleste()
{
	delete[] e;
	delete[] poz;

	//setam capacitatea
	this->cp_poz = 1;
	this->cp_elm = 1;

	//alocam spatiu de memorare pentru vector
	e = new TElem[cp_elm];
	poz = new int[cp_poz];

	//setam numarul de elemente
	this->n_elm = 0;
	this->n_poz = 0;

}



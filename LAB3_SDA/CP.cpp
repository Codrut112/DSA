
#include "CP.h"
#include <exception>
#include <stdio.h>
#include <iostream>
using namespace std;

//complextate Theta(cp)
void CP::redim()
{
	//crearea unui nou spatiu in memorie
	int new_cp = 2 * cp;
	Element* new_elem = new Element[new_cp];
	int* new_urm = new int[new_cp];
	int* new_prec = new int[new_cp];
	//copierea vechilor elemente
	for (int i = 0; i < cp; i++)
	{
		new_urm[i] = urm[i];
		new_prec[i] = prec[i];
		new_elem[i] = elem[i];
	   }
	for (int i = cp; i < new_cp; i++)
		new_urm[i] = i + 1;
	
	//distrugerea spatiului vechi de memorie
	delete[] elem;
	delete[] prec;
	delete[] urm;


	primLiber = cp;
	urm = new_urm;
	prec = new_prec;
	elem = new_elem;
	cp = new_cp;
	urm[cp - 1] = -1;

}
//complexitate Theta(cp)
void CP::init_spatiu_liber()
{    
	//marchez toate pozitiile din  vector ca find libere
	for (int i = 0; i < cp-1; i++) 
		urm[i] = i + 1;
	//marcam	
    urm[cp - 1] = -1;
	primLiber = 0;
}
//caz favorabil theta(1)
//caz defavorabil theta(cp)
//caz mediu theta(cp)
//complexitate generala O(n)
int CP::aloca()
{
    //daca nu mai avem nici un spatiu liber facem redimensionare	
	if (primLiber == -1)redim();
	
	int pozitie_libera = primLiber;

		primLiber = urm[primLiber];
		
		return pozitie_libera;
	

}
//complexitate theta(1)
void CP::dealoca(int i)
{
	//adaugam la inceptul listei noua pozitie libera
	urm[i] = primLiber;
	primLiber = i;
}


CP::CP(Relatie r) {
	this->cp = 1;
	this->prim = -1;
	this->ultim = -1;
	this->r = r;
	this->elem = new Element[cp];
	this->urm = new int[cp];
	this->prec = new int[cp];
	init_spatiu_liber();
}

//caz favorabil: theta(1)
//caz defavorabil: theta(n)
//caz mediu: theta(n)
//complexitate generala: O(n)
void CP::adauga(TElem e, TPrioritate p) {


	int poz = aloca();

	
	//nu avem nici un element in coada
	if (prim == -1) {
		//noul element adaugat este atat primul cat si ultimul
		prim = poz;
		ultim = poz;
		urm[poz] = -1;
		prec[poz] = -1;
		this->elem[poz] = make_pair(e, p);

	}
	else {
		
		int t = prim;
		int i = 0;
		//cautam pozitia in coada a noului element
		while (r(elem[t].second, p) and t!=-1)
		{
			i++;
			
			t = urm[t]; ;
		}
		//elementul trebuie pus pe prima pozitie
		if (t == prim) {
			
			urm[poz] = prim;
			prec[prim] = poz;
			prec[poz] = -1;
			
			prim = poz;
			this->elem[poz] = make_pair(e, p);
			
		}
		else {
			//elementul nu se pune nici primul nici ultimul in coada
			if (t != -1)
			{
			    int pred = prec[t];
				int nxt = t;
				urm[pred] = poz;
				prec[nxt] = poz;
				urm[poz] = nxt;
				prec[poz] = pred;
				this->elem[poz] = make_pair(e, p);
			
				
			}
			//noul element este ultimul
			else {
				
				urm[poz] = -1;
				prec[poz] = ultim;
				urm[ultim] = poz;
				ultim = poz;
				this->elem[ultim] = make_pair(e, p);
				

			}
		}

	}

}
//complexitate theta(1)
//arunca exceptie daca coada e vida
Element CP::element() const {
	if (vida()) throw exception("coada este vida");
	return elem[prim];
;
}
//complexitate theta(1)
Element CP::sterge() {
	if (vida()) throw exception("coada este vida");
	Element e=elem[prim];
int urmatorul= urm[prim];
dealoca(prim);//dealoca spatiul care era ocupat de primul element
prim = urmatorul;
	return e;
}
//complexitate theta(1)
bool CP::vida() const {
	return prim == -1;
	
}

//theta(1)
CP::~CP() {
	delete[] urm;
	delete[] prec;
	delete[] elem;
};


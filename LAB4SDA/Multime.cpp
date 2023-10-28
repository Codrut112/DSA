#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>

//complexitate theta(1)
int Multime::d(TElem e, int i) const
{   
	return (abs(e) % m + i * (1 + abs(e) % (m - 2)))%m;
}

//complexitate theta(m)
void Multime::redispersare()
{    

	
	int copie_m = m;
	TElem* copie_e = e;
	m = next_prim(2*m);
	TElem* new_e = new TElem[m];
	this->e = new_e;
	//marcam elementele zonele din tabela ca fiind goale
	for (int i = 0; i < m; i++)
		e[i] = NULL_TELEM;
	//adaugam elementele in noua zona de memorie
	for (int i = 0; i < copie_m; i++) {
		if (copie_e[i] != NULL_TELEM or copie_e[i]==STERS)
			adauga(copie_e[i]);
	}
	//functia de adauga a incrementat DIM si trebuie scazut deoarece nu am adaugat elemente noi,le-am readaugat pe cele vechi 
	DIM -= copie_m;
	
	delete[] copie_e;

}
//complexitate O(sqrt(x))
int Multime::next_prim(int x)
{   
	while (true) {
		x++;
		bool prim = true;
		for (int i = 2; i <= sqrt(x); i++)
			if (x % i == 0)prim = false;
		if (prim == true)return x;
	}
}



//complexitate theta(m)
Multime::Multime() {
	this->m = 3;
	e = new TElem[m];
	this->DIM = 0;
	for (int i = 0; i < m; i++)
		this->e[i] = NULL_TELEM;
}

//complexitate O(m)
bool Multime::adauga(TElem elem) {
	int i = 0;
	if(m==DIM)redispersare();
	
	while (i < m ) {
		int j = d(elem, i);
		if (e[j] == elem)return false;
		if (e[j] == NULL_TELEM or e[j]==STERS)
		{
			
			DIM++;
			e[j] = elem;
		
			return true;
		}
		i++;
}


}

//complexitate O(m)
bool Multime::sterge(TElem elem) {
	int i = 0;

	while (i < m) {
		int j = d(elem, i);
		if (e[j] == elem) {
			DIM--;
			e[j] = STERS;
			return true;
		}
		if (e[j] == NULL_TELEM)return false;
		i++;
	}
}

//complexitate O(m)
bool Multime::cauta(TElem elem) const {
	int i = 0;
	while (i < m) {
		
		int j =d(elem,i);
		
		if (e[j] == elem) {
		
	     return true;
		}
		if (e[j] == NULL_TELEM)return false;
		i++;
	}
	return false;
}

//complexitate theta(1)
int Multime::dim() const {
	
	return DIM;
}
//complexitate theta(1)
bool Multime::vida() const {
	return DIM == 0;
}

//complexitate theta(m)
int Multime::diferențaMaxMin() const
{
	if (vida())return -1;
	IteratorMultime im = iterator();
	im.prim();

	TElem mx = im.element(), mn = im.element();

	while (im.valid()) {
		TElem e = im.element();

		if (e > mx)mx = e;
		if (e < mn)mn = e;
		im.urmator();
	}
	return mx - mn;
}

//complexitate theta(1)
Multime::~Multime() {
	delete[] e;
}


//complexitate theta(1)
IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}


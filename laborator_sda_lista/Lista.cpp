
#include <exception>

#include "IteratorLP.h"
#include "Lista.h"

#include <iostream>
//cosntructor element
Nod::Nod(TElem e, Pnod urm, Pnod prec) {
	this->e = e;
	this->urm = urm;
	this->prec = prec;
}
TElem Nod::element() {
	return e;
}
Pnod Nod::urmator(){
	return urm;
}
Pnod Nod::precedent(){
	return prec;
}
//constructor lista
Lista::Lista() {
   
	this->ultimul = nullptr;
	this->primul =nullptr;
	
}
//complexitate theta(n)
int Lista::dim() const {
	
	//cazul in care in lista nu se afla niciun element
	if (primul == NULL and ultimul == NULL)
		return 0;
		Pnod p = this->primul;
		
		if (ultimul == primul) return 1;//daca in lista exista un singur element atunci elementul este atat primul cat si ultimul
		int dim = 1;//ultimul nu este numarat deci setam dimensiunea la 1
	while (p != ultimul and p!=nullptr) {
		
		dim++;
		p = p->urm;//parcurgem lista
	}
	return dim ;
}

//complexitate theta(n)
bool Lista::vida() const {
	
	return dim() == 0;
	
}

//complextate theta(1)
IteratorLP Lista::prim() const {
	IteratorLP it = IteratorLP(*this);
	it.curent = primul;
	return it;
}

//complexitate theta(1)
TElem Lista::element(IteratorLP poz) const {
	if (poz.valid()) return poz.element();
	else throw std::exception("iterator invalid");
}

//complexitate 
//caz favorabil: theta(1)-iterator invalid
//caz defavorabil: theta(n)-iterator valid
//complexitate generala: O(n)
TElem Lista::sterge(IteratorLP& poz) {
	//daca pozitia este invalida aruncam exceptie
	if (!poz.valid()) throw std::exception("iterator invalid");
	//daca in lista avem un singur element
	if (dim() == 1) {
		primul = NULL;
		ultimul = NULL;
		return poz.curent->e;

	}
	Pnod p = poz.curent;
	p->prec->urm = p->urm;
	p->urm->prec = p->prec;
	TElem e = p->e;
	delete p;
	return e;
	
}
//complexitate: O(n)
IteratorLP Lista::cauta(TElem e) const{
	
	if (vida()) throw std::exception("iterator invalid");
	
	Pnod nod = primul;
	
	while (nod != ultimul and nod->element() != e)  nod = nod->urm;//cautam in lista elementul
	
	
	
	Lista lista_vida;
	if (nod->element() != e) return IteratorLP(lista_vida);//daca nu am gasit elementul returnam un iterator invalid;
	
	IteratorLP it = IteratorLP(*this);
	it.curent = nod;
	return it;
}

//complexitate theta(1)
TElem Lista::modifica(IteratorLP poz, TElem e) {
	if (!poz.valid()) throw std::exception("iterator invalid");
	else {
		TElem e_vechi = poz.curent->e;
		poz.curent->e = e;
		return e_vechi;
	}
	
}

//complexitate theta(1)
void Lista::adauga(IteratorLP& poz, TElem e) {
	
	if (!poz.valid())  throw std::exception("iterator invalid"); 

	if (poz.curent != ultimul)
	{
		Pnod p = new Nod(e, nullptr, nullptr);
		Pnod next = poz.curent->urm;
		poz.curent->urm = p;
		p->urm = next;
		next->prec = p;
		p->prec = poz.curent;
		poz.curent = p;
	}
	else {//daca elementul dupa care trebuie sa adaugam este ultimul
		
		Pnod p = new Nod(e, nullptr, ultimul);
		poz.curent->urm = p;
		ultimul = p;
		poz.curent = p;

	}
	
	
}

//complexitate theta(n)
void Lista::adaugaInceput(TElem e) {
	Pnod p=new Nod(e,nullptr,nullptr);
	
	
	//daca lista este vida setam elementul nou adaugat ca fiind atat primul cat si ultimul
	if (vida()) {
		ultimul = p;
		primul = p;
		
	}
	else {
		primul->prec = p;
		p->urm = primul;
		primul = p;
	}
}
//complexitate theta(n)
void Lista::adaugaSfarsit(TElem e) {
	Pnod p=new Nod(e,nullptr,nullptr);
	p->e = e;
	
	//daca lista este vida setam elementul nou adaugat ca fiind atat primul cat si ultimul
	if (vida()) {
		ultimul = p;
		primul = p;
	}
	else {
		ultimul->urm = p;
		p->prec = ultimul;
		ultimul = p;

	}
	
}
//complexitate theta(1)
Lista::~Lista() {
	
	while (primul != nullptr) {
		Pnod p = primul->urm;
		delete primul;
		primul = p;
}
}

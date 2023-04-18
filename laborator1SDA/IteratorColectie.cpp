#include "IteratorColectie.h"
#include "Colectie.h"
#include <exception>
//complexitate theta(1)
IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
	curent = 0;
}

//complexitate theta(1)
void IteratorColectie::prim() {
	curent = 0;
}

//complexitate theta(1)
void IteratorColectie::urmator() {
	if (!valid()) throw std::exception("iterator invalid");
	curent = curent + 1;
	
}

//complexitate theta(1)
bool IteratorColectie::valid() const {
	return curent<col.n_poz;
}


//complexitate theta(1)
TElem IteratorColectie::element() const {
	if (!valid()) throw std::exception("iterator invalid");
	return col.e[col.poz[curent]];
}

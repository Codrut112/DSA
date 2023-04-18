#include "IteratorLP.h"
#include "Lista.h"
#include <exception>
#include <iostream>
//complexitate theta(1)
IteratorLP::IteratorLP(const Lista& l):lista(l) {
	this->curent = l.primul;
}
//complexitate theta(1)
void IteratorLP::prim(){
	this->curent = lista.primul;
}
//complexitate theta(1)
void IteratorLP::urmator(){
	if (!valid()) throw std::exception("iterator invalid");
	this->curent = this->curent->urmator();
}
//complexitate theta(1)
bool IteratorLP::valid() const{
	
	return (curent != nullptr);
}
//complexitate theta(1)
TElem IteratorLP::element() const{
	if (valid() == true) return curent->element();
	else throw std::exception();
}



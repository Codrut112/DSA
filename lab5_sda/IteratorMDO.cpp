#include "IteratorMDO.h"
#include <iostream>
//complexitate theta(DIM)
IteratorMDO::IteratorMDO(const MDO& d) : dict(d) {
    prim();
}
//complexitate theta(DIM)
void IteratorMDO::prim() {
    curent = nullptr;
    //golim stiva de nouduri
    while (!stiva.empty()) {
        stiva.pop();
      
    }
    //setam pozitia curenta in radacina
    curent = dict.rad;
    //cautam cheia cea mai mica
    while (curent != nullptr) {
        stiva.push(curent);
    
        curent = curent->stanga();
    }
    //setam pozitia pe primul element(cel mai mic)
    if (!stiva.empty()) {
        curent = stiva.top();
        
    }
  
}
//complexitate theta(1)
TElem IteratorMDO::element() const {
    if (valid()) {
      
        return curent->element();
    }
    throw std::exception("IteratorMDO: Invalid iterator");
}
//complexitate theta(n)(n=inaltime nod curent)
void IteratorMDO::urmator() {
    if (!valid()) {
        throw std::exception("IteratorMDO: Invalid iterator");
    }
    stiva.pop();
    
   if (curent->dreapta() != nullptr) {
        curent = curent->dreapta();

        while (curent != nullptr) {
            stiva.push(curent);
        
   
            curent = curent->stanga();
        }
    }
     //setam noua pozitie
    if (!stiva.empty()) {
        curent = stiva.top();
   }

}
//complexitate theta(1)
bool IteratorMDO::valid() const {
    return curent != nullptr && !stiva.empty();
}
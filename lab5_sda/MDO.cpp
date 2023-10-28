#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>

#include <exception>
using namespace std;

//caz favorabil theta(1)-trebuie sa stergem radacina care nu are descendeenti
//caz defavorabil O(DIM)
//caz mediu O(log(DIM))
//complexitate generala O(log(DIM))
bool MDO::sterge_recursiv(Pnod nod, TCheie c, TValoare v)
{   //nu am gasit elementul de sters
	if (nod == nullptr or DIM==0)return false;
     //am gasit elementul de sters
	if (nod->e.first == c and nod->e.second == v) {
	
		    //este nod frunza
			if (nod->st == nullptr and nod->dr == nullptr) {
				//in cazul in care este radacina nu are parine
				if (nod != rad) {
					auto parinte = nod->parinte;
					//stergem informatiile parintelui despre fiu
					if (parinte->dr == nod)parinte->dr = nullptr;
					if (parinte->st == nod)parinte->st = nullptr;
				}
		        //stergerea efectiva a elementului
				delete nod;
				nod = nullptr;
			
				return true;

			}
			else {
				//are fiu drept
				if (nod->dr != nullptr)
				{   //punem pe pozitia gasita fiul drept al nodului
					nod->e = nod->dr->e;
					//stergem fiul drept
					return sterge_recursiv(nod->dr, nod->dr->e.first, nod->dr->e.second);
				}
				else {
					//are doar fiu stang
					nod->e = nod->st->e;
					return sterge_recursiv(nod->st, nod->st->e.first, nod->st->e.second);
       }
			

		}

	}    
	//parcurgem graful si cautam elementul
		if (r(nod->e.first, c)) {
			
			return sterge_recursiv(nod->dr, c, v);
		}
		else {
	
			return sterge_recursiv(nod->st, c, v);
		}
	
}

//complexitate theta(1)
MDO::MDO(Relatie r) :r{ r } {
	rad = nullptr;
	DIM= 0;
}
//complexitate theta(DIM)
void MDO::destructor(Pnod nod)
{
	
	if (nod != nullptr)
	{   
		if (nod->dr != nullptr)destructor(nod->dr);
		if (nod->st != nullptr)destructor(nod->st);
		delete nod;
	}
}
//complexitate theta(1)
TElem Nod::element() const {
	return e;
}
//complexitate theta(1)
Pnod Nod::stanga() const {
	return st;
}
//complexitate theta(1)
Pnod Nod::dreapta() const{
	return dr;
}
//caz favorabil theta(1)-arborele este gol
//caz defavorabil O(DIM)
//caz mediu O(log(DIM))
//complexitate generala O(log(DIM))
void MDO::adauga(TCheie c, TValoare v) {
	if (rad == nullptr) {
		Pnod x = new Nod(TElem(c, v), nullptr, nullptr, nullptr);
		rad = x;
	}
	else {
		auto nod = rad;
		Pnod parinte = nod;
		int dr = 0, st = 0;
		//cautam poziti in arbore a elementului
		while (nod != nullptr) {
			if (!r(nod->e.first, c)) {
				parinte = nod;
				nod = nod->st;
				st = 1;
				dr = 0;
			}
			else if (r(nod->e.first, c)) {
				parinte = nod;
				nod = nod->dr;
				dr = 1;
				st = 0;
			}
			else {
				break;
			}
		}
		if (st == 1) {
			parinte->st = new Nod(TElem(c, v), nullptr, nullptr, parinte);
		}
		else if (dr == 1) {
			parinte->dr = new Nod(TElem(c, v), nullptr, nullptr, parinte);
		}
	}
	DIM++;
}




//complexitate generala O(log(DIM))
vector<TValoare> MDO::cauta(TCheie c) const {
	vector<TValoare> stiva;
	auto nod = rad;
	
	if (vid())return vector<TValoare>();
	while (nod != nullptr) {
		if(nod != nullptr)
		while (!r(nod->e.first, c) )
		{
			if (nod->e.first == c)stiva.push_back(nod->e.second);
			nod = nod->st;
			if (nod == nullptr)break;
		}
		if(nod!=nullptr)
		while (r(nod->e.first, c) and nod != nullptr) {
			if (nod->e.first == c)stiva.push_back(nod->e.second);
			nod = nod->dr; 
			if (nod == nullptr)break;
		
		}
	}
	return stiva;
	
}
//caz favorabil theta(1)-trebuie sa stergem radacina care nu are descendenti
//caz defavorabil O(DIM)
//caz mediu O(log(DIM))
//complexitate generala O(log(DIM))
bool MDO::sterge(TCheie c, TValoare v) {
	
	bool sters=sterge_recursiv(rad, c, v);
	if (sters)DIM--;
	if (sters && rad == nullptr) rad = nullptr;
	return sters;
}
//complexitate theta(1)
int MDO::dim() const {
	
	return DIM;
}
//complexitate theta(1)
bool MDO::vid() const {
	return DIM == 0;
}
//complexitate theta(1)
IteratorMDO MDO::iterator() const {
	return IteratorMDO(*this);
}
//complexitate theta(DIM)
MDO::~MDO() {
	if(!vid())destructor(rad);
}
//complexitate O(log(DIM)*nr_val_sterse)
vector<TValoare> MDO::stergeValoriPentruCheie(TCheie cheie)
{
	vector<TValoare> valori_de_sters = cauta(cheie);
	

	for (auto const& valori : valori_de_sters) {
	
		sterge(cheie, valori);
}    
	return valori_de_sters;
}

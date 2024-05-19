#pragma once

#include <vector>

using namespace std;

typedef int TCheie;
typedef int TValoare;

#include <utility>
typedef std::pair<TCheie, vector<TValoare>> TElem;

using namespace std;

class IteratorMDO;

typedef bool(*Relatie)(TCheie, TCheie);

class MDO {
	friend class IteratorMDO;
    private:
	/* aici e reprezentarea */

	int capacitate = 100;
	int size = 0;
	int* urmator = new int[capacitate];

	TElem* tabela = new TElem[capacitate];
	
	int primLiber = 0;

	void actualizarePrimLiber();
	int hashing(TCheie cheie);

    public:

	// constructorul implicit al MultiDictionarului Ordonat
	MDO(Relatie r);

	// adauga o pereche (cheie, valoare) in MDO
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c);

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MDO 
	int dim() const;

	//verifica daca MultiDictionarul Ordonat e vid 
	bool vid() const;

	void goleste();

	// se returneaza iterator pe MDO
	// iteratorul va returna perechile in ordine in raport cu relatia de ordine
	IteratorMDO iterator() const;

	// destructorul 	
	~MDO();

};

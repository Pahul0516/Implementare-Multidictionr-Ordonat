#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>

#include <exception>
using namespace std;


// complexitate O(n)
MDO::MDO(Relatie r) {
	/* de adaugat */
	primLiber = 0;
	for (int i = 0; i <= capacitate; i++)
	{
		tabela[i].first = -1;
		urmator[i] = -1;
	}
}

//complexitate teta(1)
int MDO::hashing(TCheie cheie)
{
	if (cheie < 0)
		cheie *= -1;
	return cheie % 10;
}


//complexitate teta(n)
void MDO::actualizarePrimLiber()
{
	primLiber++;
	while (primLiber < capacitate && tabela[primLiber].first != -1)
	{
		primLiber = primLiber + 1;
	}
}

//complexitate teta(n)
void MDO::adauga(TCheie c, TValoare v) {
	/* de adaugat */
	int indice = hashing(c);
	if (tabela[indice].first == -1)
	{
		vector<TValoare> vec;
		vec.push_back(v);
		pair<TCheie, vector<TValoare>> val = make_pair(c, vec);
		tabela[indice] = val;
		size++;
		if (indice == primLiber)
			actualizarePrimLiber();
	}
	else
	{
		int precedent = 0;
		while (indice != -1 && c!=tabela[indice].first)
		{
			precedent = indice;
			indice = urmator[indice];
		}
		if (indice != -1)
		{
			tabela[indice].second.push_back(v);
			size++;
		}
		else
		{
			if (primLiber < capacitate - 1)
			{
				vector<TValoare> vec;
				vec.push_back(v);
				pair<TCheie, vector<TValoare>> val = make_pair(c, vec);
				tabela[primLiber] = val;
				size++;
				urmator[precedent] = primLiber;
				actualizarePrimLiber();
			}
		}
	}
} 

//complexitate teta(n)
vector<TValoare> MDO::cauta(TCheie c){
	/* de adaugat */
	int indice = hashing(c);
	while (indice != -1)
	{
		if (tabela[indice].first == c)
			return tabela[indice].second;
		indice = urmator[indice];
	}
	return vector<TValoare>  ();
}

	
//complexitate O(n)
bool MDO::sterge(TCheie c, TValoare v) {
	/* de adaugat */
	bool ok = false;
	vector<TValoare> valori = cauta(c);
	auto it = find(valori.begin(), valori.end(), v);
	if (valori.empty())
	{
		return false;
	}
	else
	{
		if (it == valori.end())
		{
			return false;
		}
		else
		{

			bool ok = false;
			int indice = hashing(c);
			while (indice != -1)
			{
				if (tabela[indice].first == c)
				{
					if (tabela[indice].second.size() > 1) // cazul cand sterg doar din lista asociata cheii
					{
						for (auto it = tabela[indice].second.begin(); it != tabela[indice].second.end(); it++)
						{
							if (*it == v)
							{
								tabela[indice].second.erase(it);
								break;
							}
						}
					}
					else // cazul cand terbuie sa sterg perechea cheie-valoare
					{
						int cheia_urmatoare = -1;
						int anterior = -1;
						while (indice != -1)
						{
							cheia_urmatoare = tabela[urmator[indice]].first;
							if (hashing(cheia_urmatoare) == indice && urmator[indice]!=-1)
							{
								tabela[indice].first = cheia_urmatoare;
								tabela[indice].second = tabela[urmator[indice]].second;
							}
							else
							{
								urmator[anterior] = urmator[indice];
								tabela[indice].first = -1;
								tabela[indice].second.clear();
								urmator[indice] = -1;

								// facem o reactiualizare a primLiber

								for (int i = 0; i <= capacitate; i++)
								{
									if (tabela[i].first == -1)
									{
										primLiber = i;
										break;
									}
								}
								ok = true;
								break;
							}
							anterior = indice;
							indice = urmator[indice];
						}
					}
				}
				indice = urmator[indice];
			}
			size--;
			return true;
		}
	}
}

//teta(1)
int MDO::dim() const {
	/* de adaugat */
	return size;
}

//teta(1)
bool MDO::vid() const {
	/* de adaugat */
	if (size == 0)
		return true;
	else
		return false;
}

//test(1)
IteratorMDO MDO::iterator() const {
	return IteratorMDO(*this);
}

//teta(1)
MDO::~MDO() {
	/* de adaugat */
	//delete[] urmator;
	//delete[] tabela;
}

//teta(N)
void MDO::goleste()
{
	if (size != 0)
	{
		primLiber = 0;
		for (int i = 0; i <= capacitate; i++)
		{
			tabela[i].first = -1;
			urmator[i] = -1;
		}
		size = 0;
	}
	else
		throw exception("MDO-ul este deja gol");
}



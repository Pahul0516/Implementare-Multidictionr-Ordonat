#include "IteratorMDO.h"
#include "MDO.h"

//teta (1)
IteratorMDO::IteratorMDO(const MDO& d) : dict(d){
	/* de adaugat */
	prim();
}

//teta(1)
void IteratorMDO::prim(){
	/* de adaugat */
	indice = 0;
}

//O(n)
void IteratorMDO::urmator(){
	/* de adaugat */
	indice++;
	while (this->dict.tabela[indice].first == -1)
	{

		indice++;
		if (valid() == false)
			break;
	}
}

//teta(1)
bool IteratorMDO::valid() const{
	/* de adaugat */
	if (indice == this->dict.capacitate || this->dict.size==0)
	{
		return false;
	}
	return true;
}

//O(N)
TElem IteratorMDO::element() const {
	/* de adaugat */

	int de_parcurs = 0;
	bool ok = 0;

	while (de_parcurs < this->dict.size)
	{
		if (Relatie(TCheie(this->dict.tabela[de_parcurs].first)))
		{
			ok = 1;
			break;
		}
		de_parcurs++;
	}

	TCheie a;
	if (ok == 1)
	{
		a = this->dict.tabela[de_parcurs].first;

	}
	else
	{
		a = this->dict.tabela[indice].first;
	}
	vector<TValoare> b = this->dict.tabela[indice].second;
	pair <TCheie, vector<TValoare>> de_returnat = make_pair(a, b);
	return pair<TCheie, vector<TValoare>>(0, 0);
}



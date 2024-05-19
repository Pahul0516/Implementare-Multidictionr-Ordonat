#include <assert.h>

#include "MDO.h"
#include "IteratorMDO.h"

#include <exception>
#include <vector>

using namespace std;

bool relatia_mea(TCheie cheie1, TCheie cheie2) {
    if (cheie1 <= cheie2) {
        return true;
    }
    else {
        return false;
    }
}

void testul_meu() {

    MDO d = MDO(relatia_mea);

    try
    {
        d.goleste();
    }
    catch (exception)
    {
        assert(true);
    }
    d.adauga(1, 2);
    d.adauga(1, 3);
    d.goleste();
    assert(d.vid()); 
    d.adauga(2, 1);
    d.adauga(3, 1);
    d.adauga(4, 1);
    d.goleste();
    assert(d.vid());
}


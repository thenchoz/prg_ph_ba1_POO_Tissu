#include <iostream>
#include "../general/Systeme.h"
#include "../text/TextView.h"

using namespace std;

int main()
{
	TextView ecran(cout);
	
	Vecteur3D nul(0,0,0);
	Vecteur3D rayon(0,0,30);
	
	TissuDisque tissu(&ecran, nul, rayon, 2, 6, 0.3, 0.9, 2, 72);
	
	Systeme syst(&ecran);
	syst.add_Tissu(&tissu);
	
	cout << "Au départ :" << endl;
	syst.dessine();
	
	return 0;
}

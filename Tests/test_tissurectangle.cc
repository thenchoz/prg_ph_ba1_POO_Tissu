#include <iostream>
#include "../general/Systeme.h"
#include "../text/TextView.h"

using namespace std;

int main()
{
	TextView ecran(cout);
	Vecteur3D nul;
	Vecteur3D largeur(20,0,0);
	Vecteur3D longueur(0,20,0);

	
	TissuRectangle tissu(&ecran,largeur, longueur, nul, 1, 0.4, 0.25, 2, 4);	
	
	Systeme syst(&ecran);
	syst.add_Tissu(&tissu);

	
	cout << "Au départ :" << endl;
	syst.dessine();
	
	return 0;
}

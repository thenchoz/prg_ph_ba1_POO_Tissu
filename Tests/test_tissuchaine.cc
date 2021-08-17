#include <iostream>
#include "../general/Systeme.h"
#include "../text/TextView.h"

using namespace std;

int main()
{
	TextView ecran(cout);
	
	Vecteur3D nul(0,0,0);
	Vecteur3D pos1(0,1,0);
	Vecteur3D pos2(0,2,0);
	Vecteur3D pos3(1,2,0);
	Vecteur3D pos4(1,2,1);
	
	TissuChaine tissu(&ecran,{nul,pos1,pos2,pos3,pos4},2, 0.3, 1, 2);		
	
	Systeme syst(&ecran);
	syst.add_Tissu(&tissu);

	
	cout << "Au départ :" << endl;
	syst.dessine();
	
	
	return 0;
}

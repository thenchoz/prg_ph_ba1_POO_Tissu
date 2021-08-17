#include <iostream>
#include "TextView.h"
#include "Systeme.h"
#include "Initial.h"

using namespace std;

int main()
{
	TextView ecran(cout);
	Systeme syst(&ecran);
	Initial in(&syst);
	double dt(0.1);
	
	cout << "Au départ :" << endl;
	syst.dessine();
	
	for(int i(1); i < 40; i++)
	{
		syst.evolue(dt, i * dt);
		cout << "Après " << i << " pas de calcul :" << endl;
		syst.dessine();
	}
	
	
	return 0;
}

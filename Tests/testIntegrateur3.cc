#include <iostream>
#include "../general/Integrateur.h"
#include "../general/Vecteur3D.h"
#include "../general/Ressort.h"
#include "../general/Masse.h"

using namespace std;

int main()
{
	Vecteur3D nul;
	double mas1(0.33);
	double mas2(1.0);
	double lambda(0.3);
	Vecteur3D vitesse;
	Vecteur3D position1(0.0, 0.0, -3.0);
	Vecteur3D position2(-0.5);
	Vecteur3D position3(0.5);
	
	Masse* masse1 = new Masse(mas1, position1, vitesse, lambda);
	Masse* masse2 = new Masse(mas2, position2, vitesse, lambda);
	Masse* masse3 = new Masse(mas2, position3, vitesse, lambda);
	
	double k(0.6);
	double l0(2.5);
	
	Ressort res1(k, l0, masse1, masse2);
	Ressort res2(k, l0, masse1, masse3);
	
	cout << "Situation de départ :" << endl;
	
	cout << *masse1 << endl
		 << *masse2 << endl
		 << *masse3 << endl;
	
	cout << res1 << endl
		 << res2 << endl;
		 
	cout << "============================================================" << endl << endl;
	
	double dt(0.1);
	IntegrateurEulerCromer inte;
	
	for(int i(1); i <= 4; i++)
	{
		cout << "T = " << i * dt << endl;
		
		masse1->mise_a_jour_forces();
		masse2->mise_a_jour_forces();
		masse3->mise_a_jour_forces();
		
		masse2->set_force(nul);
		masse3->set_force(nul);
		
		inte.evolue(masse1, dt);
		inte.evolue(masse2, dt);
		inte.evolue(masse3, dt);
		
		cout << *masse1 << endl
			 << *masse2 << endl
			 << *masse3 << endl;
			 
		cout << "============================================================" << endl << endl;
	}
	
	return 0;
}

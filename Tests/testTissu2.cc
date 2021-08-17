#include <iostream>
#include "../general/Tissu.h"

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
	
	vector<Masse*> masse({masse1, masse2, masse3});
	Tissu tissu(masse);
	
	double k(0.6);
	double l0(2.5);
	
	tissu.connect(k, l0, masse1, masse2);
	tissu.connect(k, l0, masse1, masse3);
	
	cout << "Situation de départ :" << endl;
	
	cout << tissu << endl;
		 
	cout << "============================================================" << endl << endl;
	
	double dt(0.1);
	IntegrateurEulerCromer inte;
	
	for(int i(1); i <= 4; i++)
	{
		cout << "T = " << i * dt << endl;
		
		tissu.mise_a_jour_force();
		
		masse2->set_force(nul);
		masse3->set_force(nul);
		
		tissu.evolue(inte, dt);
		
		cout << tissu << endl;
			 
		cout << "============================================================" << endl << endl;
	}
	
	delete masse1;
	delete masse2;
	delete masse3;
	
	return 0;
}

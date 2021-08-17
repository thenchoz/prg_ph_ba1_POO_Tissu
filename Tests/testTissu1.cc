#include <iostream>
#include "../general/Tissu.h"

using namespace std;

int main()
{
	Vecteur3D antigravite(0.0, 0.0, 9.81);
	double mas(1);
	double lambda(0.3);
	Vecteur3D vitesse;
	//pour test de bases
	/**
	Vecteur3D position1;
	Vecteur3D position2(2.0);
	Vecteur3D position3(0.0, 2.0);
	**/
	//pour test pos. équilibre
	
	Vecteur3D position1;
	Vecteur3D position2(1.5);
	Vecteur3D position3(1.25, 1.2247);
	
	//pour test ressort comprimé
	/**
	Vecteur3D position1;
	Vecteur3D position2(1.0);
	Vecteur3D position3(1.0, 1.0);
	**/
	
	Masse* masse1 = new Masse(mas, position1, vitesse, lambda);
	Masse* masse2 = new Masse(mas, position2, vitesse, lambda);
	Masse* masse3 = new Masse(mas, position3, vitesse, lambda);
	
	vector<Masse*> masse({masse1, masse2, masse3});
	Tissu tissu(masse);
	
	double k1(9);
	double k2(1.9);
	double k3(5.5);
	double l01(1.5);
	double l02(1.75);
	double l03(1.25);
	
	tissu.connect(k1, l01, masse1, masse2);
	tissu.connect(k2, l02, masse1, masse3);
	tissu.connect(k3, l03, masse2, masse3);
	
	cout << "Situation de départ :" << endl;
	
	cout << tissu << endl;
		 
	cout << "============================================================" << endl << endl;
	
	double dt(0.1);
	IntegrateurEulerCromer inte;
	
	for(int i(1); i <= 4; i++)
	{
		cout << "T = " << i * dt << endl;
		
		tissu.mise_a_jour_force();
		
		masse1->ajoute_force(mas * antigravite);
		masse2->ajoute_force(mas * antigravite);
		masse3->ajoute_force(mas * antigravite);
		
		tissu.evolue(inte, dt);
		
		cout << tissu << endl;
			 
		cout << "============================================================" << endl << endl;
	}
	
	delete masse1;
	delete masse2;
	delete masse3;
	
	return 0;
}


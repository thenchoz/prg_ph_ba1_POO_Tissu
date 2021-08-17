#include <iostream>
#include "../general/Integrateur.h"
#include "../general/Vecteur3D.h"
#include "../general/Ressort.h"
#include "../general/Masse.h"

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
	
	double k1(9);
	double k2(1.9);
	double k3(5.5);
	double l01(1.5);
	double l02(1.75);
	double l03(1.25);
	
	Ressort res1(k1, l01, masse1, masse2);
	Ressort res2(k2, l02, masse1, masse3);
	Ressort res3(k3, l03, masse2, masse3);
	
	cout << "Situation de départ :" << endl;
	
	cout << *masse1 << endl
		 << *masse2 << endl
		 << *masse3 << endl;
	
	cout << res1 << endl
		 << res2 << endl
		 << res3 << endl;
		 
	cout << "============================================================" << endl << endl;
	
	double dt(0.1);
	IntegrateurEulerCromer inte;
	
	for(int i(1); i <= 4; i++)
	{
		cout << "T = " << i * dt << endl;
		
		masse1->mise_a_jour_forces();
		masse2->mise_a_jour_forces();
		masse3->mise_a_jour_forces();
		
		masse1->ajoute_force(mas * antigravite);
		masse2->ajoute_force(mas * antigravite);
		masse3->ajoute_force(mas * antigravite);
		
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


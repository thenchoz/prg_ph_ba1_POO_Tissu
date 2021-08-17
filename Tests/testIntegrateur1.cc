#include <iostream>
#include "../general/Integrateur.h"
#include "../general/Vecteur3D.h"
#include "../general/Ressort.h"
#include "../general/Masse.h"

using namespace std;

int main()
{
	double t(0.01);
	IntegrateurEulerCromer inte;
	
	cout << "Situation de départ 1 :" << endl << endl;
	
	Vecteur3D position1(0.0, 0.0, 1.0);
	Vecteur3D vitesse1(1.0, 0.0, 2.0);
	Masse* mas1 = new Masse(0.127, position1, vitesse1);
	
	cout << *mas1 << endl;
	
	for(int i(1); i <= 3; i++)
	{
		mas1->mise_a_jour_forces();
		inte.evolue(mas1, t);
		cout << "T = " << t * i << endl
			 << *mas1 << endl;
			 
		cout << "==============================" << endl << endl;
	}
	
	
	cout << "Situation de départ 2 :" << endl << endl;
	
	Vecteur3D position2(0.0, 0.0, 0.0);
	Vecteur3D vitesse2(0.0, 0.0, 0.0);
	Masse* mas2 = new Masse(1/9.81, position2, vitesse2);
	
	cout << *mas2 << endl;
	
	for(int i(1); i <= 3; i++)
	{
		mas2->mise_a_jour_forces();
		inte.evolue(mas2, t);
		cout << "T = " << t * i << endl
			 << *mas2 << endl;
			 
		cout << "==============================" << endl << endl;
	}
	
	
	cout << "Situation de départ 3 :" << endl << endl;
	
	Vecteur3D position3(0.0, 0.0, 0.0);
	Vecteur3D vitesse3(0.0, 0.0, 0.0);
	Masse* mas3 = new Masse(1, position3, vitesse3, 1);
	
	cout << *mas3 << endl;
	
	for(int i(1); i <= 3; i++)
	{
		mas3->mise_a_jour_forces();
		inte.evolue(mas3, t);
		cout << "T = " << t * i << endl
			 << *mas3 << endl;
			 
		cout << "==============================" << endl << endl;
	}
	
	return 0;
}

#include <iostream>
#include "../general/Ressort.h"
#include "../general/Masse.h"
#include "../general/Vecteur3D.h"

using namespace std;

int main()
{
	Vecteur3D position1;
	Vecteur3D position2(1.0);
	Vecteur3D position3(2.0);
	double lambda(0.3);
	
	Masse mas1(1.0, position1, lambda);
	Masse mas2(2.0, position2, lambda);
	Masse mas3(3.0, position3, lambda);
	
	double k1(3.0);
	double k2(4.0);
	double L01(1.0);
	double L02(5.0);
	
	Ressort res1(k1, L01, &mas1, &mas2);
	cout << res1 << endl;
	
	Ressort res2(k2, L02, &mas2, &mas3);
	cout << res2 << endl;
	
	cout << "================================================================================================================================" << endl
		 << "A) Vérification de l'intégrité des ressorts après tous les ajouts :" << endl << endl;
		
	cout << res1 << endl
		 << res2 << endl
		 << endl;
	
	cout << "================================================================================================================================" << endl
		 << "B) Modification de la masse 2 (postition, vitesse et force)." << endl
		 << "   Les ressorts sont-ils informés des changements ? " << endl << endl;
	
	Vecteur3D changement(42.0, 42.0, 42.0);
	mas2.set_position(changement);
	mas2.set_vitesse(changement);
	mas2.set_force(changement);
	
	cout << mas2 << endl
		 << res1 << endl
		 << res2 << endl
		 << endl;
	
	cout << "================================================================================================================================" << endl
		 << "C) Vérification des forces :" << endl << endl;
 		 
	cout << "ressort " << &res1 << " sur masse " << &mas1 << " : " << res1.force_rappel(&mas1)
		 << "ressort " << &res1 << " sur masse " << &mas2 << " : " << res1.force_rappel(&mas2)
		 << "ressort " << &res1 << " sur masse " << &mas3 << " : " << res1.force_rappel(&mas3)
		 << endl
		 << "ressort " << &res2 << " sur masse " << &mas1 << " : " << res2.force_rappel(&mas1)
		 << "ressort " << &res2 << " sur masse " << &mas2 << " : " << res2.force_rappel(&mas2)
		 << "ressort " << &res2 << " sur masse " << &mas3 << " : " << res2.force_rappel(&mas3)
		 << endl;
	
	cout << "================================================================================================================================" << endl
		 << "D) Vérification de la mise à jour des forces :" << endl << endl;
		 
	
	mas1.mise_a_jour_forces();
	mas2.mise_a_jour_forces();
	mas3.mise_a_jour_forces();
	
	cout << "masse " << &mas1 << " : " << endl
		 << mas1 << endl
		 << "masse " << &mas2 << " : " << endl
		 << mas2 << endl
		 << "masse " << &mas3 << " : " << endl
		 << mas3 << endl
		 << endl;
	
	return 0;
}

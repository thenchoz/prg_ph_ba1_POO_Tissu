#include <iostream>
#include <vector>
#include "../general/Masse.h"
#include "../general/Vecteur3D.h"

using namespace std;


int main()
{
	Vecteur3D position1(1.0, 2.0, 3.0);
	Vecteur3D vitesse1(4.0, 5.0, 6.0);
	double mas1(2.3);
	double mas2(1.0);
	double lambda1(0.3);
	
	Masse masse1(mas1, position1, vitesse1, lambda1);
	Masse masse2(mas2);

	cout << masse1 << endl;
	cout << masse2 << endl;

	//test des accesseures
	cout << "Tests des get() :" << endl
		<< "masse = "		<< masse1.get_masse() << endl
		<< "lambda = "		<< masse1.get_lambda() << endl
		<< "position = " 	<< masse1.get_position()
		<< "vitesse = " 	<< masse1.get_vitesse()
		<< "force = " 		<< masse1.get_force()
	
		//test de la méthode acceleration
		<< "acceleration = " << masse1.acceleration() << endl;


	//test de la méthode ajoute_force
	Vecteur3D df(1.1, 2.2, 3.3);
	cout << "force = " << df;

	masse1.ajoute_force(df);
	cout << masse1;

	cout << "acceleration =" << masse1.acceleration() << endl;
	
	
	// le test de la méthode mise_a_jour se fera dans le test des ressorts
	
	return 0;
}

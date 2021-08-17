#include <iostream>
#include "../general/Systeme.h"
#include "../text/TextView.h"

using namespace std;

int main()
{
	double t(0.01);
	IntegrateurRungeKutta inte;
	TextView ecran(cout);
	
	/**Situation 1**/
	
	Vecteur3D position1(0.0, 0.0, 1.0);
	Vecteur3D vitesse1(1.0, 0.0, 2.0);
	Masse mas1(&ecran, 0.127, position1, vitesse1);
	
	Tissu tissu1(&ecran, {&mas1});
	
	Systeme syst(&ecran, &inte);
	syst.add_Tissu(&tissu1);
	
	cout << "Au départ :" << endl;
	mas1.dessine();
	
	for(int i(1); i < 68; i++)
	{
		syst.evolue(t, i * t);
		cout << endl << "Après " << i << " pas de calcul :" << endl;
		mas1.dessine();
	}
	
	/**Situation 2**/
	
	cout << "Situation de départ 2 :" << endl << endl;
	
	Vecteur3D position2;
	Vecteur3D vitesse2;
	Masse mas2(&ecran, 1/9.81, position2, vitesse2);
	
	Tissu tissu2(&ecran, {&mas2});
	
	Systeme syst2(&ecran, &inte);
	syst2.add_Tissu(&tissu2);
	
	cout << "Au départ :" << endl;
	mas2.dessine();
	
	for(int i(1); i < 68; i++)
	{
		syst2.evolue(t, i * t);
		cout << endl << "Après " << i << " pas de calcul :" << endl;
		mas2.dessine();
	}
	
	/** Situation 3**/
	cout << "Situation de départ 3 :" << endl << endl;
	
	Vecteur3D position3(0.0, 0.0, 0.0);
	Vecteur3D vitesse3(0.0, 0.0, 0.0);
	Masse mas3(&ecran, 1, position3, vitesse3, 1);
	
	Tissu tissu3(&ecran, {&mas3});
	
	Systeme syst3(&ecran, &inte);
	syst3.add_Tissu(&tissu3);
	
	cout << "Au départ :" << endl;
	mas3.dessine();
	
	for(int i(1); i < 68; i++)
	{
		syst3.evolue(t, i * t);
		cout << endl << "Après " << i << " pas de calcul :" << endl;
		mas3.dessine();
	}
	
	
	return 0;
}

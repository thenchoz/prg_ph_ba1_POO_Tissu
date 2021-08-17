#include <iostream>
#include "../general/Systeme.h"
#include "../text/TextView.h"

using namespace std;

int main()
{
	double t(0.1);
	IntegrateurEulerCromer inte;
	//Integrateur Newmark inte;
	//Integrateur RungKutta inte;
	TextView ecran(cout);

	
	/** Situation 1 Impulsion Sinus de gauche vers la droite **/
	
	Vecteur3D position1;
	Vecteur3D vitesse1;
	
	Vecteur3D force(0.0, 0.0, 9.81);
	Vecteur3D pos(0.0, 0.0, -5.0);
	
	Masse mas1(&ecran, 1, position1, vitesse1, 0);
	
	Tissu tissu(&ecran, {&mas1});	

	ImpulsionsSinus imp(pos, 10, {&tissu}, force, 0.3, 1.0, 10);
	
	Systeme syst(&ecran, &inte);
	syst.add_Tissu(&tissu);
	syst.add_Contrainte(&imp);
	
	cout << "Au départ :" << endl;
	mas1.dessine();
	
	for(int i(1); i < 20; i++)
	{
		syst.evolue(t, i * t);
		cout << endl << "Après " << i << " pas de calcul :" << endl;
		mas1.dessine();
	}
	
	return 0;
}

#include <iostream>
#include "../general/Systeme.h"
#include "../text/TextView.h"

using namespace std;

int main()
{
	double t(0.01);
	IntegrateurEulerCromer inte;
	//Integrateur Newmark inte;
	//Integrateur RungKutta inte;
	TextView ecran(cout);

	
	//Situation 1 P13.4.b
	cout << "Situation de départ 1 :" << endl << endl;
	
	Vecteur3D nul(0,0,0);
	Vecteur3D largeur(3,0,0);
	Vecteur3D longueur(0,3,0);
	Vecteur3D f(0,0,30);
	
	TissuRectangle tissu(&ecran, largeur, longueur, nul, 0.3125, 0.3, 1, 1, 1);	

	Crochets crochet1(nul,0.1);
	Crochets crochet2(longueur, 0.1);

	ImpulsionsSinus imp1(largeur, 0.5, {&tissu}, f, 0, 2, 1.5);
	ImpulsionsSinus imp2(largeur + longueur, 0.5, {&tissu}, f, 0, 2, 1.5);
	
	
	Systeme syst(&ecran, &inte);
	syst.add_Tissu(&tissu);
	syst.add_Contrainte(&crochet1);
	syst.add_Contrainte(&crochet2);
	syst.add_Contrainte(&imp1);
	syst.add_Contrainte(&imp2);
	
	cout << "Au départ :" << endl;
	syst.dessine();
	
	for(int i(1); i < 20; i++)
	{
		syst.evolue(t, i * t);
		cout << endl << "# position : au temps " << i * t << endl;
		syst.dessine();
	}
	
	return 0;
}

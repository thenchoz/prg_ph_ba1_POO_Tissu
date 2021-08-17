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
	
	/** Situation 1, masse accroché à un crochet **/
	
	Vecteur3D position1(0.0, 0.0, 1.0);
	Vecteur3D vitesse1(1.0, 0.0, 2.0);
	Masse* mas1 = new Masse(&ecran, 0.127, position1, vitesse1);
	
	Tissu* tissu1 = new Tissu(&ecran, {mas1});
	
	Crochets* crochet1 = new Crochets(position1, 0.1);
	
	Systeme syst(&ecran, &inte);
	syst.add_Tissu(tissu1);
	syst.add_Contrainte(crochet1);
	
	
	cout << "Au départ :" << endl;
	mas1->dessine();
	
	for(int i(1); i < 3; i++)
	{
		syst.evolue(t, i * t);
		cout << "Après " << i << " pas de calcul :" << endl;
		mas1->dessine();
	}
	
	delete mas1;
	delete tissu1;
	delete crochet1;
	
	mas1 = nullptr;
	tissu1 = nullptr;
	crochet1 = nullptr;
	
	
	cout << endl << "==================================================================================================================" << endl << endl;
	
	/** Situation 2, masse qui tombe en chute libre et s'accroche **/
	
	cout << "Situation de départ 2 :" << endl << endl;
	
	Vecteur3D position2;
	Vecteur3D vitesse2;
	Masse* mas2 = new Masse(&ecran, 10, position2, vitesse2);
	
	Tissu* tissu2 = new Tissu(&ecran, {mas2});
	
	Vecteur3D pos2(0.0, 0.0, -5);
	Crochets* crochet2 = new Crochets(pos2, 0.4);
	
	Systeme syst2(&ecran, &inte);
	syst2.add_Tissu(tissu2);
	syst2.add_Contrainte(crochet2);
	
	cout << "Au départ :" << endl;
	mas2->dessine();
	
	for(int i(1); i < 20; i++)
	{
		syst2.evolue(t, i * t);
		cout << "Après " << i << " pas de calcul :" << endl;
		mas2->dessine();
	}
	
	delete mas2;
	delete tissu2;
	delete crochet2;
	
	mas2 = nullptr;
	tissu2 = nullptr;
	crochet2 = nullptr;
	
	cout << endl << "==================================================================================================================" << endl << endl;
	
	/** Situation 3, 3 masse accroché à deux crcohets **/
	
	Vecteur3D nul;
	Vecteur3D posi2(0.0, 1.0, 0.0);
	Vecteur3D posi3(0.0, 2.0, 0.0);
	
	TissuChaine* tissu3 = new TissuChaine(&ecran, {nul, posi2, posi3}, 1, 0.3, 1, 1.2);
	
	Crochets* crochet3 = new Crochets(nul, 0.1);
	Crochets* crochet4 = new Crochets(posi3, 0.1);
	
	Systeme syst3(&ecran, &inte);
	syst3.add_Tissu(tissu3);
	syst3.add_Contrainte(crochet3);
	syst3.add_Contrainte(crochet4);
	
	cout << "Au départ :" << endl;
	syst3.dessine();
	
	for(int i(1); i < 10; i++)
	{
		syst3.evolue(t, i * t);
		cout << "Après " << i << " pas de calcul :" << endl;
		syst3.dessine();
	}
	
	delete tissu3;
	delete crochet3;
	delete crochet4;
	
	tissu3 = nullptr;
	crochet3 = nullptr;
	crochet4 = nullptr;
	
	
	return 0;
}

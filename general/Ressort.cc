#include <iostream>
#include "Ressort.h"
#include "Masse.h"

using namespace std;

/** class ressort  **/

	//constructeur
	Ressort::Ressort(SupportADessin* const& support, double k, double l0,  Masse* const& m1, Masse* const& m2)
	:Dessinable(support), k(k), L0(l0), masse1(m1), masse2(m2)
	{
		m1->ajouter_ressort(this);
		m2->ajouter_ressort(this);
	}
	//Destructeur
	Ressort::~Ressort() {}
	
	
	//modificateurs
	
	//accesseurs
	double Ressort::get_k() const {return k;}
	double Ressort::get_L0() const {return L0;}
	Masse* Ressort::get_m1() const {return masse1;}
	Masse* Ressort::get_m2() const {return masse2;}
	
	//méthodes
	Vecteur3D Ressort::vecteur_ressort() const
	{
		return (masse2->get_position()) - (masse1->get_position());
	}
	Vecteur3D Ressort::force_rappel(Masse* m) const
	{
		Vecteur3D force(k*(vecteur_ressort().norm() - L0) / vecteur_ressort().norm() * vecteur_ressort());
		
		// k * (||distance entre les masses|| - L0) * vecteur unitaire (dans le bon sens, d'où le if)
		if(m == masse2)
		{
			force = -1 * force;
		}
		
		return force;
	}
	void Ressort::dessine()
	{
		support->dessine(*this);
	}

/** fin class ressort  **/

ostream& operator<<(ostream& sortie, Ressort const& r)
{
	sortie 	<< "Ressort " 	<< &r << " : " 				<< endl
			<< r.get_k() 	<< " # cst raideur" 		<< endl
			<< r.get_L0() 	<< " # longueur au repos" 	<< endl
			
			<< "# masse depart : Masse "			<< r.get_m1() 	<< " : " << endl
			<< *r.get_m1();
			
	sortie	<< "# masse arrivee : Masse " 			<< r.get_m2() 	<< " : " << endl
			<< *r.get_m2();
	return sortie;
}

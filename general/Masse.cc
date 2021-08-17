#include <iostream>
#include "Masse.h"
#include <cmath>


using namespace std;


const Vecteur3D Masse::gravite = Vecteur3D(0.0, 0.0, -9.81);


/** class masse **/


	//constructeurs
	Masse::Masse(SupportADessin* const& s, double mas, Vecteur3D const& pos, Vecteur3D const& vit, double l)
	:Dessinable(s), masse(abs(mas)), coeff_lambda(l), position(pos), vitesse(vit), force(masse * gravite) {}
	
	
	//modificateurs, pour la force soit par copie, soit nouveau vecteur
	void Masse::set_position(double x,double y, double z)
	{
		position.set_coord(x, y, z); 		
	}
	void Masse::set_position(Vecteur3D const& p)
	{
		position = p;
	}
	void Masse::set_vitesse(double x,double y, double z)
	{
		vitesse.set_coord(x, y, z); 		
	}
	void Masse::set_vitesse(Vecteur3D const& v)
	{
		vitesse = v;
	}
	void Masse::set_force(Vecteur3D const& f)
	{
		force = f;
	}
	void Masse::ajouter_ressort(Ressort* const& r)
	{
		ressorts.push_back(r);
	}
	
	//accesseurs
	double Masse::get_masse() 		const {return masse;}
	double Masse::get_lambda() 		const {return coeff_lambda;}
	Vecteur3D Masse::get_position() const {return position;}
	Vecteur3D Masse::get_vitesse() 	const {return vitesse;}
	Vecteur3D Masse::get_force() 	const {return force;}
	vector<Ressort*> Masse::get_ressorts() const {return ressorts;}

	//méthodes
	Vecteur3D Masse::acceleration() const
	{
		Vecteur3D acc((1 / masse) * force);
		return acc;
	}
	void Masse::ajoute_force(Vecteur3D const& df)
	{
		force += df;
	}
	void Masse::mise_a_jour_forces()
	{
		// gravité + frottement;
		force = (masse * gravite) - (coeff_lambda * vitesse);
		
		// forces de rappel des ressorts
		for(auto const& res : ressorts)
		{
			force += res->force_rappel(this);
		}
		
		// si force insignifiant, on la met à zéro
		if(force.norm() < 0.01) force = Vecteur3D();
		
	}
	void Masse::vider_ressorts()
	{
		ressorts = {};
	}
	bool Masse::possede_ressort(Ressort* const& r) const
	{
		for(auto const& res : ressorts)
		{
			if(res == r) return true;
		}
		return false;
	}
	void Masse::dessine()
	{
		support->dessine(*this);
	}
	
	//méthode utilisée pour les intégrateur Newmark et Runge-Kutta 
	Vecteur3D Masse::f(Vecteur3D const& x, Vecteur3D const& v)
	{
		Vecteur3D nul;
		if(vitesse == nul && force == nul)
		{
			return nul;
		}
		
		Vecteur3D rappel_1;
		for(auto const& res : ressorts)
		{
			rappel_1 += res->force_rappel(this);
		}
		
		Vecteur3D pos(position);
		set_position(x);
		
		Vecteur3D rappel_2;
		for(auto const& res : ressorts)
		{
			rappel_2 += res->force_rappel(this);
		}
		
		set_position(pos);
			
		return force - rappel_1 + rappel_2 + coeff_lambda * (vitesse - v);			
	}


/** fin class masse**/


//opérateur
ostream& operator<<(ostream& sortie, Masse const& m)
{
	sortie << "affichage de la masse : " 	<< &m << endl
		<< m.get_masse() << " # masse" 		<< endl
		<< m.get_lambda() << " # lambda" 	<< endl
		<< m.get_position().getX() 	<< ' ' 	<< m.get_position().getY()  << ' ' << m.get_position().getZ()	<< " # position" << endl
		<< m.get_vitesse().getX() 	<< ' ' 	<< m.get_vitesse().getY()  	<< ' ' << m.get_vitesse().getZ() 	<< " # vitesse" << endl
		<< m.get_force().getX() 	<< ' ' 	<< m.get_force().getY()  	<< ' ' << m.get_force().getZ()		<< " # force" << endl
		<< m.get_ressorts().size() <<  " ressorts" << endl;
		
	for(auto  const& res : m.get_ressorts())
	{
		sortie << res << endl;
	}
	
	return sortie;
}

#define  _USE_MATH_DEFINES
#include <iostream>
#include "Contraintes.h"
#include <math.h>

using namespace std;


/** class Contraintes **/

	//constructeur
	Contraintes::Contraintes(Vecteur3D const& p, double r)
	: pos(p), rayon(r) {}
	
	
	//méthode
	//Est-elle dans la zone d'application
	bool Contraintes::est_concerne(Masse* const& m) const
	{
		Vecteur3D dist(m->get_position() - pos);
		if(dist.norm() <= rayon)
		{
			return true;
		}
		return false;
	}
	

/** fin class Contraintes **/


/** class Crochets **/

	//constructeur
	Crochets::Crochets(Vecteur3D const& position, double rayon)
	: Contraintes(position, rayon) {}
	
	
	//méthode
	void Crochets::appliquer(Tissu* const& tissu, double dt) const
	{
		for(auto const& mas : tissu->get_masses())
		{
			Vecteur3D nul;
			
			if(est_concerne(mas))
			{
				mas->set_force(nul);
				mas->set_vitesse(nul);
			}
		}
	}
	

/** fin class Crochets **/


/** class Impulsions **/

	//constructeur
	Impulsions::Impulsions(Vecteur3D const& position, double rayon, vector<Tissu*> const& tissus, Vecteur3D const& impulsion, double temps0, double temps1)
	: Contraintes(position, rayon), impulsion(impulsion)
	{
		if(temps1 < temps0)
		{
			t0 = temps1;
			t1 = temps0;
		}
		else
		{
			t0 = temps0;
			t1 = temps1;
		}
		
		for(auto const& t : tissus)
		{
			for(auto const& mas : t->get_masses())
			{
				if(est_concerne(mas))
				{
					masses.push_back(mas);
				}
			}
		}		
	}
	
	
	//méthode
	void Impulsions::appliquer(Tissu* const& tissu, double t) const
	{
		// si le temps est dans l'intervalle
		if((t > t0) && (t < t1))
		{
			Vecteur3D gravite(0.0, 0.0, -9.81);
			
			for(auto const& mas : masses)
			{
				mas->set_force(mas->get_force() - mas->get_masse() * gravite + impulsion);
			}
		}
	}


/** fin class Impulsions **/


/** class ImpulsionsSinus **/
	
	//constructeur
	ImpulsionsSinus::ImpulsionsSinus(Vecteur3D const& position, double rayon, vector<Tissu*> const& tissus, Vecteur3D const& impulsion, double temps0, double temps1, double f)
	: Impulsions(position, rayon, tissus, impulsion, temps0, temps1), frequence(f) {}
	
	
	//méthodes
	void ImpulsionsSinus::appliquer(Tissu* const& tissu, double t) const
	{
		// si le temps est dans l'intervalle
		if((t > t0) && (t < t1))
		{
			Impulsions::appliquer(tissu, t);
			
			for(auto const& mas : masses)
			{
				mas->set_force(mas->get_force() - impulsion + sin(2 * M_PI * frequence * (t - t0)) * impulsion);
			}
		}
	}


/** fin class ImpulsionsSinus **/

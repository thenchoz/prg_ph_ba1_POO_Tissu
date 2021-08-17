#include <iostream>
#include "Systeme.h"

using namespace std;

/** class Systeme **/

	//constructeur
	Systeme::Systeme(SupportADessin* const& s, Integrateur* const& type)
	: Dessinable(s), type(type) {}
	
	
	//modificateurs
	void Systeme::add_Tissu(Tissu* const& t)
	{
		tissu.push_back(t);
	}
	void Systeme::add_Contrainte(Contraintes* const& c)
	{
		contrainte.push_back(c);
	}
	void Systeme::change_Integrateur(Integrateur* const& i)
	{
		type = i;
	}
	
	//accesseur
	vector<Tissu*> Systeme::get_Tissu() const
	{
		return tissu;
	}
	vector<Contraintes*> Systeme::get_Contrainte() const
	{
		return contrainte;
	}
	
	//méthodes
	void Systeme::dessine()
	{
		support->dessine(*this);
	}
	void Systeme::evolue(double dt, double temps) const
	{
		for(auto const& t : tissu)
		{
			t->mise_a_jour_force();
		}
		
		for(auto const& t : tissu)
		{
			for(auto const& c : contrainte)
			{
				c->appliquer(t, temps);
			}
		}
		
		for(auto const& t : tissu)
		{
			t->evolue(type, dt);
		}
	}
	

/** fin class Systeme **/

ostream& operator<<(ostream& sortie, Systeme const& s)
{
	for(auto const& t : s.get_Tissu())
	{
		sortie << *t;
	}
	return sortie;
}

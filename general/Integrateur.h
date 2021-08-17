#ifndef INTEGRATEUR_H
#define INTEGRATEUR_H

#include "Masse.h"
#include "Vecteur3D.h"

//class Integrateur
class Integrateur
{
	
	public:
	//consructeur
	Integrateur() {};
	//destructeur
	virtual ~Integrateur() {};
	//copie		supprimer, car on ne veut pas avoir deux fois la même intégration, par contre on garde l'operator = pour pouvoir le modifier
	Integrateur(Integrateur const& i) = delete;
	
	
	//modificateurs
	
	//accesseur
	
	//méthodes
	virtual void evolue(Masse* const& m, double dt) const = 0;
};

//sous-class integrateur d'Euler-Cromer
class IntegrateurEulerCromer: public Integrateur
{
	public:
	//constructeur
	IntegrateurEulerCromer() {};
	//destructeur
	~IntegrateurEulerCromer() {};
	//copie		supprimer, car on ne veut pas avoir deux fois la même intégration
	IntegrateurEulerCromer(Integrateur const& i) = delete;
	
	
	//méthodes
	void evolue(Masse* const& m, double dt) const override;
};


//sous-class intégrateur Newmark
class IntegrateurNewmark: public Integrateur
{
	public:
	//constructeur
	IntegrateurNewmark() {};
	//destructeur
	~IntegrateurNewmark() {};
	//copie		supprimer, car on ne veut pas avoir deux fois la même intégration
	IntegrateurNewmark(Integrateur const& i) = delete;
	
	
	//méthodes
	void evolue(Masse* const& m, double dt) const override;
};



//sous-class intégrateur Runge Kutta
class IntegrateurRungeKutta: public Integrateur
{
	public:
	//constructeur
	IntegrateurRungeKutta() {};
	//destructeur
	~IntegrateurRungeKutta() {};
	//copie		supprimer, car on ne veut pas avoir deux fois la même intégration
	IntegrateurRungeKutta(Integrateur const& i) = delete;
	
	
	//méthodes
	void evolue(Masse* const& m, double dt) const override;
};

#endif // INTEGRATEUR_H

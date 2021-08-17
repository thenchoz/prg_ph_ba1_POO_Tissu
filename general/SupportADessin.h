#ifndef SUPPORTADESSIN_H
#define SUPPORTADESSIN_H

//#include "Tissu.h"
//#include "Systeme.h"
//#include "Masse.h"
//#include "Ressort.h"

class Tissu;
class Systeme;
class Masse;
class Ressort;

// class SupportADessin
class SupportADessin
{
	public:
	//consructeur
	SupportADessin() {};
	//destructeur
	virtual ~SupportADessin() {};
	//copie		supprimer, car on ne veut pas avoir deux fois le même support
	SupportADessin(SupportADessin const& d) = delete;
	SupportADessin& operator=(SupportADessin const& d) = delete;
	
	
	//modificateurs
	
	//accesseur
	
	//méthodes
	virtual void dessine(Tissu const& t) = 0;
	virtual void dessine(Systeme const& s) = 0;
	virtual void dessine(Masse const& m) = 0;
	virtual void dessine(Ressort const& r) = 0;
};

#endif // SUPPORTADESSIN_H

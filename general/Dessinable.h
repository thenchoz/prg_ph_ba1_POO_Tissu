#ifndef DESSINABLE_H
#define DESSINABLE_H

#include "SupportADessin.h"

//class Dessinable
class Dessinable
{
	public:
	//consructeur
	Dessinable(SupportADessin* const& s)
	:support(s) {};
	//destructeur
	virtual ~Dessinable() {};
	//copie		supprimer, car on ne veut pas avoir deux fois le même dessin
	Dessinable(Dessinable const& d) = delete;
	Dessinable& operator=(Dessinable const& d) = delete;
	
	
	//modificateurs
	
	//accesseur
	SupportADessin* get_support() const {return support;}
	
	//méthodes
	virtual void dessine() = 0;
	
	
	protected:
	SupportADessin* support;
};

#endif // DESSINABLE_H

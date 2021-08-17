#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include <iostream>
#include "../general/SupportADessin.h"

class Tissu;
class Systeme;
class Masse;

class TextView : public SupportADessin
{
	public:
	//consructeur
	TextView(std::ostream& flot);
	//destructeur
	virtual ~TextView() {};
	//copie		supprimer, car on ne veut pas avoir deux fois le même support
	TextView(TextView const& d) = delete;
	TextView& operator=(TextView const& d) = delete;
	
	
	//modificateurs
	
	//accesseur
	
	//méthodes
	virtual void dessine(Tissu const& t) override;
	virtual void dessine(Systeme const& s) override;
	virtual void dessine(Masse const& m) override;
	virtual void dessine(Ressort const& r) override;
	
	
	private:
	std::ostream& flot;
};

#endif // TEXTVIEW_H

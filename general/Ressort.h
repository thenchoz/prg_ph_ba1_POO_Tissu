#ifndef RESSORT_H
#define RESSORT_H

//#include "Masse.h"
#include "Vecteur3D.h"
#include "Dessinable.h"

class Masse;

//class Ressort
class Ressort : public Dessinable
{
	public:
	//constructeur
	Ressort(SupportADessin* const& support, double k, double l0,  Masse* const& m1, Masse* const& m2);
	//destructeur
	virtual ~Ressort() override;
	//copie		supprimer, car on ne veut pas avoir deux fois le même ressort au même endroit
	Ressort(Ressort const& r) = delete;
	Ressort& operator=(Ressort const& r) = delete;
	
	
	//modificateurs
	
	//accesseurs
	double get_k() const;
	double get_L0() const;
	Masse* get_m1() const;
	Masse* get_m2() const;
	
	//méthodes
	Vecteur3D vecteur_ressort() const;
	Vecteur3D force_rappel(Masse* m) const;
	virtual void dessine() override;
	
	
	private:
	const double k;
	const double L0;
	Masse* masse1;
	Masse* masse2;
};

std::ostream& operator<<(std::ostream& sortie, Ressort const& r);

#endif // RESSORT_H

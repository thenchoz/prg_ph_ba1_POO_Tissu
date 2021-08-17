#ifndef MASSE_H
#define MASSE_H

#include "Ressort.h"
#include "Vecteur3D.h"
#include "Dessinable.h"
#include <vector>

//class Masse
class Masse : public Dessinable
{
	public:
	//constructeurs
	Masse(SupportADessin* const& s, double mas, Vecteur3D const& pos = Vecteur3D(), Vecteur3D const& vit = Vecteur3D(), double l = 0);
	//destructeur
	virtual ~Masse() override {};
	//copie		supprimer, car on ne veut pas avoir deux fois la même masse au même endroit
	Masse(Masse const& m) = delete;
	Masse& operator=(Masse const& m) = delete;
	
	//modificateurs, pour la force soit par copie, soit nouveau vecteur
	void set_position(double x, double y, double z);
	void set_position(Vecteur3D const& p);
	void set_vitesse(double x, double y, double z);
	void set_vitesse(Vecteur3D const& v);
	void set_force(Vecteur3D const& f);
	void ajouter_ressort(Ressort* const& r);
	
	//accesseurs
	double get_masse() const;
	double get_lambda() const;
	Vecteur3D get_position() const;
	Vecteur3D get_vitesse() const;
	Vecteur3D get_force() const;
	std::vector<Ressort*> get_ressorts() const;
	
	//méthodes
	Vecteur3D acceleration() const;
	void ajoute_force(Vecteur3D const& df);
	void mise_a_jour_forces();
	void vider_ressorts();
	bool possede_ressort(Ressort* const& r) const;
	Vecteur3D f(Vecteur3D const& x, Vecteur3D const& v);
	virtual void dessine() override;
	
	
	private:
	const double masse;
	const double coeff_lambda;
	Vecteur3D position;
	Vecteur3D vitesse;
	Vecteur3D force;
	std::vector<Ressort*> ressorts;
	// vecteurs de gravité, plusieurs fois utilisés
	static const Vecteur3D gravite;
};


//opérateur
std::ostream& operator<<(std::ostream& sortie, Masse const& m);

#endif // MASSE_H

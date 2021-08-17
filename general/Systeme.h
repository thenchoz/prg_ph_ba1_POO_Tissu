#ifndef SYSTEME_H
#define SYSTEME_H

#include "Tissu.h"
#include "Contraintes.h"
#include "Dessinable.h"
#include <vector>

//class Systeme
class Systeme : public Dessinable
{
	public:
	//constructeur
	Systeme(SupportADessin* const& s, Integrateur* const& inte = nullptr);
	//destructeur
	virtual ~Systeme() override {};
	//copie		supprimer, car on ne veut pas avoir deux fois le même système
	Systeme(Systeme const& s) = delete;
	Systeme& operator=(Systeme const& s) = delete;
	
	
	//modificateurs
	void add_Tissu(Tissu* const& t);
	void add_Contrainte(Contraintes* const& c);
	void change_Integrateur(Integrateur* const& i);
	
	//accesseur
	std::vector<Tissu*> get_Tissu() const;
	std::vector<Contraintes*> get_Contrainte() const;
	
	//méthodes
	virtual void dessine() override;
	void evolue(double dt, double temps) const;
	
	
	private:
	std::vector<Tissu*> tissu;
	std::vector<Contraintes*> contrainte;
	Integrateur* type;
};

std::ostream& operator<<(std::ostream& sortie, Systeme const& s);

#endif // SYSTEME_H

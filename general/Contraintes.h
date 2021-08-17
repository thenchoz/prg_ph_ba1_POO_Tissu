#ifndef CONTRAINTES_H
#define CONTRAINTES_H

#include "Vecteur3D.h"
#include "Masse.h"
#include "Tissu.h"
#include <vector>

//class Contraintes
class Contraintes
{
	public:
	//constructeur
	Contraintes(Vecteur3D const& position, double rayon);
	//destructeur
	virtual ~Contraintes() {};
	// suppression copie
	Contraintes(Contraintes const& t) = delete;
	Contraintes& operator=(Contraintes const& t) = delete;
	
	
	//méthodes
	virtual void appliquer(Tissu* const& tissu, double temps) const = 0;
	bool est_concerne(Masse* const& m) const;
	
	
	private:
	const Vecteur3D pos;
	const double rayon;
};


//class Crochets
class Crochets: public Contraintes
{
	public:
	//constructeur
	Crochets(Vecteur3D const& position, double rayon);
	//destructeur
	virtual ~Crochets() override {};
	// suppression copie
	Crochets(Crochets const& t) = delete;
	Crochets& operator=(Crochets const& t) = delete;
	
	
	//Méthodes
	virtual void appliquer(Tissu* const& tissu, double temps) const override;
};


//class Impulsions
class Impulsions: public Contraintes
{
	public:
	//constructeur
	Impulsions(Vecteur3D const& position, double rayon, std::vector<Tissu*> const& tissus, Vecteur3D const& impulsion, double temps0, double temps1);
	//destructeur
	virtual ~Impulsions() override {};
	// suppression copie
	Impulsions(Impulsions const& t) = delete;
	Impulsions& operator=(Impulsions const& t) = delete;
	
	
	//Méthodes
	virtual void appliquer(Tissu* const& tissu, double temps) const override;
	
	
	protected:
	double t0;
	double t1;
	const Vecteur3D impulsion;
	std::vector<Masse*> masses;
};


//class ImpulsionsSinus
class ImpulsionsSinus: public Impulsions
{
	public:
	//constructeur
	ImpulsionsSinus(Vecteur3D const& position, double rayon, std::vector<Tissu*> const& tissus, Vecteur3D const& impulsion, double temps0, double temps1, double frequence);
	//destructeur
	virtual ~ImpulsionsSinus() override {};
	// suppression copie
	ImpulsionsSinus(ImpulsionsSinus const& t) = delete;
	ImpulsionsSinus& operator=(ImpulsionsSinus const& t) = delete;
	
	
	//Méthodes
	virtual void appliquer(Tissu* const& tissu, double temps) const override;
	
	private:
	const double frequence;
};


#endif //CONTRAINTES_H

#ifndef TISSU_H
#define TISSU_H

#include "Integrateur.h"
#include "Dessinable.h"
#include "Vecteur3D.h"
#include <vector>

//class Tissu
class Tissu : public Dessinable
{
	public:
	//constructeur
	Tissu(SupportADessin* const& s, std::vector<Masse*> const& m = {});
	//destructeur
	virtual ~Tissu() override;
	//copie à supprimer
	Tissu(Tissu const& t) = delete;
	Tissu& operator=(Tissu const& t) = delete;
	
	
	//modificateurs
	
	//accesseurs
	std::vector<Masse*> get_masses() const;
	std::vector<Ressort*> get_ressorts() const;
		
	//méthodes
	void connecte(double k, double L0, Masse* const& m1, Masse* const& m2);
	void connecte_masses() const;
	virtual void deconnecte(Ressort*& r);
	virtual bool check() const;
	void mise_a_jour_force() const;
	void evolue(Integrateur* const& type, double dt) const;
	void dessine() override;
	
	protected:
	std::vector<Masse*> masses;
	
	private:
	std::vector<Ressort*> ressorts;
};


//class TissuChaine
class TissuChaine : public Tissu
{
	public:
	//constructeur
	TissuChaine(SupportADessin* const& support, std::vector<Vecteur3D> const& pos, double masse, double lambda, double k, double L0);
	//destructeur
	virtual ~TissuChaine() override;
	//copie à supprimer
	TissuChaine(TissuChaine const& t) = delete;
	TissuChaine& operator=(TissuChaine const& t) = delete;
};


//class 
class TissuRectangle : public Tissu
{
	public:
	//constructeur
	TissuRectangle(SupportADessin* const& support, Vecteur3D largeur, Vecteur3D const& longueur, Vecteur3D const& pos, double masse, double lambda, double densite, double k, double L0);
	//destructeur
	virtual ~TissuRectangle() override;
	//copie à supprimer
	TissuRectangle(TissuRectangle const& t) = delete;
	TissuRectangle& operator=(TissuRectangle const& t) = delete;
};


//class
class TissuDisque : public Tissu
{
	public:
	//constructeur
	TissuDisque(SupportADessin* const& sup, Vecteur3D const& pos, Vecteur3D const& rayon, double masse, double pas, double lambda, double k, double L0, double angle = 20);
	//destructeur
	virtual ~TissuDisque() override;
	//copie à supprimer
	TissuDisque(TissuDisque const& t) = delete;
	TissuDisque& operator=(TissuDisque const& t) = delete;
};


//class
class TissuComposee : public Tissu
{
	public:
	//constructeur
	TissuComposee(SupportADessin* const& support, std::vector<Tissu*> const& tissus, double e, double k, double L0);
	//destructeur
	virtual ~TissuComposee() override {};
	//copie à supprimer
	TissuComposee(TissuComposee const& t) = delete;
	TissuComposee& operator=(TissuComposee const& t) = delete;
	
	
	//modificateurs
	void add_Tissu(Tissu* const& t);
	
	//accesseurs
	std::vector<Tissu*> get_Tissu() const;
	
	//méthodes
	bool distance(Masse* const& masse1, Masse* const& masse2) const;
	void raccommode();
	virtual void deconnecte(Ressort*& r) override;
	virtual bool check() const override;
	
	
	private:
	std::vector<Tissu*> tissus;
	const double epsilon;
	const double k;
	const double L0;
};

void operator+=(TissuComposee& tissucompo, Tissu& t);
std::ostream& operator<<(std::ostream& sortie, Tissu const& t);

#endif // TISSU_H

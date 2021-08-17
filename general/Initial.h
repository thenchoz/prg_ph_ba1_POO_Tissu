#ifndef INITIAL_H
#define INITIAL_H

#include "Systeme.h"
#include "Integrateur.h"
#include <vector>


class Initial
{
	public:
	//constructeur
	Initial(Systeme* const& systeme);
	//destructeur
	~Initial();
	
	
	//méthodes public
	void modif();
	
	
	
	private:
	//méthodes privées
	void choix_integrateur();
	
	void creation_Tissu();
	void create_tissu();
	void create_tissuChaine();
	void create_tissuRectangle();
	void create_tissuDisque();
	void create_tissuCompose();
	void add_Tissu(Tissu* const& t);
	
	void creation_contrainte();
	void create_crochet();
	void create_impul();
	void create_impulsin();
	void add_Contrainte(Contraintes* const& c);
	
	void modification();
	void raccommode();
	
	
	Systeme* syst;
	Integrateur* inte;
	SupportADessin* sup;
	std::vector<Contraintes*> contrainte;
	std::vector<Tissu*> tissus;
	std::vector<TissuComposee*> possede;
};

#endif // INITIAL_H

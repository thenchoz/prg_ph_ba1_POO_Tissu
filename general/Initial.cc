#include <iostream>
#include "Initial.h"
#include <vector>
#include <limits>
#include <array>

using namespace std;

//fonctions pour verifier les entrées
	
//nettoyer cin
void nettoyer()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//Demander un entier strictement positif
int demander_size_t(bool strict = true)
{
	int i;
	if(cin >> i)
	{
		if(strict)
		{
			if(i > 0)
			{
				return i;
			}
			else
			{
				cout << "On souhaite un entier strictement positif :" << endl;
				return demander_size_t();
			}
		}
		else
		{
			if(i >= 0)
			{
				return i;
			}
			else
			{
				cout << "On souhaite un entier positif :" << endl;
				return demander_size_t();
			}
		}
	}
	else
	{
		nettoyer();
		cout << "On souhaite un entier strictement positif :" << endl;
		return demander_size_t();
	}
}

//Demander un réel positif (strictement)
double demander_positif(bool strict = false)
{
	double i;
	
	if(!(cin >> i))
	{
		nettoyer();
		cout << "On souhaite un nombre réel positif:" << endl;
		return demander_positif(strict);
	}
	else
	{
		if(strict && i > 0)
		{
			return i;
		}
		else if(!strict && i >= 0)
		{
			return i;
		}
		else
		{
			cout << "On souhaite un nombre réel positif";
			if(strict)
			{
				cout << " (strictement)";
			}
			cout << " :" << endl;
			return demander_positif(strict);
		}
	}	
}

//Demander un entier positif plus petit que max
int demander_nb(int max)
{
	int i;
	if(cin >> i)
	{
		if(i >= 1 && i <= max)
		{
			return i;
		}
		else
		{
			cout << "On souhaite un entier compris entre 1 et " << max << " :" << endl;
			return demander_nb(max);	
		}
	}
	else
	{
		nettoyer();
		cout << "On souhaite un entier compris entre 1 et " << max << " :" << endl;
		return demander_nb(max);
	}
}

//Demander un Vecteur3D
Vecteur3D demander_vecteur()
{
	double x, y, z;
	if(cin >> x >> y >> z)
	{
		return Vecteur3D(x, y, z);
	}
	else
	{
		nettoyer();
		cout << "On souhaite trois réels :" << endl;
		return demander_vecteur();
	}
}


/** class Initial **/

	//constructeur
	Initial::Initial(Systeme* const& systeme)
	: syst(systeme), inte(nullptr), sup(nullptr)
	{
		sup = syst->get_support();
		
		choix_integrateur();
		creation_Tissu();
		creation_contrainte();
	}
	//destructeur
	Initial::~Initial()
	{
		delete inte;
		inte = nullptr;
		
		for(auto & c : contrainte)
		{
			delete c;
			c = nullptr;
		}
		
		for(auto & t : tissus)
		{
			delete t;
			t = nullptr;
		}
	}
	
	
	//méthodes
	//Integrateur ==========================================================================================================================================
	void Initial::choix_integrateur()
	{
		cout << "Veuillez choisir un intégrateur (1 Euler-Cromer, 2 NewMark, 3 Runge-Kutta) :" << endl;
		int in(demander_size_t());
		
		switch(in)
		{
			case 1:
				inte = new IntegrateurEulerCromer();
			break;
			
			case 2:
				inte = new IntegrateurNewmark();
			break;
			
			case 3:
				inte = new IntegrateurRungeKutta();
			break;
			
			default:
				inte = new IntegrateurEulerCromer();
			break;
		}
		syst->change_Integrateur(inte);
	}
	
	
	//Tissu ==========================================================================================================================================
	void Initial::creation_Tissu()
	{
		cout << "Veuillez choisir un type de Tissu (1 Tissu Simple, 2 Tissu Chaîne, 3 Tissu Rectangle, 4 Tissu Disque, 5 Tissu Composé) :" << endl;
		int ti(demander_nb(5));
		
		switch(ti)
		{
			case 1:
				create_tissu();
			break;
			
			case 2:
				create_tissuChaine();
			break;
			
			case 3:
				create_tissuRectangle();
			break;
			
			case 4:
				create_tissuDisque();
			break;
			
			case 5:
				create_tissuCompose();
			break;
		}
	}
	
	void Initial::create_tissu()
	{
		cout << "Désolé, ce produit n'est pas disponible pour l'instant." << endl;
		creation_Tissu();
	}
	
	void Initial::create_tissuChaine()
	{
		cout << "Combien de masses souhaiteriez-vous avoir ?" << endl;
		int ma(demander_size_t());
		
		vector<Vecteur3D> pos;
		
		for(int i(1); i <= ma; i++)
		{
			cout << "Veuillez rentrer la position de votre " << i << "e masse :" << endl;
			Vecteur3D position(demander_vecteur());
			
			pos.push_back(position);
		}
		
		cout << "Veuillez rentrer leur masse :" << endl;
		double m(demander_positif(true));
		
		cout << "Ainsi que leur coefficient de frottement :" << endl;
		double l(demander_positif());
		
		cout << "Veuillez rentrer la constante de rappel des ressorts :" << endl;
		double k(demander_positif(true));
		
		cout << "Ainsi que leur longueur au repos :" << endl;
		double L0(demander_positif(true));
		
		add_Tissu(new TissuChaine(sup, pos, m, l, k, L0));
	}
	
	void Initial::create_tissuRectangle()
	{
		cout << "Veuillez rentrer la position de départ :" << endl;
		Vecteur3D position(demander_vecteur());
		
		cout << "Veuillez rentrer un vecteur de largeur :" << endl;
		Vecteur3D largeur(demander_vecteur());
		
		cout << "Veuillez rentrer un vecteur de longueur :" << endl;
		Vecteur3D longueur(demander_vecteur());
		
		cout << "Veuillez rentrer la densité de masse par unité :" << endl;
		double d(demander_positif(true));
		
		cout << "Veuillez rentrer leur masse :" << endl;
		double m(demander_positif(true));
		
		cout << "Ainsi que leur coefficient de frottement :" << endl;
		double l(demander_positif());
		
		cout << "Veuillez rentrer la constante de rappel des ressorts :" << endl;
		double k(demander_positif(true));
		
		cout << "Ainsi que leur longueur au repos :" << endl;
		double L0(demander_positif(true));
		
		add_Tissu(new TissuRectangle(sup, largeur, longueur, position, m, l, d, k, L0));
	}
	
	void Initial::create_tissuDisque()
	{
		cout << "Veuillez rentrer la position de départ :" << endl;
		Vecteur3D position(demander_vecteur());
		
		cout << "Veuillez rentrer un vecteur normal :" << endl;
		Vecteur3D rayon(demander_vecteur());
		
		cout << "Veuillez rentrer le pas :" << endl;
		double p(demander_positif(true));
		
		cout << "Veuillez rentrer leur masse :" << endl;
		double m(demander_positif(true));
		
		cout << "Ainsi que leur coefficient de frottement :" << endl;
		double l(demander_positif());
		
		cout << "Veuillez rentrer la constante de rappel des ressorts :" << endl;
		double k(demander_positif(true));
		
		cout << "Ainsi que leur longueur au repos :" << endl;
		double L0(demander_positif(true));
		
		cout << "Et un angle :" << endl;
		double a(demander_positif(true));
		
		add_Tissu(new TissuDisque(sup, position, rayon, m, p, l, k, L0, a));
	}
	
	void Initial::create_tissuCompose()
	{
		if(tissus.size() >= 2)
		{
			cout << "Veuillez rentrer la distance à partir de laquelle les tissus seront raccommodés :" << endl;
			double e(demander_positif(true));
			
			cout << "Veuillez rentrer la constante de rappel des ressorts :" << endl;
			double k(demander_positif(true));
			
			cout << "Ainsi que leur longueur au repos :" << endl;
			double L0(demander_positif(true));
			
			TissuComposee* t;
			if(tissus.size() == 2)
			{
				t = new TissuComposee(sup, tissus, e, k, L0);
			}
			else
			{
				cout << "Combien de tissus souhaitez-vous raccommoder ?" << endl;
				int nb(demander_size_t());
				
				vector<Tissu*> tis;
				for(int i(0); i < nb; i++)
				{
					cout << "Veuillez renter le " << i << "e tissu à devoir être racommodé :" << endl;
					int pos(demander_nb(tissus.size()));
					
					tis.push_back(tissus[pos - 1]);
				}
				
				t = new TissuComposee(sup, tis, e, k, L0);
			}
			possede.push_back(t);
			add_Tissu(t);
		}
		else
		{
			cout << "Désolé, ce produit n'est pas disponible pour l'instant, vous n'avez pas assez de tissu créé." << endl;
			creation_Tissu();
		}
	}
	
	void Initial::add_Tissu(Tissu* const& t)
	{
		tissus.push_back(t);
		syst->add_Tissu(t);
	}
	
	
	//Contraintes ==========================================================================================================================================
	void Initial::creation_contrainte()
	{
		cout << "Combien de contrainte souhaiteriez-vous ajouter ?" << endl;
		int nb(demander_size_t());
		
		for(int i(1); i <= nb; i++)
		{
			cout << "Veuillez rentrer le type de votre " << i << "e contrainte (1 Crochets, 2 Impulsions, 3 Impulsions Sinus) :" << endl;
			int co(demander_size_t());
			
			switch(co)
			{
				case 1:
					create_crochet();
				break;
				
				case 2:
					create_impul();
				break;
				
				case 3:
					create_impulsin();
				break;
				
				default:
					create_crochet();
				break;
			}
		}
	}
	
	void Initial::create_crochet()
	{
		cout << "Veuillez rentrer la position de votre crochet :" << endl;
		Vecteur3D position(demander_vecteur());
		
		cout << "Ainsi que son rayon :" << endl;
		double r(demander_positif(true));
		
		add_Contrainte(new Crochets(position, r));
	}
	
	void Initial::create_impul()
	{
		cout << "Veuillez rentrer la position de votre impulsion :" << endl;
		Vecteur3D position(demander_vecteur());
		
		cout << "Ainsi que l'impulsion :" << endl;
		Vecteur3D impulsion(demander_vecteur());
		
		cout << "Et son rayon :" << endl;
		double r(demander_positif(true));
		
		cout << "Ainsi que le temps de départ :" << endl;
		double t0(demander_positif());
		
		cout << "Et d'arrêt :" << endl;
		double t1(demander_positif(true));
		
		add_Contrainte(new Impulsions(position, r, tissus, impulsion, t0, t1));
	}
	
	void Initial::create_impulsin()
	{
		cout << "Veuillez rentrer la position de votre impulsion :" << endl;
		Vecteur3D position(demander_vecteur());
		
		cout << "Ainsi que l'impulsion :" << endl;
		Vecteur3D impulsion(demander_vecteur());
		
		cout << "Et son rayon :" << endl;
		double r(demander_positif(true));
		
		cout << "Ainsi que le temps de départ :" << endl;
		double t0(demander_positif());
		
		cout << "Et d'arrêt :" << endl;
		double t1(demander_positif(true));
		
		cout << "Et pour finir sa fréquence :" << endl;
		double f(demander_positif(true));
		
		add_Contrainte(new ImpulsionsSinus(position, r, tissus, impulsion, t0, t1, f));
	}
	
	void Initial::add_Contrainte(Contraintes* const& c)
	{
		contrainte.push_back(c);
		syst->add_Contrainte(c);
	}
	
	
	//Modification ==========================================================================================================================================
	void Initial::modif()
	{
		char si;
		cout << "Souhaiteriez-vous faire une modification de votre système (y or n)?" << endl;
		if(cin >> si)
		{
			if(si == 'y')
			{
				modification();
			}
		}
		else
		{
			nettoyer();
			modif();
		}
	}
	
	void Initial::modification()
	{
		cout << "Que souhaiteriez-vous modifier (1 ajouter un tissu, 2 changer d'intégrateur, 3 raccommoder un tissu, 4 ajouter une contrainte) ?" << endl;
		int re(demander_nb(4));
		
		switch(re)
		{
			case 1:
				creation_Tissu();
			break;
			
			case 2:
				choix_integrateur();
			break;
			
			case 3:
				raccommode();
			break;
			
			case 4:
				creation_contrainte();
			break;
		}
		
		modif();
	}
	
	void Initial::raccommode()
	{
		if(possede.size() < 1 && tissus.size() < 2)
		{
			cout << "Désolé, ce produit n'est pas disponible pour l'instant, vous n'avez pas assez de tissu créé." << endl;
		}
		else if(possede.size() < 1)
		{
			create_tissuCompose();
		}
		else if(possede.size() == 1)
		{
			cout << "Quel tissu souhaiteriez-vous ajouter au tissu racommodé ?" << endl;
			int nb(demander_nb(tissus.size()) - 1);
			
			if(tissus[nb] != possede[0])
			{
				bool deja(true);
				for(auto const& t : possede[0]->get_Tissu())
				{
					if(tissus[nb] == t)
					{
						cout << "Ce tissu est déjà raccommodé." << endl;
						deja = false;
					}
				}
				
				if(deja)
				{
					*possede[0] += *tissus[nb];
				}
			}
		}
		else
		{
			cout << "A quel tissu composé souhaiteriez-vous rajouter un tissu ?" << endl;
			int co(demander_nb(possede.size()));
			
			cout << "Quel tissu souhaiteriez-vous ajouter au tissu racommodé ?" << endl;
			int nb(demander_nb(tissus.size()));
			
			if(tissus[nb] != possede[co])
			{
				bool deja(true);
				for(auto const& t : possede[0]->get_Tissu())
				{
					if(tissus[nb] == t)
					{
						cout << "Ce tissu est déjà raccommodé." << endl;
						deja = false;
					}
				}
				
				if(deja)
				{
					*possede[0] += *tissus[nb];
				}
			}
		}
	}
	
/** fin class Initial **/

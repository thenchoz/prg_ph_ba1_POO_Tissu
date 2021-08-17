#define  _USE_MATH_DEFINES
#include <iostream>
#include "Tissu.h"
#include <math.h>


using namespace std;


/** class Tissu**/

	//constructeur
	Tissu::Tissu(SupportADessin* const& s, vector<Masse*> const& m)
	:Dessinable(s), masses(m), ressorts{} {}
	//destructeur
	Tissu::~Tissu()
	{
		for(auto & res : ressorts)
		{
			delete res;
			res = nullptr;
		}
	}

	//modificateurs (pas d'ajouts de masses en cours de route : consigne)

	//accesseurs
	vector<Masse*> Tissu::get_masses() const {return masses;}
	vector<Ressort*> Tissu::get_ressorts() const {return ressorts;}
	
	
	//méthodes
	void Tissu::connecte(double k, double L0, Masse* const& m1, Masse* const& m2)
	{
		Ressort* r = new Ressort(support, k, L0, m1, m2);
		ressorts.push_back(r);
	}

	void Tissu::connecte_masses() const
	{
		for(auto const& m : get_masses())
		{
			m->vider_ressorts();
		}
		
		for(auto const& res : get_ressorts())
		{
			res->get_m1()->ajouter_ressort(res);
			res->get_m2()->ajouter_ressort(res);
		}
	}

	void Tissu::deconnecte(Ressort*& r)
	{
		//trouver la position de r dans ressorts
		int pos(-1);
		for(size_t i(0); i < ressorts.size(); i++)
		{
			if(r == ressorts[i])
				pos = i;		
		}
		
		if(pos != -1)
		{
			//le supprimer
			ressorts.erase(ressorts.begin() + pos);
			
			//supprimer les ressorts ds la classe masse et reconnecte masses
			connecte_masses();
			
			//vérifier, si faux, on remet le tissu comme il était avant
			if(!check())
			{
				ressorts.push_back(r);
				connecte_masses();
			}
			else
			{
				//sinon, on supprime le pointeur
				delete r;
				r = nullptr;
			}
		}
	}

	bool Tissu::check() const
	{
		for(auto const& m : masses)
		{
			// condition 1
			if(m->get_ressorts().size() < 1) return false; 
			
			//condition 3.1
			for(auto const& res : m->get_ressorts()) 
			{
				if((res->get_m1() != m) and (res->get_m2() != m)) return false;
			}
		}
		for(auto const& res : ressorts)
		{
			//condition 2.2
			if(res->get_m1() == res->get_m2()) return false; 
			
			//condition 2.1
			if((res->get_m1() == nullptr) or (res->get_m2() == nullptr)) return false;
			
			//condition 3.2
			if(!res->get_m1()->possede_ressort(res)) return false;
			if(!res->get_m2()->possede_ressort(res)) return false;
		
		}
		
		return true;
	}
	
	//attention, pour TissuComposee les deux fonctions ci-dessous n'agissent sur rien (tissucompsee n'a pas de masse), c'est pour éviter une "double évolution" dans les tissus
	void Tissu::mise_a_jour_force() const
	{
		for(auto const& m : masses)
		{
			m->mise_a_jour_forces();
		}
	}

	void Tissu::evolue(Integrateur* const& type, double dt) const
	{
		for(auto const& m : masses)
		{
			type->evolue(m, dt);
		}
	}
	
	void Tissu::dessine()
	{
		support->dessine(*this);
	}
	

/** fin class Tissu **/


/** class TissuChaine **/

	//constructeur
	TissuChaine::TissuChaine(SupportADessin* const& support, vector<Vecteur3D> const& pos, double masse, double lambda, double k, double L0)
	:Tissu(support)
	{
		for(auto const& position : pos)
		{
			Masse* mas = new Masse(support, masse, position, lambda);
			masses.push_back(mas); 			
		}
		
		for(size_t i(0); i < pos.size() - 1; i++)
		{
			connecte(k, L0, masses[i], masses[i+1]);
		}
		
		if(!check())
		{
			connecte_masses();
		}
	}
	//destructeur
	TissuChaine::~TissuChaine()
	{
		for(auto & m : masses)
		{
			delete m;
			m = nullptr;
		}
	}
	

/**fin class TissuChaine**/

/** class TissuRectangle**/

	//constructeur
	TissuRectangle::TissuRectangle(SupportADessin* const& support, Vecteur3D largeur, Vecteur3D const& longueur, Vecteur3D const& pos, double masse, double lambda, double densite, double k, double L0)
	:Tissu(support)
	{
		//vecteurs ne sont pas colinéaires
		if((largeur * longueur) != largeur.norm() * longueur.norm())
		{
			if((largeur * longueur) != 0)
			{
				//s'ils ne sont pas orthogonaux
				largeur -= ((largeur * longueur) / longueur.norm2()) * longueur;
			}
			
			//mettre les masses
			for(size_t i(0); i <= longueur.norm() * densite; i++)
			{
				for(size_t j(0); j <= largeur.norm() * densite; j++)
				{
					Masse* mas = new Masse(support, masse, pos + i * 1.0 / (densite * longueur.norm()) * longueur + j * 1.0 / (densite * largeur.norm()) * largeur, lambda);
					masses.push_back(mas);
					
					if(j != 0)
					{
						//ressorts connectés selon dans le sens de la largeur
						connecte(k, L0, masses[masses.size() - 2], mas);
					}
				}
			}
			
			//ajouter les ressorts selon la longueur
			for(size_t i(0); i < largeur.norm() * densite + 1; i++)
			{
				for(size_t j(0); j <= longueur.norm() * densite - 1; j++)
				{
					connecte(k, L0, masses[i + j * (floor(largeur.norm() * densite) + 1)], masses[i + (j + 1) * (floor(largeur.norm() * densite) + 1)]);
				}
			}
		}
		if(!check())
		{
			connecte_masses();
		}
	}
	//destructeur
	TissuRectangle::~TissuRectangle()
	{
		for(auto & m : masses)
		{
			delete m;
			m = nullptr;
		}
	}
	

/** fin class TissuRectangle**/


/** class TissuDisque**/
	
	//constructeur
	TissuDisque::TissuDisque(SupportADessin* const& support, Vecteur3D const& pos, Vecteur3D const& normal, double masse, double pas, double lambda, double k, double L0, double angle)
	:Tissu(support)
	{
		//on prend un angle qui est un diviseur de 360, pour que le disque soit uniforme
		while(angle >= 360) angle -= 360;
		while(angle < 0) angle += 360;
		unsigned int nb(360 / angle);
		angle = 360 / nb;
		
		Masse* mas = new Masse(support, masse, pos, lambda);
		masses.push_back(mas);
		
		size_t nbr_m_rayon(floor(normal.norm() / pas) + 1);
		Vecteur3D n(1.0 / normal.norm() * normal);
		Vecteur3D u;
		
		//vecteur u, orthogonal à n et unitaire
		if(n.getX() == 0)		{u.set_coord(1,0,0);}
		else if(n.getY() == 0) 	{u.set_coord(0,1,0);}
		else if(n.getZ() == 0) 	{u.set_coord(0,0,1);}
		else
		{
			u.set_coord(-n.getY(), n.getX(), 0);
			u = 1.0 / u.norm() * u; 
		}
		
		for(size_t i(0); i < nb; i++)
		{
			u = cos(angle * M_PI / 180) * u + sin(angle * M_PI / 180) * (n ^ u);
			
			for(size_t j(1); j < nbr_m_rayon; j++)
			{
				Masse* mas = new Masse(support, masse, pos + j * pas * u , lambda);
				masses.push_back(mas);
				
				if(j == 1)
				{
					//on relie à m0
					connecte(k, L0, masses[0], mas);
				}
				else
				{
					//on relie selon une droite
					connecte(k, L0, masses[masses.size() - 2], mas);
				}
			}
		}
		
		for(size_t i(1); i < nbr_m_rayon; i++)
		{
			for(size_t j(0); j < nb; j++)
			{
				if(j < nb - 1)
				{
					connecte(k, L0, masses[i + j * (nbr_m_rayon - 1)], masses[i + (j + 1) * (nbr_m_rayon - 1)]);
				}
				else
				{
					connecte(k, L0, masses[i + j * (nbr_m_rayon - 1)], masses[i]);
				}
			}
		}
		
		if(!check())
		{
			connecte_masses();
		}
	}
	//destructeur
	TissuDisque::~TissuDisque()
	{
		for(auto & m : masses)
		{
			delete m;
			m = nullptr;
		}
	}
	
	
/** fin class TissuDisque**/

/** class TissuComposee **/

	//constructeur
	TissuComposee::TissuComposee(SupportADessin* const& support, vector<Tissu*>  const& tissus, double e, double k, double L0)
	:Tissu(support), tissus(tissus), epsilon(e), k(k), L0(L0)
	{
		raccommode();
		
		if(!check())
		{
			connecte_masses();
		}
	}
	
	
	//modificateurs
	void TissuComposee::add_Tissu(Tissu* const& t)
	{
		tissus.push_back(t);
		raccommode();
	}
	
	//accesseurs
	vector<Tissu*> TissuComposee::get_Tissu() const
	{
		return tissus;
	}
	
	//méthode
	bool TissuComposee::distance(Masse* const& masse1, Masse* const& masse2) const
	{
		Vecteur3D dist(masse1->get_position() - masse2->get_position());
		
		if(dist.norm() <= epsilon)
		{
			return true;
		}
		
		return false;
	}
	
	void TissuComposee::raccommode()
	{
		//Boucles sur chaque Tissu
		for(size_t i(0); i < tissus.size()-1; i++)
		{
			//Boucles sur les tissus
			for(size_t j(i + 1); j < tissus.size(); j++)
			{
				for(auto const& masse1 : tissus[i]->get_masses())
				{
					for(auto const& masse2 : tissus[j]->get_masses())
					{
						//on raccommode toutes les masses qui sont à une distance faible
						if(distance(masse1, masse2))
						{
							//ajoute ressort aux masses
							connecte(k, L0, masse1, masse2);
						}						
					}
				}
			}
		}
	}

	void TissuComposee::deconnecte(Ressort*& r)
	{
		Tissu::deconnecte(r);
		
		for(auto const& t : tissus)
		{
			t->deconnecte(r);
		}
	}
	
	bool TissuComposee::check() const
	{
		bool control(true);
		
		control &= Tissu::check();
		
		if(control)
		{
			for(auto const& t : tissus)
			{
				//on contrôl tous les tissus contenus, et on fait un "and" avec notre boolean
				control &= t->check();
			}
		}
		
		return control;
	}


/**fin class TissuComposee **/


void operator+=(TissuComposee& tissucompo, Tissu& t)
{
	bool dist(false);
	
	//on verifie qu'au moins une masse du nouveau tissu est à distance sufisamment faible
	for(auto const& m : t.get_masses())
	{
		for(auto const& t : tissucompo.get_Tissu())
		{
			for(auto const& ma : t->get_masses())
			{
				dist |= tissucompo.distance(m, ma);
			}
		}
	}
	
	//si c'est le cas, on raccommode
	if(dist)
	{
		tissucompo.add_Tissu(&t);
		tissucompo.raccommode();
	}
}

ostream& operator<<(ostream& sortie, Tissu const& t)
{
	for(auto const& r : t.get_ressorts())
	{
		sortie << *r << endl;
	}
	
	return sortie;
}

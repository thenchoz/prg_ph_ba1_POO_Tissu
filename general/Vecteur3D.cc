#include <iostream>
#include <math.h>
#include "Vecteur3D.h"

using namespace std;

/** class vecteur3D **/

	//constructeur
	Vecteur3D::Vecteur3D(double x, double y, double z)
	:pos{x,y,z}{}
	
	
	//set_coordonnee, variante avec trois modif et une seule
	void Vecteur3D::set_coord(double x, double y, double z)
	{
		pos[0] = x;
		pos[1] = y;
		pos[2] = z;
	}
	void Vecteur3D::set_coord(int p, double n) {pos[p] = n;}
	
	//accesseur, soit version x,y,z, soit d'après un int correspondant à la position dans le vecteur (entre 0 et 2)
	double Vecteur3D::getX() const {return pos[0];}
	double Vecteur3D::getY() const {return pos[1];}
	double Vecteur3D::getZ() const {return pos[2];}
	double Vecteur3D::getcoord(int i) const {return pos[i];}
	
	
	//méthodes
	ostream& Vecteur3D::affiche(ostream& sortie) const
	{
		sortie << '(' << pos[0] << ", " << pos[1] << ", " << pos[2] << ')' << endl;
		return sortie;
	}
	bool Vecteur3D::compare(Vecteur3D const& a_compare) const
	{
		return (a_compare.pos[0] == pos[0]) && (a_compare.pos[1] == pos[1]) && (a_compare.pos[2] == pos[2]);
	}
	
	//opperations sur les vecteurs
	void Vecteur3D::addition(Vecteur3D const& a_additione)
	{
		pos[0] += a_additione.pos[0];
		pos[1] += a_additione.pos[1];
		pos[2] += a_additione.pos[2];
	}
	void Vecteur3D::soustraction(Vecteur3D const& a_soustrait)
	{
		this->addition(a_soustrait.oppose());
	}
	Vecteur3D Vecteur3D::oppose() const
	{
		Vecteur3D opp(-pos[0], -pos[1], -pos[2]);
		return opp;
	}
	Vecteur3D Vecteur3D::mult(double lambda) const
	{
		Vecteur3D result(pos[0] * lambda, pos[1] * lambda, pos[2] * lambda);
		return result;
	}
	Vecteur3D Vecteur3D::prod_vect(Vecteur3D const& autre) const
	{
		Vecteur3D prod(pos[1]*autre.pos[2] - pos[2]*autre.pos[1], pos[2]*autre.pos[0] - pos[0]*autre.pos[2], pos[0]*autre.pos[1] - pos[1]*autre.pos[0]);
		return prod;
	}
	
	double Vecteur3D::prod_scal(Vecteur3D const& autre) const
	{
		return autre.pos[0] * pos[0] + autre.pos[1] * pos[1] + autre.pos[2] * pos[2];
	}
	double Vecteur3D::norm2() const
	{
		return prod_scal(*this);
	}
	double Vecteur3D::norm() const
	{
		return sqrt(norm2());
	}

/** fin class vecteur3D **/


//opérateurs
void operator+=(Vecteur3D& v1, Vecteur3D const& v2)
{
	v1.addition(v2);
}

const Vecteur3D operator+(Vecteur3D v1, Vecteur3D const& v2)
{
	v1 += v2;
	return v1;
}

void operator-=(Vecteur3D& v1, Vecteur3D const& v2)
{
	v1.soustraction(v2);
}

const Vecteur3D operator-(Vecteur3D v1, Vecteur3D const& v2)
{
	v1 -= v2;
	return v1;
}

const Vecteur3D operator-(Vecteur3D const& v)
{
	return v.oppose();
}

const Vecteur3D operator*(double lambda, Vecteur3D const& v) //Attention, toujours lambda * vecteur (par choix), et vecteur / lambda devient (1 / lambda) * vecteur (aussi par choix)
{
	return v.mult(lambda);  
}

const Vecteur3D operator^(Vecteur3D const& v1, Vecteur3D const& v2)
{
	return v1.prod_vect(v2);
}

const double operator*(Vecteur3D const& v1, Vecteur3D const& v2)
{
	return v1.prod_scal(v2);
}

bool operator==(Vecteur3D const& v1, Vecteur3D const& v2)
{
	return v1.compare(v2);
}

bool operator!=(Vecteur3D const& v1, Vecteur3D const& v2)
{
	return !(v1 == v2);
}

ostream& operator<<(ostream& sortie, Vecteur3D const& v)
{
	return v.affiche(sortie);
}


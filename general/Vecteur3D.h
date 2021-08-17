#ifndef VECTEUR_H
#define VECTEUR_H


//class vecteur 3D (x, y, z)
class Vecteur3D
{
	public:
	//constructeur
	Vecteur3D(double x = 0.0, double y = 0.0, double z = 0.0);
	//destructeur
	~Vecteur3D() {};
	//copie
	//Vecteur3D(Vecteur3D const& v); 			-> on garde le constructeur de copie par défaut
	
	
	//set_coordonnee, variante avec trois modif et une seule
	void set_coord(double x, double y, double z);
	void set_coord(int p, double n);
	
	//accesseur, soit version x,y,z, soit d'après un int correspondant à la position dans le vecteur (entre 0 et 2)
	double getX() const;
	double getY() const;
	double getZ() const;
	double getcoord(int i) const;
	
	//méthodes
	std::ostream& affiche(std::ostream& sortie) const;
	bool compare(Vecteur3D const& a_compare) const;
	
	//opperations sur les vecteurs (utilisé pour la plupart pour définir les opérateurs)
	void addition(Vecteur3D const& a_additione);
	void soustraction(Vecteur3D const& a_soustrait);
	Vecteur3D oppose() const;
	Vecteur3D mult(double lambda) const;
	Vecteur3D prod_vect(Vecteur3D const& autre) const;
	
	double prod_scal(Vecteur3D const& autre) const;
	double norm2() const;
	double norm() const;
	
	
	private:
	double pos[3];
};


//opérateurs
void operator+=(Vecteur3D& v1, Vecteur3D const& v2);

const Vecteur3D operator+(Vecteur3D v1, Vecteur3D const& v2);

void operator-=(Vecteur3D& v1, Vecteur3D const& v2);

const Vecteur3D operator-(Vecteur3D v1, Vecteur3D const& v2);

const Vecteur3D operator-(Vecteur3D const& v);

const Vecteur3D operator*(double lambda, Vecteur3D const& v); //Attention, toujours lambda * vecteur (par choix), et vecteur / lambda devient (1 / lambda) * vecteur (aussi par choix)

const Vecteur3D operator^(Vecteur3D const& v1, Vecteur3D const& v2);

const double operator*(Vecteur3D const& v1, Vecteur3D const& v2);

bool operator==(Vecteur3D const& v1, Vecteur3D const& v2);

bool operator!=(Vecteur3D const& v1, Vecteur3D const& v2);

std::ostream& operator<<(std::ostream& sortie, Vecteur3D const& v);

#endif  //VECTEUR_H

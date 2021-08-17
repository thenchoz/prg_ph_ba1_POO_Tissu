#include <iostream>
#include "../general/Vecteur3D.h"

using namespace std;

int main()
{
	// un vecteur3D :
	Vecteur3D vect1(1.0, 2.0, -0.1);

	// un autre vecteur3D
	Vecteur3D vect2(2.6, 3.5,  4.1);

	Vecteur3D vect3(vect1);  // copie de V1
	Vecteur3D vect4;         // le vecteur nul

	cout << "Vecteur3D 1 : " << vect1 << endl;
	cout << "Vecteur3D 2 : " << vect2 << endl;
	cout << "Vecteur3D 4 : " << vect4 << endl;
	
	//test des opérateur d'égalité
	cout << "Le vecteur 1 est ";
	if (vect1 == vect2) {
		cout << "égal au";
	} else {
		cout << "différent du";
	}
	cout << " vecteur 2," << endl << "et est ";
	if (vect1 != vect3) {
		cout << "différent du";
	} else {
		cout << "égal au";
	}
	cout << " vecteur 3." << endl;
	
	cout << endl;
	//test des opérations sur les vecteurs
	cout << "Vecteur3D 1 + Vecteur3D 2 = " << (vect1 + vect2);
	cout << "Vecteur3D 2 + Vecteur3D 1 = " << (vect2 + vect1);
	cout << "Vecteur3D 1 + Vecteur3D 4 = " << (vect1 + vect4);
	cout << "Vecteur3D 4 + Vecteur3D 1 = " << (vect4 + vect1);
	cout << "Vecteur3D 1 - Vecteur3D 2 = " << (vect1 - vect2);
	cout << "Vecteur3D 2 - Vecteur3D 1 = " << (vect2 - vect1);
	cout << "Vecteur3D 2 - Vecteur3D 2 = " << (vect2 - vect2);
	cout << "- Vecteur3D 1 = " << -vect1;
	cout << "- Vecteur3D 2 + Vecteur3D 1 = " << (-vect2 + vect1);
	cout << "2.5 	* Vecteur3D 1 = " << (2.5 * vect1);
	cout << "Vecteur3D 1 ^ Vecteur3D 2 = " << (vect1 ^ vect2);
	cout << "Vecteur3D 2 ^ Vecteur3D 1 = " << (vect2 ^ vect1);
	cout << "Vecteur3D 1 * Vecteur3D 2 = " << (vect1 * vect2) << endl;
	cout << "Vecteur3D 2 * Vecteur3D 1 = " << (vect2 * vect1) << endl;
	cout << "Norme2 du Vecteur3D 1 = " << (vect1.norm2()) << endl;
	cout << "Norme du Vecteur3D 1 = " << (vect1.norm()) << endl;
	cout << "Norme2 du Vecteur3D 2 = " << (vect2.norm2()) << endl;
	cout << "Norme du Vecteur3D 2 = " << (vect2.norm()) << endl;
	vect1 += vect2;
	cout << "Vecteur3D 1 += Vecteur3D 2 : " << vect1;
	vect1 -= vect2;
	cout << "Vecteur3D 1 -= Vecteur3D 2 : " << vect1;
	
	return 0;
}

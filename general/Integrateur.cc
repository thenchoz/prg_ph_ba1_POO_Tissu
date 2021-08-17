#include <iostream>
#include "Integrateur.h"


using namespace std;

/** class intégrateur **/

/** fin class intégrateur **/


/**class Integrateur Euler-Cromer **/
	
	
	//méthodes
	void IntegrateurEulerCromer::evolue(Masse* const& m, double dt) const
	{
		m->set_vitesse(m->get_vitesse()   + dt * m->acceleration()); // v(T + dt) = v(T) + dt * a(T)
		m->set_position(m->get_position() + dt * m->get_vitesse());  // x(T + dt) = x(T) + dt * v(T + dt)
		
		if((1/2 * m->get_masse() * m->get_vitesse().norm() < 0.1) && (m->get_force().norm() < 0.05)) m->set_vitesse(0, 0, 0);
	}

	
/** fin class intégrateur d'Euler-Cromer **/



/** class intégrateur Newmark **/
	
	
	//méthodes
	void IntegrateurNewmark::evolue(Masse* const& m, double dt) const
	{
		double epsilon = 0.0005;
		Vecteur3D v(m->get_vitesse());
		Vecteur3D v1(v);
		Vecteur3D x(m->get_position());
		Vecteur3D x1(x);
		Vecteur3D khi_1(1.0/(m->get_masse()) * (m->f(x, v)));
		Vecteur3D xi;
		Vecteur3D khi;
		Vecteur3D diff;
		
		do{
			xi = x1;
			khi = 1.0/(m->get_masse()) * m->f(x1, v1);
			v1 = v + 1.0/2.0 * dt * (khi + khi_1);
			x1 = x + dt * v + 1.0/3.0 * dt * dt * (1.0/2.0 * khi + khi_1); 
		
			diff = (x1 - xi);
		}while(diff.norm() >= epsilon);
		
		m->set_vitesse(v1);
		m->set_position(x1);
	}

/**fin class intégrateur Newmark**/



/** class intégrateur Runge Kutta **/
	
	
	//méthodes
	void IntegrateurRungeKutta::evolue(Masse* const& m, double dt) const
	{
		Vecteur3D k1(m->get_vitesse());
		Vecteur3D k_1(m->acceleration());
		Vecteur3D k2(k1 + 1.0/2.0 * dt * k_1);
		Vecteur3D k_2(1.0/(m->get_masse()) * (m->f(m->get_position() + 1.0/2.0 * dt * k1, m->get_vitesse() + 1.0/2.0 * dt *k_1)));
		Vecteur3D k3(k1 + 1.0/2.0 * dt * k_2);
		Vecteur3D k_3(1.0/(m->get_masse()) * (m->f(m->get_position() + 1.0/2.0 * dt * k2, m->get_vitesse() + 1.0/2.0 * dt * k_2)));
		Vecteur3D k4(k1 + dt * k_3);
		Vecteur3D k_4(1.0/(m->get_masse()) * (m->f(m->get_position() + dt * k3, m->get_vitesse() + dt * k_3)));		
	
		m->set_position(m->get_position() + 1.0/6.0 * dt * (k1 + 2.0 * k2 + 2.0 * k3 + k4));
		m->set_vitesse(m->get_vitesse() + 1.0/6.0 * dt * (k_1 + 2.0 * k_2 + 2.0 * k_3 + k_4));
	}

/** fin class intégrateur Runge Kutta **/

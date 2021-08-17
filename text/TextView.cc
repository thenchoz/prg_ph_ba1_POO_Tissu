#include <iostream>
#include "TextView.h"
#include "../general/Systeme.h"

using namespace std;


/** class TextView **/


	//consructeur
	TextView::TextView(std::ostream& flot)
	:flot(flot) {}
	
	
	//modificateurs
	
	//accesseur
	
	//méthodes
	void TextView::dessine(Tissu const& t)
	{
		flot << t;
	}
	void TextView::dessine(Systeme const& s)
	{
		flot << s;
	}
	void TextView::dessine(Masse const& m)
	{
		flot << m;
	}
	void TextView::dessine(Ressort const& r)
	{
		flot << r;
	}


/** fin class TextView **/

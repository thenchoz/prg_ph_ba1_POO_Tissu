#include "vue_opengl.h"
#include "vertex_shader.h" // Identifiants Qt de nos différents attributs
#include "../general/Systeme.h"


/** class VueOpenGL **/
//class reprise en partie du tutoriel d'OpenGL

	//deffinition méthodes dessine
	void VueOpenGL::dessine(Tissu const& t)
	{
		for(auto const& m : t.get_masses())
		{
			m->dessine();
		}
		for(auto const& r : t.get_ressorts())
		{
			r->dessine();
		}
	}
	void VueOpenGL::dessine(Systeme const& s)
	{
		for(auto const& t : s.get_Tissu())
		{
			t->dessine();
		}
	}
	void VueOpenGL::dessine(Masse const& m)
	{
		QMatrix4x4 matrice;
  
		double x(m.get_position().getX());
		double y(m.get_position().getY());
		double z(m.get_position().getZ());
  
		matrice.translate(x, y, z);
		matrice.scale(0.35);
		
		// color RGB
		double r(155);
		double g(155);
		double b(155);
		
		//dessineCube(matrice);
		dessineSphere(matrice, r, g, b);
	}
	void VueOpenGL::dessine(Ressort const& r)
	{
		
		QMatrix4x4 matrice;
		
		double x1(r.get_m1()->get_position().getX());
		double y1(r.get_m1()->get_position().getY());
		double z1(r.get_m1()->get_position().getZ());
		
		matrice.translate(x1, y1, z1);
		
		double x2(r.get_m2()->get_position().getX() - x1);
		double y2(r.get_m2()->get_position().getY() - y1);
		double z2(r.get_m2()->get_position().getZ() - z1);
		
		dessineLigne(matrice, x2, y2, z2);
		
	}
	
	
	//méthodes propres à la class, non re-touchées
	void VueOpenGL::init()
	{
		prog.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/vertex_shader.glsl");
		prog.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.glsl");
		
		
		prog.bindAttributeLocation("sommet",  SommetId);
		prog.bindAttributeLocation("couleur", CouleurId);

		// Compilation du shader OpenGL
		prog.link();

		// Activation du shader
		prog.bind();
		
		
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		
		sphere.initialize();

		initializePosition();
	}
	
	void VueOpenGL::initializePosition()
	{
		// position initiale
		matrice_vue.setToIdentity();
		matrice_vue.translate(0.0, 0.0, -10.0);
		matrice_vue.rotate(50, -1.0, 0.0, 0.0);
		matrice_vue.translate(0.0, 10.0, 0.0);
	}
	
	void VueOpenGL::translate(double x, double y, double z)
	{
		QMatrix4x4 translation_supplementaire;
		translation_supplementaire.translate(x, y, z);
		matrice_vue = translation_supplementaire * matrice_vue;
	}
	
	void VueOpenGL::rotate(double angle, double dir_x, double dir_y, double dir_z)
	{
		// Multiplie la matrice de vue par LA GAUCHE
		QMatrix4x4 rotation_supplementaire;
		rotation_supplementaire.rotate(angle, dir_x, dir_y, dir_z);
		matrice_vue = rotation_supplementaire * matrice_vue;
	}
	
	
	//méthodes pour dessiner (cube, sphere, ligne, etc)
	void VueOpenGL::dessineCube(QMatrix4x4 const& point_de_vue)
	{
		prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

		glBegin(GL_QUADS);
		// face coté X = +1
		prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
		prog.setAttributeValue(SommetId, +0.5, -0.5, -0.5);
		prog.setAttributeValue(SommetId, +0.5, +0.5, -0.5);
		prog.setAttributeValue(SommetId, +0.5, +0.5, +0.5);
		prog.setAttributeValue(SommetId, +0.5, -0.5, +0.5);

		// face coté X = -1
		prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0); // vert
		prog.setAttributeValue(SommetId, -0.5, -0.5, -0.5);
		prog.setAttributeValue(SommetId, -0.5, -0.5, +0.5);
		prog.setAttributeValue(SommetId, -0.5, +0.5, +0.5);
		prog.setAttributeValue(SommetId, -0.5, +0.5, -0.5);

		// face coté Y = +1
		prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0); // bleu
		prog.setAttributeValue(SommetId, -0.5, +0.5, -0.5);
		prog.setAttributeValue(SommetId, -0.5, +0.5, +0.5);
		prog.setAttributeValue(SommetId, +0.5, +0.5, +0.5);
		prog.setAttributeValue(SommetId, +0.5, +0.5, -0.5);

		// face coté Y = -1
		prog.setAttributeValue(CouleurId, 0.0, 1.0, 1.0); // cyan
		prog.setAttributeValue(SommetId, -0.5, -0.5, -0.5);
		prog.setAttributeValue(SommetId, +0.5, -0.5, -0.5);
		prog.setAttributeValue(SommetId, +0.5, -0.5, +0.5);
		prog.setAttributeValue(SommetId, -0.5, -0.5, +0.5);

		// face coté Z = +1
		prog.setAttributeValue(CouleurId, 1.0, 1.0, 0.0); // jaune
		prog.setAttributeValue(SommetId, -0.5, -0.5, +0.5);
		prog.setAttributeValue(SommetId, +0.5, -0.5, +0.5);
		prog.setAttributeValue(SommetId, +0.5, +0.5, +0.5);
		prog.setAttributeValue(SommetId, -0.5, +0.5, +0.5);

		// face coté Z = -1
		prog.setAttributeValue(CouleurId, 1.0, 0.0, 1.0); // magenta
		prog.setAttributeValue(SommetId, -0.5, -0.5, -0.5);
		prog.setAttributeValue(SommetId, -0.5, +0.5, -0.5);
		prog.setAttributeValue(SommetId, +0.5, +0.5, -0.5);
		prog.setAttributeValue(SommetId, +0.5, -0.5, -0.5);

		glEnd();
	}
	
	void VueOpenGL::dessineSphere (QMatrix4x4 const& point_de_vue, double r, double v, double b)
	{
		prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
		prog.setAttributeValue(CouleurId, r, v, b);		// met la couleur
		sphere.draw(prog, SommetId);					// dessine la sphère
	}
	
	void VueOpenGL::dessineLigne(QMatrix4x4 const& point_de_vue, double x, double y, double z)
	{
		prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
		
		glBegin(GL_LINES);
		
		prog.setAttributeValue(CouleurId, 1.0, 0.0, 1.0);
		prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
		prog.setAttributeValue(SommetId, x, y, z);
		
		glEnd();
		
	}


/** fin class VueOpenGL **/

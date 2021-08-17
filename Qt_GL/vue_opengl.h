#ifndef VUEOPENGL_H
#define VUEOPENGL_H

#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "../general/SupportADessin.h"
#include "glsphere.h"


//class VueOpenGL
//class reprise en partie du tutoriel d'OpenGL
class VueOpenGL : public SupportADessin
{
	public:
	// méthode(s) de dessin (héritée(s) de SupportADessin)
	virtual void dessine(Tissu const& t) override;
	virtual void dessine(Systeme const& s) override;
	virtual void dessine(Masse const& m) override;
	virtual void dessine(Ressort const& r) override;

	// méthodes de (ré-)initialisation
	void init();
	void initializePosition();

	// méthode set
	void setProjection(QMatrix4x4 const& projection) {prog.setUniformValue("projection", projection);}

	// méthodes set
	void translate(double x, double y, double z);
	void rotate(double angle, double dir_x, double dir_y, double dir_z);
	
	
	void dessineCube(QMatrix4x4 const& point_de_vue = QMatrix4x4());
	void dessineSphere(QMatrix4x4 const& point_de_vue, double r, double v, double b);
	void dessineLigne(QMatrix4x4 const& point_de_vue, double x, double y, double z);


	private:
	// Un shader OpenGL encapsulé dans une classe Qt
	QOpenGLShaderProgram prog;
	
	// "Caméra"
	QMatrix4x4 matrice_vue;
	
	GLSphere sphere;
};

#endif // VUEOPENGH_H

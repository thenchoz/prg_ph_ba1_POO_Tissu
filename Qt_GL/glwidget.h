#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTime> 
#include "vue_opengl.h"
#include "Initial.h"


//class GLWidget
//class reprise en partie du tutoriel d'OpenGL
class GLWidget : public QGLWidget
{
	public:
	//constructeur
	GLWidget(QWidget* parent = nullptr);
	//destructeur
	virtual ~GLWidget() override {};
	
	private:
	// Les 3 méthodes clés de la classe QGLWidget à réimplémenter
	virtual void initializeGL()                  override;
	virtual void resizeGL(int width, int height) override;
	virtual void paintGL()                       override;
	
	// Méthodes de gestion d'évènements
	virtual void keyPressEvent(QKeyEvent* event) override;
	virtual void timerEvent(QTimerEvent* event)  override;
	
	// Méthodes de gestion interne
	void pause();
	
	
	//attributs
	//support à dessin
	VueOpenGL vue;
	
	//timer
	int timerId;
	double t;
	
	//pour évoluer
	QTime chronometre;
	
	//un systeme à évoluer et dessiner
	Systeme syst;
	
	//un intégrateur;
	Integrateur* inte;
	
	//un moyen d'initier le systeme
	Initial initier;
};

#endif // GLWIDGET_H

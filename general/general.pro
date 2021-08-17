TEMPLATE = lib

CONFIG = staticlib c++11

SOURCES += \
	Vecteur3D.cc \
	Masse.cc \
	Ressort.cc \
	Integrateur.cc \
	Tissu.cc \
	Contraintes.cc \
	Initial.cc \
	Systeme.cc

HEADERS += \
	Vecteur3D.h \
	Masse.h \
	Ressort.h \
	Integrateur.h \
	Tissu.h \
	Contraintes.h \
	Initial.h \
	Systeme.h \
	Dessinable.h \
	SupportADessin.h

QT += core gui opengl widgets
CONFIG += c++11

win32:LIBS += -lopengl32


TARGET = projet_gl

LIBS += -L../general -lgeneral
	
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH += ../general

SOURCES += \
    main_qt_gl.cc \
    glwidget.cc \
    vue_opengl.cc \
    glsphere.cc

HEADERS += \
    vertex_shader.h \
    glwidget.h \
    vue_opengl.h \
    glsphere.h \
    ../general/Initial.h \
    ../general/Dessinable.h \
    ../general/Systeme.h \
    ../general/Tissu.h \
    ../general/Contraintes.h \
    ../general/Masse.h \
    ../general/Ressort.h \
    ../general/SupportADessin.h \
    ../general/Vecteur3D.h

RESOURCES += \
    resource.qrc

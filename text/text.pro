CONFIG += c++11

TARGET = projet_text

LIBS += -L../general -lgeneral
	
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    TextView.cc \
    main_text.cc

HEADERS += \
    ../general/SupportADessin.h \
    ../general/Systeme.h \
    ../general/Tissu.h \
    ../general/Masse.h \
    ../general/Ressort.h \
    ../general/Dessinable.h \
    ../general/Integrateur.h \
    ../general/Initial.h \
    TextView.h

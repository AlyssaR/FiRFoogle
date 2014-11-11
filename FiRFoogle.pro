TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
CONFIG += xml
QMAKE_CXXFLAGS += -Wno-write-strings

SOURCES += main.cpp \
<<<<<<< HEAD
    xmlparser.cpp

HEADERS += \
    xmlparser.h \
    English_Stem.h
=======
    tree.cpp

HEADERS += \
    file.h \
    tree.h
>>>>>>> ba1d5e73089937525783e76f923eb21c902139a4


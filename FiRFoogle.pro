TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
CONFIG += xml
QMAKE_CXXFLAGS += -Wno-write-strings

SOURCES += main.cpp \
    xmlparser.cpp \
    tree.cpp \
    porter2_stemmer.cpp

HEADERS += \
    xmlparser.h \
    file.h \
    tree.h \
    porter2_stemmer.h \
    rapidxml.h

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
CONFIG += xml
QMAKE_CXXFLAGS += -Wno-write-strings -fopenmp -mavx -fabi-version=0 -ffast-math
QMAKE_LFLAGS += -fopenmp
QMAKE_CXXFLAGS_RELEASE *= -O3


SOURCES += main.cpp \
    xmlparser.cpp \
    porter2_stemmer.cpp \
    index.cpp \
    handler.cpp \
    babyparser.cpp \
    queryparser.cpp

HEADERS += \
    xmlparser.h \
    porter2_stemmer.h \
    index.h \
    entry.h \
    handler.h \
    babyparser.h \
    rapidxml.h \
    rapidxml_iterators.h \
    rapidxml_utils.h \
    rapidxml_print.h \
    queryparser.h \
    article.h

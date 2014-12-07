TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
CONFIG += xml
QMAKE_CXXFLAGS += -Wno-write-strings



SOURCES += main.cpp \
    xmlparser.cpp \
    porter2_stemmer.cpp \
    handler.cpp \
    queryparser.cpp \
    avltree.cpp \
    index2.cpp \
    avlindex.cpp

HEADERS += \
    xmlparser.h \
    porter2_stemmer.h \
    entry.h \
    handler.h \
    rapidxml.h \
    rapidxml_iterators.h \
    rapidxml_utils.h \
    rapidxml_print.h \
    queryparser.h \
    article.h \
    avltree.h \
    index2.h \
    avlindex.h \
    avlnode.h

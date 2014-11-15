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
    index.cpp \
    handler.cpp \
    tinyxml2.cpp

HEADERS += \
    xmlparser.h \
    porter2_stemmer.h \
    index.h \
    entry.h \
    handler.h \
    tinyxml2.h

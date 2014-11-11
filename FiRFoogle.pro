TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
CONFIG += xml
QMAKE_CXXFLAGS += -Wno-write-strings

SOURCES += main.cpp \
    xmlparser.cpp

HEADERS += \
    xmlparser.h \
    English_Stem.h


TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
QMAKE_CXXFLAGS += -Wno-write-strings

SOURCES += main.cpp \
    tree.cpp

HEADERS += \
    file.h \
    tree.h


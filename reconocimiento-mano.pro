TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    HandGesture.cpp \
    MyBGSubtractorColor.cpp

HEADERS += \
    HandGesture.h \
    MyBGSubtractorColor.h

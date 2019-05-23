TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        Interpolation.cpp \
        LinearInterpolation.cpp \
        Exception.cpp \
    CubicSplineInterpolation.cpp

HEADERS += \
        Interpolation.h \
        LinearInterpolation.h \
        Exception.h \
    CubicSplineInterpolation.h
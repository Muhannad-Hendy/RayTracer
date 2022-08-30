TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Canvas.cpp \
        CanvasTest.cpp \
        Color.cpp \
        ColorTest.cpp \
        Intersection.cpp \
        IntersectionTracker.cpp \
        Matrix.cpp \
        MatrixTest.cpp \
        Ray.cpp \
        RaySphereIntersectionTest.cpp \
        Sphere.cpp \
        TransformationTest.cpp \
        Transformer.cpp \
        Tuple.cpp \
        TupleTest.cpp \
        Utilities.cpp \
        main.cpp

INCLUDEPATH += /Users/muhannadhendy/GoogleTest/googletest/googletest
INCLUDEPATH += /Users/muhannadhendy/GoogleTest/googletest/googlemock
INCLUDEPATH += /Users/muhannadhendy/GoogleTest/googletest/googletest/include
INCLUDEPATH += /Users/muhannadhendy/GoogleTest/googletest/googlemock/include

SOURCES += /Users/muhannadhendy/GoogleTest/googletest/googletest/src/gtest-all.cc
SOURCES += /Users/muhannadhendy/GoogleTest/googletest/googlemock/src/gmock-all.cc

HEADERS += \
    Canvas.h \
    Color.h \
    Intersection.h \
    IntersectionTracker.h \
    Matrix.h \
    Ray.h \
    Sphere.h \
    Transformer.h \
    Tuple.h \
    Utilities.h

TEMPLATE = app
CONFIG += console c++11
CONFIG += debug
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpthread

SOURCES += \
        Canvas.cpp \
        CanvasTest.cpp \
        Color.cpp \
        ColorTest.cpp \
        Intersection.cpp \
        IntersectionTracker.cpp \
        Light.cpp \
        LightAndShadingTest.cpp \
        Material.cpp \
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
        World.cpp \
        WorldTest.cpp \
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
    Light.h \
    Material.h \
    Matrix.h \
    Ray.h \
    Sphere.h \
    Transformer.h \
    Tuple.h \
    Utilities.h \
    World.h

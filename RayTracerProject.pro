TEMPLATE = app
CONFIG += console c++17
CONFIG += debug
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++17

LIBS += -lpthread

SOURCES += \
        Camera.cpp \
        CameraTest.cpp \
        Canvas.cpp \
        CanvasTest.cpp \
        Color.cpp \
        ColorTest.cpp \
        ConeTest.cpp \
        CubeTest.cpp \
        CylinderTest.cpp \
        Gradient.cpp \
        Intersection.cpp \
        IntersectionTracker.cpp \
        Light.cpp \
        LightAndShadingTest.cpp \
        Material.cpp \
        Matrix.cpp \
        MatrixTest.cpp \
        Pattern.cpp \
        PatternsTest.cpp \
        Plane.cpp \
        PlaneTest.cpp \
        Ray.cpp \
        RaySphereIntersectionTest.cpp \
        Rings.cpp \
        Shape.cpp \
        Sphere.cpp \
        Stripe.cpp \
        TransformationTest.cpp \
        Transformer.cpp \
        Tuple.cpp \
        TupleTest.cpp \
        Utilities.cpp \
        World.cpp \
        WorldTest.cpp \
        checker.cpp \
        cone.cpp \
        cube.cpp \
        cylinder.cpp \
        main.cpp \
        testpattern.cpp

INCLUDEPATH += /Users/muhannadhendy/GoogleTest/googletest/googletest
INCLUDEPATH += /Users/muhannadhendy/GoogleTest/googletest/googlemock
INCLUDEPATH += /Users/muhannadhendy/GoogleTest/googletest/googletest/include
INCLUDEPATH += /Users/muhannadhendy/GoogleTest/googletest/googlemock/include

SOURCES += /Users/muhannadhendy/GoogleTest/googletest/googletest/src/gtest-all.cc
SOURCES += /Users/muhannadhendy/GoogleTest/googletest/googlemock/src/gmock-all.cc

HEADERS += \
    Camera.h \
    Canvas.h \
    Color.h \
    Gradient.h \
    Intersection.h \
    IntersectionTracker.h \
    Light.h \
    Material.h \
    Matrix.h \
    Pattern.h \
    Plane.h \
    Ray.h \
    Rings.h \
    Shape.h \
    Sphere.h \
    Stripe.h \
    Transformer.h \
    Tuple.h \
    Utilities.h \
    World.h \
    checker.h \
    cone.h \
    cube.h \
    cylinder.h \
    testpattern.h

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
        Intersection.cpp \
        IntersectionTracker.cpp \
        Light.cpp \
        LightAndShadingTest.cpp \
        Material.cpp \
        Matrix.cpp \
        MatrixTest.cpp \
        Pattern.cpp \
        Plane.cpp \
        PlaneTest.cpp \
        Ray.cpp \
        RaySphereIntersectionTest.cpp \
        Shape.cpp \
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
    Camera.h \
    Canvas.h \
    Color.h \
    Intersection.h \
    IntersectionTracker.h \
    Light.h \
    Material.h \
    Matrix.h \
    Pattern.h \
    Plane.h \
    Ray.h \
    Shape.h \
    Sphere.h \
    Transformer.h \
    Tuple.h \
    Utilities.h \
    World.h

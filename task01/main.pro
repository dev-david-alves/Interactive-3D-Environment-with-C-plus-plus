# main.pro

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

# Set the build directory to /run
DESTDIR = ./run

# Move all generated files to the build directory
OBJECTS_DIR = $$OUT_PWD/run/.obj
MOC_DIR = $$OUT_PWD/run/.moc
RCC_DIR = $$OUT_PWD/run/.rcc
UI_DIR = $$OUT_PWD/run/.ui

INCLUDEPATH += bib
INCLUDEPATH += gui_glut
INCLUDEPATH += trab1

LIBS += -lGL -lGLU -lglut -l3ds -lSDL_image -lIL

SOURCES += main.cpp \
    bib/Camera.cpp \
    bib/CameraDistante.cpp \
    bib/CameraJogo.cpp \
    bib/Desenha.cpp \
    bib/model3ds.cpp \
    bib/Vetor3D.cpp \
    gui_glut/extra.cpp \
    gui_glut/gui.cpp \
    gui_glut/OpenTextures.cpp \
    utils/perlinNoise.cpp \
    utils/utils.cpp \
    tb01/object.cpp \
    tb01/brick.cpp \
    tb01/tree.cpp \
    tb01/character.cpp \
    tb01/sheep.cpp \
    tb01/spider.cpp \
    tb01/chicken.cpp

HEADERS += \
    bib/Camera.h \
    bib/CameraDistante.h \
    bib/CameraJogo.h \
    bib/Desenha.h \
    bib/model3ds.h \
    bib/Vetor3D.h \
    gui_glut/extra.h \
    gui_glut/gui.h \
    gui_glut/OpenTextures.h \
    utils/perlinNoise.h \
    utils/utils.h \
    headers/object.h \
    headers/brick.h \
    headers/tree.h \
    headers/character.h \
    headers/sheep.h \
    headers/spider.h \
    headers/chicken.h

# configuration Qt
QT       += core gui opengl widgets
TEMPLATE  = app

# ajout des libs au linker
win32 {
    win32-msvc* {
        LIBS     += opengl32.lib glu32.lib
    } else {
        LIBS     += -lopengl32 -lglu32
    }
}
else {
	LIBS     += -lGL -lGLU
}

# nom de l'exe genere
TARGET 	  = MindMaze
# fichiers sources/headers
SOURCES	+= main.cpp myglwidget.cpp \
    player.cpp \
    sphere.cpp \
    wall.cpp

HEADERS += \
    myglwidget.h \
    player.h \
    point.h \
    sphere.h \
    wall.h

DISTFILES += \
    textures/floor1.jpg \
    textures/tse1.png \
    textures/tse1.jpg \
    textures/tse2.jpg

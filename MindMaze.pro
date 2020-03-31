# configuration Qt
QT       += core gui opengl widgets multimedia
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
    dj.cpp \
    maze.cpp \
    player.cpp \
    skybox.cpp \
    sphere.cpp \
    surface.cpp \
    wall.cpp \
    webcamwidget.cpp

HEADERS += \
    cell.h \
    dj.h \
    maze.h \
    myglwidget.h \
    player.h \
    point.h \
    skybox.h \
    sphere.h \
    surface.h \
    wall.h \
    webcamwidget.h

DISTFILES +=

RESOURCES += \
    sounds/sounds.qrc \
    textures/textures.qrc

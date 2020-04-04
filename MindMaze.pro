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
    camera.cpp \
    dj.cpp \
    maze.cpp \
    menu.cpp \
    player.cpp \
    skybox.cpp \
    sphere.cpp \
    surface.cpp \
    victory.cpp \
    wall.cpp

HEADERS += \
    camera.h \
    cell.h \
    dj.h \
    maze.h \
    menu.h \
    myglwidget.h \
    mypoint.h \
    player.h \
    skybox.h \
    sphere.h \
    surface.h \
    victory.h \
    wall.h

DISTFILES +=

INCLUDEPATH += $$(OPENCV_DIR)\..\..\include

LIBS += -L$$(OPENCV_DIR)\lib \
    -lopencv_core420 \
    -lopencv_highgui420 \
    -lopencv_imgproc420 \
    -lopencv_imgcodecs420 \
    -lopencv_videoio420 \
    -lopencv_features2d420 \
    -lopencv_calib3d420

RESOURCES += \
    resources/resources.qrc \
    sounds/sounds.qrc \
    textures/textures.qrc

FORMS += \
    menu.ui \
    victory.ui

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/bullet.cpp \
    src/enemy.cpp \
    src/entityinfo.cpp \
    src/entitytypes.cpp \
    src/game.cpp \
    src/main.cpp \
    src/menu/mainmenu.cpp \
    src/menu/singleplayermenu.cpp \
    src/player.cpp \
    src/playerhitbox.cpp \
    src/texture.cpp

HEADERS += \
    src/bullet.h \
    src/enemy.h \
    src/entityinfo.h \
    src/entitytypes.h \
    src/game.h \
    src/menu/mainmenu.h \
    src/menu/singleplayermenu.h \
    src/player.h \
    src/playerhitbox.h \
    src/texture.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets/assets.qrc

DISTFILES +=

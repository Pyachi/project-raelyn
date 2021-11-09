QT       += core gui opengl network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# For compiling in Ubuntu
#QMAKE_LFLAGS += -no-pie

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
    src/ai/bullet.cpp \
    src/ai/bulletpattern.cpp \
    src/ai/collectable.cpp \
    src/ai/enemy.cpp \
    src/ai/player.cpp \
    src/assets/music.cpp \
    src/assets/sfx.cpp \
    src/assets/texture.cpp \
    src/entity/entity.cpp \
    src/entity/entitybullet.cpp \
    src/entity/entitycollectable.cpp \
    src/entity/entityenemy.cpp \
    src/entity/entityhitbox.cpp \
    src/entity/entityplayer.cpp \
    src/framework/game.cpp \
    src/framework/level.cpp \
    src/framework/menu.cpp \
    src/main.cpp \
    src/network/connection.cpp \
    src/network/packet.cpp \
    src/network/server.cpp \
    src/network/user.cpp \
    src/network/uuid.cpp

HEADERS += \
    alias.h \
    src/ai/bullet.h \
    src/ai/bulletpattern.h \
    src/ai/collectable.h \
    src/ai/enemy.h \
    src/ai/player.h \
    src/assets/music.h \
    src/assets/sfx.h \
    src/assets/texture.h \
    src/entity/entity.h \
    src/entity/entitybullet.h \
    src/entity/entitycollectable.h \
    src/entity/entityenemy.h \
    src/entity/entityhitbox.h \
    src/entity/entityplayer.h \
    src/framework/game.h \
    src/framework/level.h \
    src/framework/menu.h \
    src/network/connection.h \
    src/network/packet.h \
    src/network/server.h \
    src/network/user.h \
    src/network/uuid.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets/levels.qrc \
    assets/music.qrc \
    assets/soundeffects.qrc \
    assets/textures.qrc

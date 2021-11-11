QT       += core gui opengl network

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
    src/framework/user.cpp \
    src/framework/util.cpp \
    src/main.cpp \
    src/network/connection.cpp \
    src/network/packet.cpp \
    src/network/server.cpp \
    src/network/uid.cpp

HEADERS += \
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
    src/framework/user.h \
    src/framework/util.h \
    src/network/connection.h \
    src/network/packet.h \
    src/network/server.h \
    src/network/uid.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=

unix: LIBS += -L$$PWD/libraries/OpenAL/lib -lopenal

INCLUDEPATH += $$PWD/src/framework

equals(QT_PATCH_VERSION,8): {
unix: LIBS += -L$$PWD/libraries/SFML-2.5.1/lib -lsfml-system
unix: LIBS += -L$$PWD/libraries/SFML-2.5.1/lib -lsfml-audio
INCLUDEPATH += $$PWD/libraries/SFML-2.5.1/include
DEPENDPATH += $$PWD/libraries/SFML-2.5.1/include
copydata.commands = $(COPY_DIR) $$PWD/assets $$PWD/libraries/SFML-2.5.1/lib $$PWD/libraries/OpenAL/lib $$OUT_PWD
} else {
unix: LIBS += -L$$PWD/libraries/SFML-2.2/lib -lsfml-system
unix: LIBS += -L$$PWD/libraries/SFML-2.2/lib -lsfml-audio
INCLUDEPATH += $$PWD/libraries/SFML-2.2/include
DEPENDPATH += $$PWD/libraries/SFML-2.2/include
copydata.commands = $(COPY_DIR) $$PWD/assets $$PWD/libraries/SFML-2.2/lib $$PWD/libraries/OpenAL/lib $$OUT_PWD
}
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

LD_RUN_PATH=lib gcc main.c -I include -L lib -ltcod -o Project-Raelyn

QMAKE_LFLAGS += -Wl,-rpath,'lib'

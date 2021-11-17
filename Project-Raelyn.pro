QT       += core gui opengl network sql

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
    src/ai/boss.cpp \
    src/ai/bullet.cpp \
    src/ai/character.cpp \
    src/ai/collectable.cpp \
    src/ai/enemy.cpp \
    src/assets/font.cpp \
    src/assets/music.cpp \
    src/assets/sfx.cpp \
    src/assets/texture.cpp \
    src/database/database_api.cpp \
    src/database/scoreboard.cpp \
    src/entity/entity.cpp \
    src/entity/entityboss.cpp \
    src/entity/entitybullet.cpp \
    src/entity/entitycollectable.cpp \
    src/entity/entityenemy.cpp \
    src/entity/entityplayer.cpp \
    src/framework/controls.cpp \
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
    src/ai/boss.h \
    src/ai/bullet.h \
    src/ai/character.h \
    src/ai/collectable.h \
    src/ai/enemy.h \
    src/assets/font.h \
    src/assets/music.h \
    src/assets/sfx.h \
    src/assets/texture.h \
    src/database/database_api.h \
    src/database/scoreboard.h \
    src/entity/entity.h \
    src/entity/entityboss.h \
    src/entity/entitybullet.h \
    src/entity/entitycollectable.h \
    src/entity/entityenemy.h \
    src/entity/entityplayer.h \
    src/framework/controls.h \
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

RESOURCES += \
    src/assets/fonts.qrc \
    src/assets/level.qrc

INCLUDEPATH += \
    src/ai \
    src/assets \
    src/database \
    src/entity \
    src/framework \
    src/network

unix: {
    DESTDIR = ../Project-Raelyn
    LIBS += -L$$PWD/libraries/OpenAL/lib -lopenal
    equals(QT_PATCH_VERSION,8): {
        LIBS += -L$$PWD/libraries/SFML-2.5.1/lib -lsfml-system
        LIBS += -L$$PWD/libraries/SFML-2.5.1/lib -lsfml-audio
        INCLUDEPATH += $$PWD/libraries/SFML-2.5.1/include
        DEPENDPATH += $$PWD/libraries/SFML-2.5.1/include
        copydata.commands = $(COPY_DIR) $$PWD/assets $$PWD/libraries/SFML-2.5.1/lib $$PWD/libraries/OpenAL/lib $$DESTDIR
        QMAKE_LFLAGS += -no-pie
    } else {
        LIBS += -L$$PWD/libraries/SFML-2.2/lib -lsfml-system
        LIBS += -L$$PWD/libraries/SFML-2.2/lib -lsfml-audio
        INCLUDEPATH += $$PWD/libraries/SFML-2.2/include
        DEPENDPATH += $$PWD/libraries/SFML-2.2/include
        copydata.commands = $(COPY_DIR) $$PWD/assets $$PWD/libraries/SFML-2.2/lib $$PWD/libraries/OpenAL/lib $$DESTDIR
    }
    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
    QMAKE_EXTRA_TARGETS += first copydata
    LD_RUN_PATH='$ORIGIN/lib' gcc main.c -I include -L lib -ltcod -o Project-Raelyn
    QMAKE_LFLAGS_RPATH=
    QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN/lib\'"
}

win32: {
    DESTDIR = ..\Project-Raelyn
    LIBS += -L$$PWD/libraries/SFML-2.5.1-Win/lib -lsfml-system
    LIBS += -L$$PWD/libraries/SFML-2.5.1-Win/lib -lsfml-audio
    INCLUDEPATH += $$PWD/libraries/SFML-2.5.1-Win/include
    DEPENDPATH += $$PWD/libraries/SFML-2.5.1-Win/include
    copyassets.commands = $(COPY_DIR) $$PWD/assets $$DESTDIR/assets/
    copyassets.commands = $$replace(copyassets.commands, /, \\)
    copylibs.commands = $(COPY_DIR) $$PWD/libraries/SFML-2.5.1-Win/bin/ $$DESTDIR
    copylibs.commands = $$replace(copylibs.commands, /, \\)
    copyqt.commands = $(COPY_DIR) $$PWD/libraries/Qt5-Win/bin/ $$DESTDIR
    copyqt.commands = $$replace(copyqt.commands, /, \\)
    first.depends = $(first) copyassets copylibs copyqt
    export(first.depends)
    QMAKE_EXTRA_TARGETS += first copyassets copylibs copyqt
}

QT       += core gui opengl network multimedia

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
    src/ai/bulletpattern.cpp \
    src/ai/bullettype.cpp \
    src/ai/collectabletype.cpp \
    src/ai/enemytype.cpp \
    src/ai/playertype.cpp \
    src/assets/music.cpp \
    src/assets/sfx.cpp \
    src/assets/texture.cpp \
    src/entity/bullet.cpp \
    src/entity/collectable.cpp \
    src/entity/enemy.cpp \
    src/entity/entity.cpp \
    src/entity/player.cpp \
    src/entity/playerhitbox.cpp \
    src/game/game.cpp \
    src/main.cpp \
    src/menu/lobbymenu.cpp \
    src/menu/mainmenu.cpp \
    src/menu/multiplayermenu.cpp \
    src/menu/singleplayermenu.cpp \
    src/network/connection.cpp \
    src/network/packet.cpp \
    src/network/server.cpp \
    src/network/user.cpp

HEADERS += \
    src/ai/bulletpattern.h \
    src/ai/bullettype.h \
    src/ai/collectabletype.h \
    src/ai/enemytype.h \
    src/ai/playertype.h \
    src/assets/music.h \
    src/assets/sfx.h \
    src/assets/texture.h \
    src/entity/bullet.h \
    src/entity/collectable.h \
    src/entity/enemy.h \
    src/entity/entity.h \
    src/entity/player.h \
    src/entity/playerhitbox.h \
    src/game/game.h \
    src/menu/lobbymenu.h \
    src/menu/mainmenu.h \
    src/menu/multiplayermenu.h \
    src/menu/singleplayermenu.h \
    src/network/connection.h \
    src/network/packet.h \
    src/network/server.h \
    src/network/user.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets/music.qrc \
    assets/soundeffects.qrc \
    assets/textures.qrc

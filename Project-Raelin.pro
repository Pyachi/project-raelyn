QT       += core gui opengl network multimedia sql

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
    src/database/database_api.cpp \
    src/database/scoreboard.cpp \
    src/entity/bullet.cpp \
    src/entity/collectable.cpp \
    src/entity/enemy.cpp \
    src/entity/entity.cpp \
    src/entity/player.cpp \
    src/entity/playerhitbox.cpp \
    src/game.cpp \
    src/main.cpp \
    src/menu/mainmenu.cpp \
    src/menu/multiplayermenu.cpp \
    src/menu/singleplayermenu.cpp \
    src/network/connection.cpp \
    src/network/server.cpp \
    src/sound/sfx.cpp \
    src/sound/sound.cpp \
    src/texture.cpp

HEADERS += \
    src/database/database_api.h \
    src/database/scoreboard.h \
    src/entity/bullet.h \
    src/entity/collectable.h \
    src/entity/enemy.h \
    src/entity/entity.h \
    src/entity/player.h \
    src/entity/playerhitbox.h \
    src/game.h \
    src/menu/mainmenu.h \
    src/menu/multiplayermenu.h \
    src/menu/singleplayermenu.h \
    src/network/connection.h \
    src/network/server.h \
    src/resources.h \
    src/sound/sfx.h \
    src/sound/sound.h \
    src/texture.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets/assets.qrc \
    assets/assets.qrc

DISTFILES += \
    assets/images/background.png \
    assets/images/bulletEllipse.png \
    assets/images/bulletRound.png \
    assets/images/enemy.png \
    assets/images/player.png \
    assets/images/player_bullet.png \
    assets/images/player_hitbox.png \
    assets/sounds/sound_collect_1.wav \
    assets/sounds/sound_collect_2.wav \
    assets/sounds/sound_collect_3.wav \
    assets/sounds/sound_expl_heavy_1.wav \
    assets/sounds/sound_expl_heavy_2.wav \
    assets/sounds/sound_expl_heavy_3.wav \
    assets/sounds/sound_expl_heavy_4.wav \
    assets/sounds/sound_expl_light_1.wav \
    assets/sounds/sound_expl_light_2.wav \
    assets/sounds/sound_expl_light_3.wav \
    assets/sounds/sound_expl_med_1.wav \
    assets/sounds/sound_expl_med_2.wav \
    assets/sounds/sound_expl_med_3.wav \
    assets/sounds/sound_expl_superheavy_1.wav \
    assets/sounds/sound_expl_superheavy_2.wav \
    assets/sounds/sound_hit_1.wav \
    assets/sounds/sound_hit_2.wav \
    assets/sounds/sound_hit_3.wav \
    assets/sounds/sound_laser_1.wav \
    assets/sounds/sound_missile_1.wav \
    assets/sounds/sound_missile_2.wav \
    assets/sounds/sound_missile_3.wav \
    assets/sounds/sound_powerup_1.wav \
    assets/sounds/sound_powerup_2.wav \
    assets/sounds/sound_powerup_3.wav \
    assets/sounds/sound_select_1.wav \
    assets/sounds/sound_select_2.wav

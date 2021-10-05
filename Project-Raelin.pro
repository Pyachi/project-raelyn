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
    src/assets/textures.cpp \
    src/entity/ai/ai.cpp \
    src/entity/entitytypes.cpp \
    src/entity/types/baseentity.cpp \
    src/entity/types/bullet.cpp \
    src/entity/types/collidableentity.cpp \
    src/entity/types/enemy.cpp \
    src/entity/types/linkedentity.cpp \
    src/entity/types/player.cpp \
    src/entity/types/playerhitbox.cpp \
    src/game/game.cpp \
    src/main.cpp

HEADERS += \
    src/assets/textures.h \
    src/entity/ai/ai.h \
    src/entity/entitytypes.h \
    src/entity/types/aientity.h \
    src/entity/types/baseentity.h \
    src/entity/types/bullet.h \
    src/entity/types/collidableentity.h \
    src/entity/types/enemy.h \
    src/entity/types/linkedentity.h \
    src/entity/types/player.h \
    src/entity/types/playerhitbox.h \
    src/game/game.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets/assets.qrc

DISTFILES +=

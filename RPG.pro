QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += C++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    artifact.cpp \
    bunch.cpp \
    cell.cpp \
    character.cpp \
    chest.cpp \
    dungeon.cpp \
    enchantment.cpp \
    enemy.cpp \
    enumtostring.cpp \
    equipment.cpp \
    equipmentartifact.cpp \
    game.cpp \
    gamewindow.cpp \
    hero.cpp \
    item.cpp \
    main.cpp \
    mainwindow.cpp \
    potion.cpp \
    setchanges.cpp \
    setcoef.cpp \
    setcount.cpp \
    setdamage.cpp \
    setitem.cpp \
    setpotion.cpp \
    setprotect.cpp \
    table.cpp \
    title.cpp \
    view.cpp \
    weapon.cpp \
    weaponartifact.cpp \
    weaponartifactenchantment.cpp \
    weaponenchantment.cpp

HEADERS += \
    artifact.h \
    bunch.h \
    cell.h \
    character.h \
    chest.h \
    dungeon.h \
    enchantment.h \
    enemy.h \
    enums.h \
    enumtostring.h \
    equipment.h \
    equipmentartifact.h \
    game.h \
    gamewindow.h \
    hero.h \
    item.h \
    mainwindow.h \
    matrix.h \
    potion.h \
    setchanges.h \
    setcoef.h \
    setcount.h \
    setdamage.h \
    setitem.h \
    setpotion.h \
    setprotect.h \
    table.h \
    title.h \
    view.h \
    weapon.h \
    weaponartifact.h \
    weaponartifactenchantment.h \
    weaponenchantment.h

FORMS += \
    gamewindow.ui \
    mainwindow.ui \
    title.ui \
    view.ui

#TRANSLATIONS += \
#    RPG_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
